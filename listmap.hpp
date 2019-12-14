#ifndef LISTMAP_H
#define LISTMAP_H

#include "abstractmap.h"

template <typename K, typename V>
class ListMapNode : public KeyValue<K, V>
{
public:
    ListMapNode<K, V> *next;

    ListMapNode(const K &k, const V &v) : KeyValue<K, V>(k, v){};
};

template <typename K, typename V>
class ListMapIterator;

template <typename K, typename V>
class ListMap : public AbstractMap<K, V>
{
private:
    ListMapNode<K, V> *_first;

public:
    ListMap()
    {
        _first = NULL;
    };

    ~ListMap()
    {
        ListMapNode<K, V> *next;
        while (_first != NULL)
        {
            next = _first->next;
            delete _first;
            _first = next;
        }
    }

    bool get(const K &key, V *value) const
    {
        ListMapNode<K, V> *node = _first;
        while (node != NULL && node->key != key)
        {
            node = node->next;
        }
        if (node != NULL)
        {
            *value = node->value;
            return true;
        }
        return false;
    }

    bool set(const K &key, const V &value)
    {
        ListMapNode<K, V> *node = _first;
        while (node != NULL && node->key != key)
        {
            node = node->next;
        }
        if (node != NULL)
        {
            node->value = value;
            return true;
        }
        else
        {
            node = new ListMapNode<K, V>(key, value);
            node->next = _first;
            _first = node;
            return false;
        }
    }

    bool remove(const K &key)
    {
        ListMapNode<K, V> *node = _first;
        ListMapNode<K, V> *prev = NULL;
        while (node != NULL && node->key != key)
        {
            prev = node;
            node = node->next;
        }
        if (node != NULL)
        {
            if (prev != NULL)
            {
                prev->next = node->next;
            }
            else
            {
                _first = node->next;
            }
            delete node;
            return true;
        }
        return false;
    }

    AbstractIterator<KeyValue<K, V>> *createIterator() const
    {
        return new ListMapIterator<K, V>(_first);
    }
};

template <typename K, typename V>
class ListMapIterator : public AbstractIterator<KeyValue<K, V>>
{
private:
    bool _started;
    ListMapNode<K, V> *_node;

public:
    ListMapIterator(ListMapNode<K, V> *node) : _started(false), _node(node) {}

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

    const KeyValue<K, V> &getValue() const
    {
        return *_node;
    }
};

#endif