#include <string>

#include "abstractmap.h"
#include "abstractset.h"
#include "hashmap.hpp"
#include "hashset.hpp"
#include "listmap.hpp"
#include "listset.hpp"
#include "test.h"

template <typename T>
void testIterable(AbstractIterable<T>& iterable);

template <typename T>
void testIterable(AbstractIterable<T>& iterable, const T& item1, const T& item2);

template <typename T>
void testSet(AbstractSet<T>& set, const T& sample1, const T& sample2);

template <typename K, typename V>
void testMap(AbstractMap<K, V>& map, const K& key1, const K& key2, const V& value1, const V& value2);

class IntHasher : public Hasher<int>
{
public:
    int operator()(const int& key)
    {
        return key;
    }
};

class StringHasher : public Hasher<string>
{
public:
    int operator()(const string& key)
    {
        int hash = 0;
        for (size_t i = 0; i < key.length(); ++i)
        {
            hash += key[i] << (8 * (i % 4));
        }
        return hash;
    }
};

int main()
{
    string str1 = "hello";
    string str2 = "world";
    IntHasher intHasher;
    StringHasher stringHasher;
    
    test::section("ListSet<int>");
    ListSet<int> intListSet;
    testSet(intListSet, 1, 5);
    
    test::section("ListSet<string>");
    ListSet<string> stringListSet;
    testSet(stringListSet, str1, str2);
    
    test::section("HashSet<int>");
    HashSet<int> intHashSet(&intHasher);
    testSet(intHashSet, 1, 5);
    
    test::section("HashSet<string>");
    HashSet<string> stringHashSet(&stringHasher);
    testSet(stringHashSet, str1, str2);
    
    test::section("ListMap<int, int>");
    ListMap<int, int> intListMap;
    testMap(intListMap, 1, 2, 3, 4);
    
    test::section("ListMap<string, float>");
    ListMap<string, float> strFloatListMap;
    testMap(strFloatListMap, str1, str2, 1.0f, 2.0f);
    
    test::section("HashMap<int, int>");
    HashMap<int, int> intHashMap(&intHasher);
    testMap(intHashMap, 1, 2, 3, 4);
    
    test::section("HashMap<string, float>");
    HashMap<string, float> strFloatHashMap(&stringHasher);
    testMap(strFloatHashMap, str1, str2, 1.0f, 2.0f);
    
    return 0;
}

template <typename T>
void testIterable(AbstractIterable<T>& iterable)
{
    AbstractIterator<T>* iterator = iterable.createIterator();
    test::result(iterator != NULL, "iterable creates a non-NULL iterator");
    test::result(iterator->moveNext() == false, "empty iterator can't moveNext");
    delete iterator;
}

template <typename T>
void testIterable(AbstractIterable<T>& iterable, const T& item1, const T& item2)
{
    AbstractIterator<T>* iterator = iterable.createIterator();
    test::result(iterator != NULL, "iterable creates a non-NULL iterator");
    test::result(iterator->moveNext() == true, "iterator can moveNext");
    const T& val1 = iterator->getValue();
    test::result(iterator->moveNext() == true, "iterator can moveNext again");
    const T& val2 = iterator->getValue();
    test::result(iterator->moveNext() == false, "iterator can't moveNext again");
    bool goodVals = (val1 == item1 && val2 == item2) || (val1 == item2 && val2 == item1);
    test::result(goodVals, "iterator returned the two items");
    delete iterator;
}

template <typename T>
void testSet(AbstractSet<T>& set, const T& sample1, const T& sample2)
{
    testIterable(set);
    test::result(set.contains(sample1) == false, "set shouldn't contain sample1");
    test::result(set.contains(sample2) == false, "set shouldn't contain sample2");
    
    set.add(sample1);
    test::result(set.contains(sample1) == true, "set should contain sample1");
    test::result(set.contains(sample2) == false, "set shouldn't contain sample2");
    
    set.add(sample2);
    testIterable(set, sample1, sample2);
    test::result(set.contains(sample1) == true, "set should contain sample1");
    test::result(set.contains(sample2) == true, "set should contain sample2");
    
    set.remove(sample1);
    test::result(set.contains(sample1) == false, "set shouldn't contain sample1");
    test::result(set.contains(sample2) == true, "set should contain sample2");
    
    set.remove(sample2);
    test::result(set.contains(sample1) == false, "set shouldn't contain sample1");
    test::result(set.contains(sample2) == false, "set shouldn't contain sample2");
}

template <typename K, typename V>
void testMap(AbstractMap<K, V>& map, const K& key1, const K& key2, const V& value1, const V& value2)
{
    V getResult;
    
    testIterable(map);
    test::result(map.get(key1, &getResult) == false, "map shouldn't contain key1");
    test::result(map.get(key2, &getResult) == false, "map shouldn't contain key2");
    
    map.set(key1, value1);
    test::result(map.get(key1, &getResult) == true, "map should contain key1");
    test::result(getResult == value1, "map should have value1 for key1");
    test::result(map.get(key2, &getResult) == false, "map shouldn't contain key2");
    
    map.set(key2, value2);
    testIterable(map, KeyValue<K, V>(key1, value1), KeyValue<K, V>(key2, value2));
    test::result(map.get(key1, &getResult) == true, "map should contain key1");
    test::result(getResult == value1, "map should have value1 for key1");
    test::result(map.get(key2, &getResult) == true, "map should contain key2");
    test::result(getResult == value2, "map should have value2 for key2");
    
    map.remove(key1);
    test::result(map.get(key1, &getResult) == false, "map shouldn't contain key1");
    test::result(map.get(key2, &getResult) == true, "map should contain key2");
    test::result(getResult == value2, "map should have value2 for key2");
    
    map.remove(key2);
    test::result(map.get(key1, &getResult) == false, "map shouldn't contain key1");
    test::result(map.get(key2, &getResult) == false, "map shouldn't contain key2");
}