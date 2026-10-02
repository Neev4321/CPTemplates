#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T, T INF, bool MIN_QUERY = true>
struct LiChao {
    struct Line {
        T m, b;
        Line(T m = 0, T b = (MIN_QUERY ? INF : -INF)) : m(m), b(b) {}
        T get(T x) const {
            return m * x + b;
        }
    };

    T L, R;
    vector<Line> tree;

    LiChao(T L, T R) : L(L), R(R) {
        tree.resize(4 * (R - L + 1));
    }

    bool better(T a, T b) const {
        if constexpr (MIN_QUERY)
            return a < b;
        else
            return a > b;
    }

    void add_line(Line nw) {
        add_line(1, L, R, nw);
    }

    void add_line(T m, T b) {
        add_line(Line(m, b));
    }

    void add_line(int node, T l, T r, Line nw) {
        T mid = l + (r - l) / 2;

        bool lef = better(nw.get(l), tree[node].get(l));
        bool midb = better(nw.get(mid), tree[node].get(mid));

        if (midb)
            swap(tree[node], nw);

        if (l == r)
            return;

        if (lef != midb)
            add_line(node * 2, l, mid, nw);
        else
            add_line(node * 2 + 1, mid + 1, r, nw);
    }

    T query(T x) const {
        return query(1, L, R, x);
    }

    T query(int node, T l, T r, T x) const {
        T ans = tree[node].get(x);

        if (l == r)
            return ans;

        T mid = l + (r - l) / 2;

        if (x <= mid)
            return best(ans, query(node * 2, l, mid, x));
        else
            return best(ans, query(node * 2 + 1, mid + 1, r, x));
    }

    T best(T a, T b) const {
        return better(a, b) ? a : b;
    }
};
