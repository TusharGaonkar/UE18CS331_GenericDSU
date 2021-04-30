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

    // Copy constructor demo.
    auto copy1 = ds;
    auto copy2 = disjoint_set(ds);
    copy1.insert("five");
    copy2.insert("six");
    cout << '\n';
    ds.disp_link();
    copy1.disp_link();
    copy2.disp_link();

    return 0;
}
