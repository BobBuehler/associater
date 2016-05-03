#ifndef ABSTRACTMAP_H
#define ABSTRACTMAP_H

template < typename K, typename V >
class AbstractMap
{
public:
    virtual bool get(const K& key, V* value) const = 0;
    virtual void set(const K& key, const V& value) = 0;
    virtual void remove(const K& key) = 0;
    
    virtual ~AbstractMap() {};
};

#endif