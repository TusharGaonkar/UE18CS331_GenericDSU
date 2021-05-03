#include "dsu.h"

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
T& disjoint_set<T>::operator[](T index) {
    if (!link.contains(index)) {
        cout << "[ERROR] : {operator[]()} - Index doesn't exist" << endl;
        exit(1);
    }
    return link[find(index)];
}

template <typename T>
disjoint_set<T>& disjoint_set<T>::operator+=(const disjoint_set<T>& rhs) {
    insert(rhs);
    return *this;
}

template <typename T>
disjoint_set<T> disjoint_set<T>::operator+(const disjoint_set<T>& rhs) {
    auto set = *this;
    set.insert(rhs);
    return set;
}

/** Helper Functions for Debugging **/
template <typename T>
void disjoint_set<T>::disp_link() const {
    for (auto& [k, v] : link) cout << k << ": " << v << '\n';
    cout << '\n';
}

template <typename T>
void disjoint_set<T>::disp_set_size() const {
    for (auto& [k, v] : set_size) cout << k << ": " << v << '\n';
    cout << '\n';
}
