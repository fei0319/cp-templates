#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

template <typename T>
struct Inf {
    static T value;
};

template <>
int Inf<int>::value = 1e9;
template <>
long long Inf<long long>::value = 1e18;

template <typename T>
class Flow {
private:
    int s, t, cnt = 1;
    struct edge {
        int next, to;
        T flow, cost;
    };
    int n;

    std::vector<T> hd;
    std::vector<edge> e;

    void Add(int u, int v, T w, T c) {
        e[++cnt] = (edge){hd[u], v, w, c};
        hd[u] = cnt;
    }
#define FOR(u) for (int i = hd[u], v; v = e[i].to, i; i = e[i].next)

    std::pair<T, T> ek() {
        std::vector<bool> vis(n + 1);
        std::vector<T> dis(n + 1), f(n + 1);
        std::vector<int> pre(n + 1);

        auto spfa = [&]() {
            for (int i = 1; i <= t; ++i)
                vis[i] = 0, dis[i] = Inf<T>::value;
            std::queue<int> q;
            q.push(s);
            vis[s] = 1;
            dis[s] = 0;
            pre[t] = -1;
            f[s] = Inf<T>::value;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                vis[u] = 0;
                FOR(u) {
                    if (!e[i].flow)
                        continue;
                    if (dis[v] > dis[u] + e[i].cost) {
                        dis[v] = dis[u] + e[i].cost;
                        f[v] = std::min(f[u], e[i].flow);
                        pre[v] = i;
                        if (!vis[v])
                            vis[v] = 1, q.push(v);
                    }
                }
            }
            return pre[t] == -1 ? -1 : f[t];
        };
        int maxf, minc;
        int u, in, i;
        maxf = 0, minc = 0;
        while ((in = spfa()) != -1) {
            u = t;
            while (u != s) {
                i = pre[u];
                e[i].flow -= in;
                e[i ^ 1].flow += in;
                u = e[i ^ 1].to;
            }
            maxf += in;
            minc += in * dis[t];
        }
        return std::make_pair(maxf, minc);
    }

public:
    Flow(int _n, int m, int _s, int _t)
        : n(_n), hd(_n + 1), e(m + 1), s(_s), t(_t){};
    void add(int u, int v, T w, T c) {
        Add(u, v, w, c);
        Add(v, u, 0LL, -c);
    }
    void mincost() {
        std::pair<T, T> x = ek();
        std::cout << x.first << " " << x.second << '\n';
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Flow<long long> fl(n, m * 2 + 1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int u, v, f, c;
        std::cin >> u >> v >> f >> c;
        fl.add(u, v, f, c);
    }
    fl.mincost();
    return 0;
}
