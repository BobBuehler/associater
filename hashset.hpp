#ifndef HASHSET_H
#define HASHSET_H

#include "abstractset.h"
#include "hashmap.hpp"

template < typename T > class HashSetIterator;

template < typename T >
class HashSet : public AbstractSet<T>
{
private:
    HashMap<T, bool> _map;
    
public:
    HashSet(Hasher<T>* h) : _map(h) {}
    
    ~HashSet() {}
    
    void add(const T& value)
    {
        _map.set(value, true);
    }
    
    void remove(const T& value)
    {
        _map.remove(value);
    }
    
    bool contains(const T& value) const
    {
        bool ignore;
        return _map.get(value, &ignore);
    }
    
    AbstractIterator<T>* createIterator() const
    {
        return new HashSetIterator<T>(_map.createIterator());
    }
};

template < typename T >
class HashSetIterator : public AbstractIterator<T>
{
private:
    AbstractIterator<KeyValue<T, bool> >* _iterator;

public:
    HashSetIterator(AbstractIterator<KeyValue<T, bool> >* iterator) : _iterator(iterator) {}
    
    ~HashSetIterator()
    {
        delete _iterator;
    }
    
    bool moveNext()
    {
        return _iterator->moveNext();
    }
    
    const T& getValue() const
    {
        return _iterator->getValue().key;
    }
};

#endif