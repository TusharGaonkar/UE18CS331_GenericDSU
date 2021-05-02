/*
Question:
https://www.geeksforgeeks.org/job-sequencing-using-disjoint-set-union/

Given a set of n jobs where each job i has a deadline di >=1 and profit pi>=0. Only one job can be scheduled at a time. Each job takes 1 unit of time to complete. We earn the profit if and only if the job is completed by its deadline. The task is to find the subset of jobs that maximizes profit.

Examples:

Input: Four Jobs with following deadlines and profits
JobID Deadline Profit
   a      4      20
   b      1      10
   c      1      40
   d      1      30
Output: Following is maximum profit sequence of jobs:
       c, a

Input: Five Jobs with following deadlines and profits
JobID Deadline Profit
   a     2       100
   b     1       19
   c     2       27
   d     1       25
   e     3       15
Output: Following is maximum profit sequence of jobs:
       c, a, e
*/

#include <fstream>
#include <iostream>
#include <vector>

#include "../../misc/VariadicTable.h"
#include "../../src/dsu.h"

using namespace std;

constexpr int TEST_CASES = 2;

int get_max_deadline(vector<tuple<char, int, int>> jobs) {
    auto max_deadline = -1;
    for (auto job = 0; job < jobs.size(); job++) {
        auto deadline = get<1>(jobs[job]);
        if (deadline > max_deadline) {
            max_deadline = deadline;
        }
    }
    return max_deadline;
}

string solve(vector<tuple<char, int, int>> jobs) {
    sort(jobs.begin(), jobs.end(), [](auto a, auto b) {
        return get<2>(a) > get<2>(b);
    });
    disjoint_set<int> set;
    for (auto job = 0; job <= get_max_deadline(jobs); job++) {
        set.insert(job);
    }
    string solution;
    for (auto job = 0; job < jobs.size(); job++) {
        auto slot = set.find(get<1>(jobs[job]));
        if (slot > 0) {
            set.merge(set.find(slot - 1), slot);
            solution += get<0>(jobs[job]);
        }
    }
    return solution;
}

int main() {
    VariadicTable<int, string, string, string> table({"Test Case No.", "Output", "Expected", "Result"});
    for (auto i = 0; i < TEST_CASES; ++i) {
        string input_file_path = "inputs/test_input_" + to_string(i + 1) + ".txt";
        ifstream input_file(input_file_path);
        int count;
        input_file >> count;
        vector<tuple<char, int, int>> jobs(count);
        for (auto& [id, deadline, profit] : jobs) input_file >> id >> deadline >> profit;
        input_file.close();
        string output = solve(jobs);
        string output_file_path = "outputs/test_output_" + to_string(i + 1) + ".txt";
        ifstream output_file(output_file_path);
        string expected;
        output_file >> expected;
        string result = output == expected ? "PASS" : "FAIL";
        table.addRow(i + 1, output, expected, result);
    }
    table.print(cout);
}
