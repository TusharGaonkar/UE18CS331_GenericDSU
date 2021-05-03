/*
Question: 
Given a graph, find the number of connected components in it.

Input:
The first input line has two integers n and m: the number of nodes and the number of edges.

Then, there are m lines describing the edges. Each line has two integers a and b: there is an edge between nodes a and b. All edges are undirected.


Input:
6 4
1 2
2 3
6 4
3 1

Output:
3
*/

/*
Logic:
Count the number of connected components using the DSU data structure. 
*/

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../../misc/VariadicTable.h"
#include "../../src/dsu.h"

using namespace std;

constexpr int TEST_CASES = 4;

string solve(int, vector<pair<int, int>>&);

int main() {
    VariadicTable<int, string, string, string> vt({"Test Case No.", "Output", "Expected", "Result"});

    for (int i = 0; i < TEST_CASES; ++i) {
        string input_file_path = "inputs/test_input_" + to_string(i + 1) + ".txt";
        ifstream input_file(input_file_path);

        int n, m;
        input_file >> n >> m;
        vector<pair<int, int>> edges(m);
        for (auto& e : edges) input_file >> e.first >> e.second;
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

string solve(int n, vector<pair<int, int>>& edges) {
    int m = (int)edges.size();

    disjoint_set<int> ds;
    for (int i = 1; i <= n; ++i) ds.insert(i);

    for (auto [a, b] : edges) {
        if (!ds.same(a, b)) ds.unite(a, b);
    }

    set<int> s;
    for (int i = 1; i <= n; ++i) s.insert(ds.find(i));

    return to_string(s.size());
}