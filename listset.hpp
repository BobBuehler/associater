#ifndef LINKEDSET_H
#define LINKEDSET_H

#include "abstractset.h"

template <typename T>
class ListSetNode;

template <typename T>
class ListSetIterator;

template <typename T>
class ListSet : public AbstractSet<T>
{
private:
    ListSetNode<T> *_first;

public:
    ListSet() : _first(NULL) {}

    virtual ~ListSet()
    {
        ListSetNode<T> *temp;
        while (_first != NULL)
        {
            temp = _first->next;
            delete _first;
            _first = temp;
        }
    }

    void add(const T &value)
    {
        ListSetNode<T> *node = new ListSetNode<T>(value);
        if (_first == NULL)
        {
            _first = node;
        }
        else
        {
            node->next = _first;
            _first = node;
        }
    }

    void remove(const T &value)
    {
        ListSetNode<T> *prev = NULL;
        ListSetNode<T> *cur = _first;
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
            }
            else
            {
                _first = cur->next;
            }
            delete cur;
        }
    }

    bool contains(const T &value) const
    {
        ListSetNode<T> *cur = _first;
        while (cur != NULL && cur->value != value)
        {
            cur = cur->next;
        }
        return cur != NULL && cur->value == value;
    }

    AbstractIterator<T> *createIterator() const
    {
        return new ListSetIterator<T>(_first);
    }
};

template <typename T>
class ListSetNode
{
public:
    const T value;
    ListSetNode<T> *next;

    ListSetNode(const T &v) : value(v), next(NULL) {}
};

template <typename T>
class ListSetIterator : public AbstractIterator<T>
{
private:
    bool _started;
    ListSetNode<T> *_node;

public:
    ListSetIterator(ListSetNode<T> *node) : _started(false), _node(node) {}

    bool moveNext()
    {
        if (!_started)
        {
            _started = true;
        }
        else
        {
            _node = _node->next;
        }

        return _node != NULL;
    }

    const T &getValue() const
    {
        return _node->value;
    }
};

#endif