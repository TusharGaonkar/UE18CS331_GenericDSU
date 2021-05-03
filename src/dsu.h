#ifndef DSU_H
#define DSU_H

#include <iostream>
#include <unordered_map>

using namespace std;

namespace std {

template <typename T1, typename T2>
class hash<pair<T1, T2>> {
public:
    size_t operator()(const pair<T1, T2>& p) const {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
};

template <typename T>
class hash<vector<T>> {
public:
    size_t operator()(const vector<T>& v) const {
        size_t seed = v.size();
        for (auto& i : v) {
            // Based on this SO reply: https://stackoverflow.com/a/4948967/11481456
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

template <typename T>
class hash<set<T>> {
public:
    size_t operator()(const set<T>& s) const {
        size_t seed = s.size();
        for (auto& i : s) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

};  // namespace std

template <typename T>
class disjoint_set {
private:
    unordered_map<T, size_t> set_size;

public:
    /** For internal purpose only. */
    unordered_map<T, T> link;

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

    T& operator[](T);
    disjoint_set<T>& operator+=(const disjoint_set<T>& rhs);
    disjoint_set<T> operator+(const disjoint_set<T>& rhs);
    bool operator==(const disjoint_set<T>& rhs) const;
    bool operator!=(const disjoint_set<T>& rhs) const;

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

#include "dsu.cpp"

#endif
