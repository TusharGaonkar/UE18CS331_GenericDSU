/*
Question: 
https://cses.fi/problemset/task/1675
*/

/*
Logic:
Minimum Spanning Tree using Kruskal's Algorithm and Union-Find Structure
*/

#include <algorithm>
#include <iostream>
#include <vector>

#include "dsu.h"

using namespace std;

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges(m);

    for (auto& [a, b, c] : edges) cin >> a >> b >> c;
    sort(edges.begin(), edges.end(), [](auto a, auto b) {
        return get<2>(a) < get<2>(b);
    });

    disjoint_set<int> ds;
    for (int i = 1; i <= n; ++i) ds.insert(i);

    long long cost = 0;
    int numOfEdgesAdded = 0;
    for (auto [a, b, c] : edges) {
        if (!ds.same(a, b)) cost += c, ++numOfEdgesAdded, ds.unite(a, b);
    }

    if (numOfEdgesAdded != n - 1)
        cout << "IMPOSSIBLE" << '\n';
    else
        cout << cost << '\n';
}
