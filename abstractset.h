#ifndef ABSTRACTSET_H
#define ABSTRACTSET_H

#include "abstractiterable.h"

template < typename T >
class AbstractSet : public AbstractIterable<T>
{
public:
    virtual void add(const T& value) = 0;
    virtual void remove(const T& value) = 0;
    virtual bool contains(const T& value) const = 0;
    
    virtual ~AbstractSet() {};
};

#endif