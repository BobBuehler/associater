#include <iostream>
#include <string>

#include "abstractmap.h"
#include "abstractset.h"
#include "listmap.hpp"
#include "listset.hpp"
#include "test.h"

using namespace std;

template <typename T>
void testSet(AbstractSet<T>& set, const T& sample1, const T& sample2);

template <typename K, typename V>
void testMap(AbstractMap<K, V>& map, const K& key1, const K& key2, const V& value1, const V& value2);

int main()
{
    test::section("ListSet<int>");
    ListSet<int> intSet;
    testSet(intSet, 1, 5);
    
    test::section("ListSet<string>");
    ListSet<string> stringSet;
    string stringSample1 = "hello";
    string stringSample2 = "world";
    testSet(stringSet, stringSample1, stringSample2);
    
    test::section("ListMap<int, int>");
    ListMap<int, int> intMap;
    testMap(intMap, 1, 2, 3, 4);
    
    test::section("ListMap<string, float>");
    ListMap<string, float> strFloatMap;
    string key1 = "hello";
    string key2 = "world";
    testMap(strFloatMap, key1, key2, 1.0f, 2.0f);
    
    return 0;
}

template <typename T>
void testSet(AbstractSet<T>& set, const T& sample1, const T& sample2)
{
    test::result(set.contains(sample1) == false, "set shouldn't contain sample1");
    test::result(set.contains(sample2) == false, "set shouldn't contain sample2");
    
    set.add(sample1);
    test::result(set.contains(sample1) == true, "set should contain sample1");
    test::result(set.contains(sample2) == false, "set shouldn't contain sample2");
    
    set.add(sample2);
    set.remove(sample1);
    test::result(set.contains(sample1) == false, "set shouldn't contain sample1");
    test::result(set.contains(sample2) == true, "set should contain sample2");
}

template <typename K, typename V>
void testMap(AbstractMap<K, V>& map, const K& key1, const K& key2, const V& value1, const V& value2)
{
    V getResult;
    
    test::result(map.get(key1, &getResult) == false, "map shouldn't contain key1");
    test::result(map.get(key2, &getResult) == false, "map shouldn't contain key2");
    
    map.set(key1, value1);
    test::result(map.get(key1, &getResult) == true, "map should contain key1");
    test::result(getResult == value1, "map should have value1 for key1");
    test::result(map.get(key2, &getResult) == false, "map shouldn't contain key2");
    
    map.set(key2, value2);
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