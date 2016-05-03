#include <iostream>
#include <string>

#include "abstractset.h"
#include "listset.hpp"
#include "test.h"

using namespace std;

template <typename T>
void testSet(AbstractSet<T>& set, const T& sample1, const T& sample2);

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