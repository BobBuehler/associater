#ifndef ABSTRACTMAP_H
#define ABSTRACTMAP_H

#include "abstractiterable.h"

template <typename K, typename V>
class KeyValue
{
public:
    const K key;
    V value;

    KeyValue(const K &k, const V &v) : key(k), value(v){};
    KeyValue(const KeyValue<K, V> &other) : key(other.key), value(other.value){};

    bool operator==(const KeyValue<K, V> &other) const
    {
        return key == other.key && value == other.value;
    }
};

template <typename K, typename V>
class AbstractMap : public AbstractIterable<KeyValue<K, V>>
{
public:
    virtual bool get(const K &key, V *value) const = 0;
    virtual bool set(const K &key, const V &value) = 0;
    virtual bool remove(const K &key) = 0;

    virtual ~AbstractMap(){};
};

#endif