#ifndef ABSTRACTITERABLE_H
#define ABSTRACTITERABLE_H

template <typename T>
class AbstractIterator;

template <typename T>
class AbstractIterable
{
public:
    virtual AbstractIterator<T> *createIterator() const = 0;
};

template <typename T>
class AbstractIterator
{
public:
    virtual bool moveNext() = 0;
    virtual const T &getValue() const = 0;
};

#endif