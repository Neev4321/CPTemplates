#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int cnt;
    vector<int> p, sz;
    DSU(int n) : cnt(n), p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        if (x == p[x])
            return x;
        return p[x] = find(p[x]);
    }
    bool merge(int x, int y){
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        p[y] = x;
        sz[x] += sz[y];
        --cnt;
        return true;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    int comp_sz(int x){
        return sz[find(x)];
    }
};
