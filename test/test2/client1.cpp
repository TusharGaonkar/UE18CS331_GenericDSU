// Connected components in a graph.

#include <iostream>

#include "../../src/dsu.h"

disjoint_set<int> set;

void test(int obj1, int obj2, bool isEqual);

int main() {
    set.insert(1);
    test(1, 1, true);
    set.insert(2);
    test(1, 2, false);
    set.unite(1, 2);
    test(1, 2, true);
    set.insert(3);
    set.unite(1, 3);
    test(1, 3, true);
    test(2, 3, true);
    set.insert(4);
    test(1, 4, false);
    set.insert(5);
    set.unite(4, 5);
    test(4, 5, true);
    test(1, 5, false);
    set.unite(3, 5);
    test(2, 4, true);
    return 0;
}

void test(int obj1, int obj2, bool isEqual) {
    auto result = isEqual ? set.find(obj1) == set.find(obj2) : set.find(obj1) != set.find(obj2);
    std::cout << "root1 " << (isEqual ? "==" : "!=") << " root2: " << (result ? "PASS" : "FAIL") << std::endl;
}
