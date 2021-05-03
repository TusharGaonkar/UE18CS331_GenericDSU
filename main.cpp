#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "src/dsu.h"

class Cell {
public:
    int x;
    int y;

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
#if 1
    // Basic use case for trivial types like std::string
    {
        vector<string> nodes = {"one", "two", "three", "four"};
        disjoint_set<string> ds;
        for (string& n : nodes) ds.insert(n);

        ds.unite("one", "three");
        ds.unite("four", "two");

        /*
            one         four
             \            |   
             three      two
            
        */

        cout << ds;
        cout << boolalpha;
        cout << ds.same("one", "two") << '\n';
        cout << ds.same("one", "three") << '\n';
    }
#endif

#if 0
    // Copy constructor demo.
    {
        // Same disjoint sets as before.
        vector<string> nodes = {"one", "two", "three", "four"};
        disjoint_set<string> ds;
        for (string& n : nodes) ds.insert(n);
        ds.unite("one", "three");
        ds.unite("four", "two");

        // Make copies.
        auto copy1 = ds;
        auto copy2 = disjoint_set(ds);
        
        // Modify them.
        copy1.insert("five");
        copy2.insert("six");
        
        // Display all 3.
        ds.disp_link();
        copy1.disp_link();
        copy2.disp_link();
    }
#endif

#if 0
    // DSU with Cell class
    {
        disjoint_set<Cell> ds;
        Cell c({1, 1});
        ds.insert(c);
        ds.insert({2, 2});
        ds.insert(Cell({3, 3}));

        ds.unite({2, 2}, c);

        /*
            C(1,1)      C(3,3)
              \
              C(2,2)
        */

        cout << boolalpha;
        cout << ds.same(c, {2, 2}) << '\n';
        cout << ds.same({1, 1}, Cell({3, 3})) << '\n';
    }
#endif

#if 0
    // Use case for derived types.
    {
        // Works because we've added std::hash<pair<int, int>>().
        disjoint_set<pair<string, int>> ds1;
        ds1.insert({"a", 1});
        ds1.insert({"b", 2});
        ds1.insert({"c", 3});
        ds1.unite({"a", 1}, {"c", 3});

        for (auto& [k, v] : ds1.link) {
            cout << "{" << k.first << "," << k.second << "} -> {" << v.first << "," << v.second << "}" << '\n';
        }

        
        // Similarly for std::vector and std::set.
        // disjoint_set<vector<string>> ds2;
        // disjoint_set<set<char>> ds2;
        // set<char> s1 = {'a', 'b', 'c'};
        // set<char> s2 = {'d', 'e'};
        // set<char> s3 = {'f', 'g', 'h', 'i'};
        // set<char> s4 = {'j', 'k', 'l', 'm'};
        // set<char> s5 = {'n'};
        // set<char> s6 = {};

        // ds2.insert(s1);
        // ds2.insert(s2);
        // ds2.insert(s3);
        // ds2.insert(s4);
        // ds2.insert(s5);
        // ds2.insert(s6);
        // ds2.unite(s1, s3);
        // ds2.unite(s1, s4);
        // ds2.unite(s5, s6);

        // /*
        //     { {a,b,c}, {f,g,h,i}, {j,k,l,m} }
        //     { {n}, {} }
        //     { {d,e} }
        // */

        // cout << boolalpha;
        // cout << ds2.same(s3, s4) << '\n';
        // cout << ds2.same(s1, s6) << '\n';
    }
#endif

// operator[]: Returns the component representative of the argument.
#if 0
    disjoint_set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.unite(1, 2);
    cout << set[2] << endl; // Prints 1.
    cout << set[4]; // Fails.
#endif

// operator+=: Merges two disjoint_set objects.
#if 0
    disjoint_set<int> set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.unite(1, 3);
    /*
        1       2
        \
         3
    */
    disjoint_set<int> set2;
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    set2.unite(3, 5);
    /*
        3       4
        \
         5
    */

    set1 += set2;
    /*
        1       2       4
       / \
      5  3
    */
    cout << "set1:" << endl << set1 << endl << "set2:" << endl << set2 << endl;
#endif

// operator+: Merges two disjoint_set objects.
// (Similar to +=).
#if 0
    disjoint_set<int> set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.unite(1, 3);
    /*
        1       2
        \
         3
    */

    disjoint_set<int> set2;
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    set2.unite(3, 5);
    /*
        3       4
        \
         5
    */

    auto set3 = set1 + set2;
    /*
        1       2       4
       / \
      5  3
    */
    cout << "set1:" << endl
         << set1 << endl
         << "set2:" << endl
         << set2 << endl
         << "set3:" << endl
         << set3 << endl;
#endif

// operator== and operator!=: Compare two disjoint_set objects for equality.
#if 0
    disjoint_set<int> set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.unite(1, 3);
    /*
        1       2
        \
         3
    */

    disjoint_set<int> set2;
    set2.insert(1);
    set2.insert(2);
    set2.insert(3);
    set2.unite(1, 3);
    /*
        1       2
        \
         3
    */

    disjoint_set<int> set3;
    set3.insert(1);
    set3.insert(2);
    set3.insert(3);
    set3.unite(1, 2);
    /*
        1       3
        \
         2
    */

    cout << "set1 == set2: " << (set1 == set2 ? "PASS" : "FAIL") << endl;
    cout << "set1 != set2: " << (set1 != set2 ? "FAIL" : "PASS") << endl;
    cout << "set1 == set3: " << (set1 == set3 ? "FAIL" : "PASS") << endl;
    cout << "set1 != set3: " << (set1 != set3 ? "PASS" : "FAIL") << endl;
#endif

    return 0;
}
