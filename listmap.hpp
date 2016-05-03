#ifndef LISTMAP_H
#define LISTMAP_H

#include "abstractmap.h"

template < typename K, typename V >
class ListMapNode
{
public:
    const K key;
    V value;
    ListMapNode<K, V>* next;
    
    ListMapNode(const K& k, const V& v) : key(k), value(v) {};
};

template < typename K, typename V >
class ListMap: public AbstractMap<K, V> {
private:
    ListMapNode<K, V>* _first;

public:
    ListMap()
    {
        _first = NULL;
    };
    
    ~ListMap()
    {
        ListMapNode<K, V>* next;
        while (_first != NULL)
        {
            next = _first->next;
            delete _first;
            _first = next;
        }
    }
    
    bool get(const K& key, V* value) const
    {
        ListMapNode<K, V>* node = _first;
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
    
    void set(const K& key, const V& value)
    {
        ListMapNode<K, V>* node = _first;
        while (node != NULL && node->key != key)
        {
            node = node->next;
        }
        if (node != NULL)
        {
            // overwrite
            node->value = value;
        }
        else
        {
            // insert at front
            node = new ListMapNode<K, V>(key, value);
            node->next = _first;
            _first = node;
        }
    }
    
    void remove(const K& key)
    {
        ListMapNode<K, V>* node = _first;
        ListMapNode<K, V>* prev = NULL;
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
        }
    }
};

#endif