#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "src/dsu.h"

class Cell {
public:
    int x;
    int y;

    Cell(int x, int y) : x(x), y(y) {}

    bool operator==(const Cell& c) const {
        return x == c.x && y == c.y;
    }
};

namespace std {
template <>
class hash<Cell> {
public:
    size_t operator()(const Cell& c) const {
        return hash<int>()(c.x) ^ hash<int>()(c.y);
    }
};
}  // namespace std

using namespace std;

int main() {
#if 0
    // Basic use case for trivial types like std::string
    {
        vector<string> nodes = {"one", "two", "three", "four"};
        disjoint_set<string> ds;
        for (string& n : nodes) ds.insert(n);

        ds.unite("one", "three");
        ds.unite("four", "two");

        cout << ds;
        // cout << boolalpha;

        // cout << ds.same("one", "two") << '\n';
        // cout << ds.same("one", "three") << '\n';
    }
#endif

#if 0
    // Copy constructor demo.
    {
        auto copy1 = ds;
        auto copy2 = disjoint_set(ds);
        copy1.insert("five");
        copy2.insert("six");
        cout << '\n';
        ds.disp_link();
        copy1.disp_link();
        copy2.disp_link();
    }
#endif

// TODO:
#if 0
    // DSU with Cell class
    {
        disjoint_set<Cell> ds;
        Cell c(1, 1);
        ds.insert(c);
        // ds.insert(Cell(2, 2));
        // ds.insert(Cell(3, 3));
        cout << "hello\n";
    }
#endif

#if 0
    // Use case for derived and user-defined types.
    {
        // disjoint_set<string> ds;
        disjoint_set<pair<string, int>> ds1;
        ds1.insert({"a", 1});
        ds1.insert({"b", 2});
        ds1.insert({"c", 3});
        ds1.unite({"a", 1}, {"c", 3});

        // cout << ds1 << '\n';

        disjoint_set<vector<string>> ds2;

        // disjoint_set<set<float>> ds3;
    }
#endif

#if 0
    disjoint_set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.unite(1, 2);
    cout << set[2] << endl; // Prints 1.
    cout << set[4]; // Fails.
#endif

// Demo operator+=
#if 0
    disjoint_set<int> set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.unite(1, 3);
    disjoint_set<int> set2;
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    set2.unite(3, 5);
    set1 += set2;
    cout << "set1:" << endl << set1 << endl << "set2:" << endl << set2 << endl;
#endif

// Demo operator+
#if 0
    disjoint_set<int> set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.unite(1, 3);
    disjoint_set<int> set2;
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    set2.unite(3, 5);
    auto set3 = set1 + set2;
    cout << "set1:" << endl << set1 << endl << "set2:" << endl << set2 << endl << "set3:" << endl << set3 << endl;
#endif

    return 0;
}
