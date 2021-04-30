/*
Question: 
https://cses.fi/problemset/task/1675

There are n cities and m roads between them. Unfortunately, the condition of the roads is so poor that they cannot be used. Your task is to repair some of the roads so that there will be a decent route between any two cities.

For each road, you know its reparation cost, and you should find a solution where the total cost is as small as possible.

Input:
The first input line has two integers n and m: the number of cities and roads. The cities are numbered 1,2,…,n.

Then, there are m lines describing the roads. Each line has three integers a, b and c: there is a road between cities a and b, and its reparation cost is c. All roads are two-way roads.

Every road is between two different cities, and there is at most one road between two cities.

Output:
Print one integer: the minimum total reparation cost. However, if there are no solutions, print "IMPOSSIBLE".

Constraints:
1≤n≤10^5
1≤m≤2⋅10^5
1≤a,b≤n
1≤c≤10^9
Example

Example:
Input
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4

Output
14
*/

/*
Logic:
Minimum Spanning Tree using Kruskal's Algorithm and Union-Find Structure
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../misc/VariadicTable.h"
#include "../../src/dsu.h"

using namespace std;

constexpr int TEST_CASES = 14;

string solve(int, vector<tuple<int, int, int>>&);

int main() {
    VariadicTable<int, string, string, string> vt({"Test Case No.", "Output", "Expected", "Result"});

    for (int i = 0; i < TEST_CASES; ++i) {
        string input_file_path = "inputs/test_input_" + to_string(i + 1) + ".txt";
        ifstream input_file(input_file_path);

        int n, m;
        input_file >> n >> m;
        vector<tuple<int, int, int>> edges(m);
        for (auto& [a, b, c] : edges) input_file >> a >> b >> c;
        input_file.close();

        string output = solve(n, edges);

        string output_file_path = "outputs/test_output_" + to_string(i + 1) + ".txt";
        ifstream output_file(output_file_path);
        string expected;
        output_file >> expected;

        string result = ((output == expected) ? "PASS" : "FAIL");
        vt.addRow(i + 1, output, expected, result);
    }

    vt.print(cout);
}

string solve(int n, vector<tuple<int, int, int>>& edges) {
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
        return "IMPOSSIBLE";
    else
        return to_string(cost);
}
