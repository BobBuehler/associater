#ifndef LINKEDSET_H
#define LINKEDSET_H

#include "abstractset.h"

template < typename T >
class LinkedSetNode
{
public:
    const T value;
    LinkedSetNode<T>* next;
    
    LinkedSetNode(const T& v) : value(v), next(NULL) {};
};

template < typename T >
class LinkedSet : public AbstractSet<T>
{
private:
    LinkedSetNode<T>* _first;
    LinkedSetNode<T>* _last;

public:
    LinkedSet() : _first(NULL), _last(NULL) {};
    virtual ~LinkedSet()
    {
        LinkedSetNode<T>* temp;
        while (_first != NULL)
        {
            temp = _first->next;
            delete _first;
            _first = temp;
        }
    }
    void add(const T& value)
    {
        LinkedSetNode<T>* node = new LinkedSetNode<T>(value);
        if (_last == NULL)
        {
            _first = _last = node;
        }
        else
        {
            _last->next = node;
            _last = node;
        }
    }
    void remove(const T& value)
    {
        LinkedSetNode<T>* prev = NULL;
        LinkedSetNode<T>* cur = _first;
        while (cur != NULL && cur->value != value)
        {
            prev = cur;
            cur = cur->next;
        }
        if (cur != NULL && cur->value == value)
        {
            if (prev != NULL)
            {
                prev->next = cur->next;
                delete cur;
            }
            else
            {
                _first = cur->next;
            }
            
            if (cur->next == NULL)
            {
                _last = cur;
            }
        }
    }
    bool contains(const T& value) const
    {
        LinkedSetNode<T>* cur = _first;
        while (cur != NULL && cur->value != value)
        {
            cur = cur->next;
        }
        return cur != NULL && cur->value == value;
    }
};

#endif