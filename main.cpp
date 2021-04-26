#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T>
class disjoint_set {
private:
    unordered_map<T, T> link;
    unordered_map<T, size_t> set_size;

public:
    explicit disjoint_set() {
        cout << "Constructor\n";
    }

    void insert(T a) {
        if (link.contains(a) || set_size.contains(a)) {
            cout << "[ERROR] : {add_edge()} - Node already exists" << '\n';
        } else {
            link[a] = a;
            set_size[a] = 1;
        }
    }

    void unite(T a, T b) {
        // Find component representatives.
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (set_size[a] < set_size[b]) swap(a, b);
        set_size[a] += set_size[b];
        link[b] = a;
    }

    // Without path compression
    T find(T a) {
        while (a != link[a]) a = link[a];
        return a;
    }

    // With path compression (TODO: Yet to be tested)
    // T find_fast(T a) {
    //     if (a == link[a])
    //         return a;
    //     else
    //         return link[a] = find_fast(link[a]);  // we set the direct parent to the root of the set to reduce path length.
    // }

    bool same(T a, T b) {
        return find(a) == find(b);
    }

    /** Helper Functions for Debugging **/
    void disp_link() {
        for (auto& [k, v] : link) cout << k << ": " << v << '\n';
        cout << '\n';
    }

    void disp_set_size() {
        for (auto& [k, v] : set_size) cout << k << ": " << v << '\n';
        cout << '\n';
    }
};

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
