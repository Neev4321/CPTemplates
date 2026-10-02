#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename t, t ID, auto merge>
struct Segtree {
    int sz;
    vector<t> tree;
    Segtree(int n) : sz(bit_ceil<unsigned int>(n)), tree(2 * sz, ID) {}
    Segtree(const vector<t> &a) : sz(bit_ceil(a.size())), tree(2 * sz, ID){
        for (int i = 0; i < a.size(); ++i)
            tree[sz + i] = a[i];
        for (int i = sz - 1; i > 0; --i)
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }
    void point_update(int idx, t val){
        idx += sz;
        tree[idx] = val;
        for (idx >>= 1; idx; idx >>= 1)
            tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }
    t range_query(int l, int r){
        t ans1 = ID, ans2 = ID;
        for (l += sz, r += sz; l <= r; l >>= 1, r >>= 1){
            if (l & 1)
                ans1 = merge(ans1, tree[l++]);
            if (!(r & 1))
                ans2 = merge(tree[r--], ans2);
        }
        return merge(ans1, ans2);
    }
    t point_query(int idx){
        return tree[sz + idx];
    }
};
ll sum_merge(ll a, ll b) {return a + b;}
ll min_merge(ll a, ll b) {return min(a, b);}
ll max_merge(ll a, ll b) {return max(a, b);}
ll gcd_merge(ll a, ll b) {return gcd(a, b);}
using SumSegtree = Segtree<ll, 0ll, sum_merge>;
using MinSegtree = Segtree<ll, LLONG_MAX, min_merge>;
using MaxSegtree = Segtree<ll, LLONG_MIN, max_merge>;
using GcdSegtree = Segtree<ll, 0ll, gcd_merge>;

template <typename t, t ID, auto merge, auto apply, auto compose>
struct LazySegtree {
    int sz;
    vector<t> tree, lazy;
    vector<bool> is_lazy;
    LazySegtree(int n) : sz(bit_ceil<unsigned int>(n)), tree(2 * sz, ID), lazy(2 * sz, ID), is_lazy(2 * sz, false){}
    LazySegtree(const vector<t> &a) : sz(bit_ceil(a.size())), tree(2 * sz, ID), lazy(2 * sz, ID), is_lazy(2 * sz, false){
        for (int i = 0; i < a.size(); ++i)
            tree[sz + i] = a[i];
        for (int i = sz - 1; i > 0; --i)
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }
    void apply_node(int node, int l, int r, t upd){
        tree[node] = apply(tree[node], upd, r - l + 1);
        if (is_lazy[node]){
            lazy[node] = compose(lazy[node], upd);
        } else{
            is_lazy[node] = true;
            lazy[node] = upd;
        }
    }
    void propogate(int node, int l, int r){
        if (!is_lazy[node])
            return;
        int mid = (l + r) / 2;
        apply_node(node * 2, l, mid, lazy[node]);
        apply_node(node * 2 + 1, mid + 1, r, lazy[node]);
        is_lazy[node] = false;
    }
    void range_update(int node, int l, int r, int ql, int qr, t upd){
        if (l > qr || r < ql)
            return;
        if (l >= ql && r <= qr)
            return apply_node(node, l, r, upd);
        propogate(node, l, r);
        int mid = (l + r) / 2;
        range_update(node * 2, l, mid, ql, qr, upd);
        range_update(node * 2 + 1, mid + 1, r, ql, qr, upd);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    void range_update(int l, int r, t upd){
        range_update(1, 0, sz - 1, l, r, upd);
    }
    t range_query(int node, int l, int r, int ql, int qr){
        if (l > qr || r < ql)
            return ID;
        if (l >= ql && r <= qr)
            return tree[node];
        propogate(node, l, r);
        int mid = (l + r) / 2;
        return merge(
            range_query(node * 2, l, mid, ql, qr),
            range_query(node * 2 + 1, mid + 1, r, ql, qr)
        );
    }
    t range_query(int l, int r){
        return range_query(1, 0, sz - 1, l, r);
    }
};
ll add_apply(ll val, ll upd, int len) {return val + upd * len;}
ll add_extreme_apply(ll val, ll upd, int len) {return val + upd;}
ll add_compose(ll old, ll del) {return old + del;}
ll set_apply(ll val, ll upd, int len) {return upd;}
ll set_sum_apply(ll val, ll upd, int len) {return upd * len;}
ll set_compose(ll old, ll del) {return del;}
ll min_apply(ll val, ll upd, int len) {return min(val, upd); }
ll min_compose(ll old, ll del) {return min(old, del);}
ll max_apply(ll val, ll upd, int len) {return max(val, upd); }
ll max_compose(ll old, ll del) {return max(old, del);}
using AddSumLazytree = LazySegtree<ll, 0ll, sum_merge, add_apply, add_compose>;
using SetSumLazytree = LazySegtree<ll, 0ll, sum_merge, set_sum_apply, set_compose>;
using AddMinLazytree = LazySegtree<ll, LLONG_MAX, min_merge, add_extreme_apply, add_compose>;
using AddMaxLazytree = LazySegtree<ll, LLONG_MIN, max_merge, add_extreme_apply, add_compose>;
using SetMinLazytree = LazySegtree<ll, LLONG_MAX, min_merge, set_apply, set_compose>;
using SetMaxLazytree = LazySegtree<ll, LLONG_MIN, max_merge, set_apply, set_compose>;
using CHminLazytree = LazySegtree<ll, LLONG_MAX, min_merge, min_apply, min_compose>;
using CHmaxLazytree = LazySegtree<ll, LLONG_MIN, max_merge, max_apply, max_compose>;
