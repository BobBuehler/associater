#ifndef HASHMAP_H
#define HASHMAP_H

#include "abstractmap.h"
#include "listmap.hpp"

template < typename K >
class Hasher
{
public:
    virtual int operator()(const K& key) = 0;
};

template < typename K, typename V > class HashMapIterator;

template < typename K, typename V >
class HashMap: public AbstractMap<K, V> {
private:
    Hasher<K>* _hasher;
    int _count;
    int _bucketCount;
    ListMap<K, V>** _buckets;

public:
    HashMap(Hasher<K>* h) : _hasher(h), _count(0), _bucketCount(1)
    {
        _buckets = new ListMap<K, V>*[_bucketCount];
        for (int i = 0; i < _bucketCount; ++i)
        {
            _buckets[i] = NULL;
        }
    };
    
    ~HashMap()
    {
        for (int i = 0; i < _bucketCount; ++i)
        {
            delete _buckets[i];
        }
        delete [] _buckets;
    }
    
    bool get(const K& key, V* value) const
    {
        int bucketIndex = (*_hasher)(key) % _bucketCount;
        ListMap<K, V>* bucket = _buckets[bucketIndex];
        if (bucket != NULL)
        {
            return bucket->get(key, value);
        }
        return false;
    }
    
    bool set(const K& key, const V& value)
    {
        int bucketIndex = (*_hasher)(key) % _bucketCount;
        ListMap<K, V>* bucket = _buckets[bucketIndex];
        if (bucket == NULL)
        {
            bucket = _buckets[bucketIndex] = new ListMap<K, V>();
        }
        if (!bucket->set(key, value))
        {
            _count++;
            _checkCount();
            return false;
        }
        return true;
    }
    
    bool remove(const K& key)
    {
        int bucketIndex = (*_hasher)(key) % _bucketCount;
        ListMap<K, V>* bucket = _buckets[bucketIndex];
        if (bucket != NULL)
        {
            if (bucket->remove(key))
            {
                _count--;
                return true;
            }
        }
        return false;
    }
    
    AbstractIterator<KeyValue<K, V> >* createIterator() const
    {
        return new HashMapIterator<K, V>(_bucketCount, _buckets);
    }
    
private:
    void _checkCount()
    {
        if (_count > _bucketCount / 2)
        {
            int oldBucketCount = _bucketCount;
            ListMap<K, V>** oldBuckets = _buckets;
            
            while (_count > _bucketCount / 2)
            {
                _bucketCount *= 2;
            }
            _buckets = new ListMap<K, V>*[_bucketCount];
            for (int i = 0; i < _bucketCount; ++i)
            {
                _buckets[i] = NULL;
            }
            _count = 0;
            
            HashMapIterator<K, V> iterator(oldBucketCount, oldBuckets);
            while(iterator.moveNext())
            {
                KeyValue<K, V> kv = iterator.getValue();
                set(kv.key, kv.value);
            }
            
            for (int i = 0; i < oldBucketCount; ++i)
            {
                delete oldBuckets[i];
            }
            delete [] oldBuckets;
        }
    }
};

template < typename K, typename V >
class HashMapIterator : public AbstractIterator<KeyValue<K, V> >
{
private:
    int _bucketIndex;
    int _bucketCount;
    ListMap<K, V>** _buckets;
    AbstractIterator<KeyValue<K, V> >* _iterator;

public:
    HashMapIterator(int bucketCount, ListMap<K, V>** buckets)
        : _bucketIndex(-1), _bucketCount(bucketCount), _buckets(buckets), _iterator(NULL) {}
    
    bool moveNext()
    {
        if (_bucketIndex == -1)
        {
            moveNextNewBucket();
        }
        else if (_iterator != NULL)
        {
            if (!_iterator->moveNext())
            {
                delete _iterator;
                _iterator = NULL;
                moveNextNewBucket();
            }
        }
        
        return _iterator != NULL;
    }
    
    const KeyValue<K, V>& getValue() const
    {
        return _iterator->getValue();
    }

private:
    void moveNextNewBucket()
    {
        _bucketIndex++;
        while(_bucketIndex < _bucketCount)
        {
            ListMap<K, V>* bucket = _buckets[_bucketIndex];
            if (bucket != NULL)
            {
                _iterator = bucket->createIterator();
                if (_iterator->moveNext())
                {
                    return;
                }
                else
                {
                    delete _iterator;
                    _iterator = NULL;
                }
            }
            _bucketIndex++;
        }
    }
};

#endif