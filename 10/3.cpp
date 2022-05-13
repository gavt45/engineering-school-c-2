//
// Created by gav on 12/05/2021.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define dst(a, b, coords) sqrt((coords[b].first - coords[a].first)*(coords[b].first - coords[a].first) + \
                                (coords[b].second - coords[a].second)*(coords[b].second - coords[a].second))

int main() {
    // входные данные
    int n, a, b, m;
    double l;

    cin >> n;

    vector< pair<double, double> > coords;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        coords.push_back(make_pair(a, b));
    }

    int k;
    cin >> k;

    vector< vector<int> > bad(n, vector<int>());

    for (int i = 0; i < k; ++i) {
        cin >> a >> b;
        a--; b--;
        bad[min(a, b)].push_back(max(a, b));
    }

//    m = n*(n-1)/2 - k;
    vector<pair<double, pair<int, int> > > g; // вес - вершина 1 - вершина 2

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (i != j && find(bad[i].begin(), bad[i].end(), j) == bad[i].end())
                g.push_back(make_pair(dst(i, j, coords), make_pair(i, j)));

    m = g.size();

    double cost = 0;
    vector< pair<int, int> > res;

    sort(g.begin(), g.end());

    vector<int> tree_id(n);

    for (int i = 0; i < n; ++i)
        tree_id[i] = i;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < bad[i].size(); ++j)
            tree_id[bad[i][j]] = tree_id[i];

    for (int i = 0; i < m; ++i) {
        a = g[i].second.first;
        b = g[i].second.second;
        l = g[i].first;
        if (tree_id[a] != tree_id[b]) {
            cost += l;
            res.push_back(make_pair(a, b));
            int old_id = tree_id[b], new_id = tree_id[a];
            for (int j = 0; j < n; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }

    for (int i = 0; i < res.size(); ++i)
        cout << res[i].first + 1 << " " << res[i].second + 1 << endl;

    return 0;
}
