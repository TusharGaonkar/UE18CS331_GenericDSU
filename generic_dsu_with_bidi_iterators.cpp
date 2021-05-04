
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class disjoint_set {
private:
    map<T, size_t> set_size;

public:
    map<T, T> link;

    map<T, T>::iterator begin() {
        return link.begin();
    }
    map<T, T>::iterator end() {
        return link.end();
    }

    disjoint_set(){};                                              // Default constructor.
    disjoint_set(disjoint_set<T> const&) = default;                // Copy constructor.
    disjoint_set<T>& operator=(const disjoint_set<T>&) = default;  // Copy assignment operator.

    void insert(T a);
    void insert(disjoint_set<T> set);
    void unite(T a, T b);
    void merge(T a, T b);
    T find(T a);
    bool same(T a, T b);
    bool exists(T a);

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

template <typename T>
void disjoint_set<T>::insert(T a) {
    if (!link.contains(a) && !set_size.contains(a)) {
        link[a] = a;
        set_size[a] = 1;
    }
}

template <typename T>
void disjoint_set<T>::insert(disjoint_set<T> set) {
    for (auto& [k, v] : set.link) {
        insert(k);
        insert(v);
        unite(k, v);
    }
}

template <typename T>
void disjoint_set<T>::unite(T a, T b) {
    // Find component representatives.
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (set_size[a] < set_size[b]) swap(a, b);
    set_size[a] += set_size[b];
    link[b] = a;
}

template <typename T>
void disjoint_set<T>::merge(T a, T b) {
    link[b] = a;
}

// With path compression
template <typename T>
T disjoint_set<T>::find(T a) {
    if (a == link[a]) return a;
    return link[a] = find(link[a]);  // we set the direct parent to the root of the set to reduce path length.
}

template <typename T>
bool disjoint_set<T>::same(T a, T b) {
    return find(a) == find(b);
}

template <typename T>
bool disjoint_set<T>::exists(T a) {
    return (link.contains(a) && set_size.contains(a));
}

// TODO: Given an iterator to a pair in link, modify the key.
// 1. Copy all nodes in the DSU to a new one only if they don't point to the node we're changing.

/** Helper Functions for Debugging **/
template <typename T>
void disjoint_set<T>::disp_link() const {
    for (auto& [k, v] : link) cout << k << "->" << v << '\n';
    cout << '\n';
}

template <typename T>
void disjoint_set<T>::disp_set_size() const {
    for (auto& [k, v] : set_size) cout << k << ": " << v << '\n';
    cout << '\n';
}

int main() {
#if 0
    disjoint_set<int> ds;
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
#endif

#if 1
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

    // cout << ds;
    // cout << boolalpha;
    // cout << ds.same("one", "two") << '\n';
    // cout << ds.same("one", "three") << '\n';

    // Traverse backwards
    for (auto it = --ds.end();; --it) {
        cout << (*it).first << ": ";

        string key = (*it).first;
        // Find which component this element belongs to.
        cout << ds.find(key) << '\n';
        if (it == ds.begin()) break;
    }

    cout << '\n';
#endif

#if 0
    // operator=
    disjoint_set<int> ds2 = ds;
    for (auto d : ds2) cout << d.first << "->" << d.second << '\n';
#endif
}
