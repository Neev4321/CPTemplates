#include <bits/stdc++.h>
using namespace std;

template <typename t>
struct Fenwick {
    vector<t> tree;
    Fenwick(int n) : tree(n + 1) {}
    void point_add(int x, t val){
        for (++x; x < tree.size(); x += x & -x)
            tree[x] += val;
    }
    t range_sum(int x){
        t ans{};
        for (++x; x > 0; x -= x & -x)
            ans += tree[x];
        return ans;
    }
    t range_sum(int l, int r){
        return range_sum(r) - range_sum(l - 1);
    }
    t point_sum(int x){
        return range_sum(x) - range_sum(x - 1);
    }
    int lower_bound(t k){
        int ans = 0;
        t sum{};
        for (int jump = (1 << 30); jump; jump >>= 1){
            int idx = ans + jump;
            if (idx < tree.size() && sum + tree[idx] < k){
                ans = idx;
                sum += tree[idx];
            }
        }
        return ans;
    }
};
