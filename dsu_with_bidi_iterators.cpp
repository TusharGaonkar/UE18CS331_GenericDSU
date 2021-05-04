
#include <cstddef>  // For std::ptrdiff_t
#include <iostream>
#include <iterator>  // For std::forward_iterator_tag
#include <map>

using namespace std;

class disjoint_set {
private:
    map<int, size_t> set_size;

public:
    map<int, int> link;

    map<int, int>::iterator begin() {
        return link.begin();
    }
    map<int, int>::iterator end() {
        return link.end();
    }

    disjoint_set(){};                                        // Default constructor.
    disjoint_set(disjoint_set const&) = default;             // Copy constructor.
    disjoint_set& operator=(const disjoint_set&) = default;  // Copy assignment operator.

    void insert(int a);
    void insert(disjoint_set set);
    void unite(int a, int b);
    void merge(int a, int b);
    int find(int a);
    bool same(int a, int b);
    bool exists(int a);

    /** Helper Functions for Debugging **/
    void disp_link() const;
    void disp_set_size() const;

    // Overloading the '<<' operator using a friend function. This is inlined because of method 2 of this SO answer (https://stackoverflow.com/a/4661372/11481456).
    friend std::ostream& operator<<(std::ostream& o, const disjoint_set& ds) {
        o << "Links: \n";
        ds.disp_link();
        o << "Set Sizes: \n";
        ds.disp_set_size();
        return o;
    }
};

void disjoint_set::insert(int a) {
    if (!link.contains(a) && !set_size.contains(a)) {
        link[a] = a;
        set_size[a] = 1;
    }
}

void disjoint_set::insert(disjoint_set set) {
    for (auto& [k, v] : set.link) {
        insert(k);
        insert(v);
        unite(k, v);
    }
}

void disjoint_set::unite(int a, int b) {
    // Find component representatives.
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (set_size[a] < set_size[b]) swap(a, b);
    set_size[a] += set_size[b];
    link[b] = a;
}

void disjoint_set::merge(int a, int b) {
    link[b] = a;
}

// With path compression
int disjoint_set::find(int a) {
    if (a == link[a]) return a;
    return link[a] = find(link[a]);  // we set the direct parent to the root of the set to reduce path length.
}

bool disjoint_set::same(int a, int b) {
    return find(a) == find(b);
}

bool disjoint_set::exists(int a) {
    return (link.contains(a) && set_size.contains(a));
}

// TODO: Given an iterator to a pair in link, modify the key.
// 1. Copy all nodes in the DSU to a new one only if they don't point to the node we're changing.

/** Helper Functions for Debugging **/
void disjoint_set::disp_link() const {
    for (auto& [k, v] : link) cout << k << "->" << v << '\n';
    cout << '\n';
}

void disjoint_set::disp_set_size() const {
    for (auto& [k, v] : set_size) cout << k << ": " << v << '\n';
    cout << '\n';
}

int main() {
    // map<int, int> mp;
    // mp[1] = -1;
    // mp[2] = -2;
    // mp[3] = -3;
    // mp[4] = -4;

    // mp.begin()->first = 5;
    // cout << mp.begin()->first << '\n';

    disjoint_set ds;
    ds.insert(1);
    ds.insert(2);
    ds.insert(3);
    ds.insert(4);
    ds.insert(5);
    ds.insert(6);
    ds.insert(7);

    ds.unite(1, 3);
    ds.unite(1, 5);
    ds.unite(7, 5);
    ds.unite(4, 6);

    // Traverse forwards
    // for (auto d : ds)
    // std::cout << d.first << "->" << d.second << '\n';
    for (auto it = ds.begin(); it != ds.end(); ++it) {
        cout << (*it).first << ' ';
    }
    cout << '\n';

    // Traverse backwards
    for (auto it = --ds.end(); ; --it) {
        cout << (*it).first << ": ";

        int key = (*it).first;
        // Find which component this element belongs to.
        cout << ds.find(key) << '\n';
        if (it == ds.begin()) break;
    }
    cout << '\n';

    // operator=
    disjoint_set ds2 = ds;
    for (auto d : ds2) cout << d.first << "->" << d.second << '\n';
}
