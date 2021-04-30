#ifndef DSU_H
#define DSU_H

#include <iostream>
#include <unordered_map>

using namespace std;

template <typename T>
class disjoint_set {
private:
    unordered_map<T, T> link;
    unordered_map<T, size_t> set_size;

public:
    explicit disjoint_set();
    void insert(T a);
    void unite(T a, T b);
    T find(T a);
    bool same(T a, T b);

    /** Helper Functions for Debugging **/
    void disp_link();

    void disp_set_size();
};

#include "dsu.cpp"

#endif
