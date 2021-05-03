/* Question : Cycle Detection in Undirected Graph
https://www.geeksforgeeks.org/detect-cycle-undirected-graph/
*/

#include <iostream>
#include<fstream>
#include <unordered_map>
#include<list>
#include<utility>

#include "../../misc/VariadicTable.h"
#include "../../src/dsu.h"

constexpr int TEST_CASES = 4;

template<typename T>
class Graph {
private:
	int vertex{} , edges{};
	list<pair<T , T>> edgeList;
	disjoint_set<T> ds;


public:



	Graph(int e) : edges(e) {}

	void addEdge(T src , T dest) {

		edgeList.push_back(make_pair(src , dest));
		// Initialize each vertex as it own parent in the beginning , only inserting the unique pairs
		ds.insert(src);
		ds.insert(dest);

	}

	string containsCycle() {
		//using the DSU logic to detect if the undirected graph has a cycle or not
		string result{};
		for (auto edge : edgeList) {

			auto s1 = ds.find(edge.first);
			auto s2 = ds.find(edge.second);

			if (!ds.same(s1 , s2)) ds.unite(s1 , s2);
			else return result = "Cycle detected (" + to_string(edge.first) + "->" + to_string(edge.second) + ")";


		}

		return result = "No Cycle detected";



	}



};


int main() {

 VariadicTable<int, string, string, string> vt({"Test Case No.", "Output", "Expected", "Result"});

    for (int i = 0; i < TEST_CASES; ++i) {
        string input_file_path = "inputs/test_input_" + to_string(i + 1) + ".txt";
        ifstream input_file(input_file_path);

        int edges;
        Graph<int> g(edges);
        input_file >>edges; //next n lines represents the edges 
        while(edges--){
        	int src , dest;
        	input_file>> src >>dest;
        	g.addEdge(src , dest);
        }


        input_file.close();

        string output = g.containsCycle();

        string output_file_path = "outputs/test_output_" + to_string(i + 1) + ".txt";
        ifstream output_file(output_file_path);
        string expected;
        getline(output_file , expected);
        
        output_file.close();

        string result = ((output == expected) ? "PASS" : "FAIL");
        vt.addRow(i + 1, output, expected, result);
    }

    vt.print(cout);


}