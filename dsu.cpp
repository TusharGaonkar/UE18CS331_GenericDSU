#include "dsu.h"

template <typename T>
disjoint_set<T>::disjoint_set() {
    cout << "Constructor\n";
}

template <typename T>
void disjoint_set<T>::insert(T a) {
    if (link.contains(a) || set_size.contains(a)) {
        cout << "[ERROR] : {add_edge()} - Node already exists" << '\n';
    } else {
        link[a] = a;
        set_size[a] = 1;
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

// Without path compression
template <typename T>
T disjoint_set<T>::find(T a) {
    while (a != link[a]) a = link[a];
    return a;
}

// With path compression (TODO: Yet to be tested)
// T disjoint_set<T>::find_fast(T a) {
//     if (a == link[a])
//         return a;
//     else
//         return link[a] = find_fast(link[a]);  // we set the direct parent to the root of the set to reduce path length.
// }

template <typename T>
bool disjoint_set<T>::same(T a, T b) {
    return find(a) == find(b);
}

/** Helper Functions for Debugging **/
template <typename T>
void disjoint_set<T>::disp_link() {
    for (auto& [k, v] : link) cout << k << ": " << v << '\n';
    cout << '\n';
}

template <typename T>
void disjoint_set<T>::disp_set_size() {
    for (auto& [k, v] : set_size) cout << k << ": " << v << '\n';
    cout << '\n';
}