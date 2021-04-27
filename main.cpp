#include <iostream>
#include <string>
#include <vector>

#include "src/dsu.h"

using namespace std;

int main() {
    vector<string> nodes = {"one", "two", "three", "four"};
    disjoint_set<string> ds;
    for (string& n : nodes) ds.insert(n);

    ds.unite("one", "three");
    ds.unite("four", "two");

    // ds.disp_link();
    // ds.disp_set_size();

    cout << boolalpha;

    cout << ds.same("one", "two") << '\n';
    cout << ds.same("one", "three") << '\n';
    return 0;
}
