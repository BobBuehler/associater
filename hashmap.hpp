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

template < typename K, typename V >
class HashMap: public AbstractMap<K, V> {
private:
    Hasher<K>* _hasher;
    int _bucketCount;
    ListMap<K, V>** _buckets;

public:
    HashMap(Hasher<K>* h, int bucketCount = 128) : _hasher(h), _bucketCount(bucketCount)
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
    
    void set(const K& key, const V& value)
    {
        int bucketIndex = (*_hasher)(key) % _bucketCount;
        ListMap<K, V>* bucket = _buckets[bucketIndex];
        if (bucket == NULL)
        {
            bucket = _buckets[bucketIndex] = new ListMap<K, V>();
        }
        bucket->set(key, value);
    }
    
    void remove(const K& key)
    {
        int bucketIndex = (*_hasher)(key) % _bucketCount;
        ListMap<K, V>* bucket = _buckets[bucketIndex];
        if (bucket != NULL)
        {
            bucket->remove(key);
        }
    }
};

#endif