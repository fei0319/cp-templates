#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>

template <typename T>
struct Inf {
	static T value;
};

template <>
int Inf<int>::value = 1e9;
template <>
long long Inf<long long>::value = 1e18;

template<typename T>
class Flow {
private:
	int s, t, cnt = 1;
	struct edge {
		int next, to;
		T flow;
	};
	int n;
	
	std::vector <T> hd;
	std::vector <edge> e;

	void Add (int u, int v, T w) {
		e[++cnt] = (edge) {hd[u], v, w};
		hd[u] = cnt;
	}
	#define FOR(u) for (int i = hd[u], v; v = e[i]. to, i; i = e[i].next)
	
	T query() {
		
		std::vector <int> dep(n + 1);
		
		std::function <bool()> bfs = [&] () {
			std::queue <int> q;
			std::fill (dep.begin(), dep.end(), 0);
			dep[s] = 1;
			q.push(s);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				FOR(u) {
					if (!e[i].flow || dep[v]) {
						continue;
					}
					dep[v] = dep[u] + 1;
					q.push(v);
				}
			}
			return dep[t] != 0 ? 1 : 0;
		};
		
		std::function <T(int, T)> dfs = [&] (int u, T flow) {
		    if (u == t) return flow;
		    T res = 0;
		    FOR(u) {
		        if (dep[v] != dep[u] + 1 || !e[i].flow)
		            continue;
		        T k = dfs (v, std::min (flow - res, e[i].flow));
		        e[i].flow -= k;
		        e[i ^ 1].flow += k;
		        res += k;
		        if (res == flow) 
		        	return flow;
		    }
		    if (res == 0) dep[u] = 0;
		    return res;
		};
		
		T ans, maxf = 0;
	    while (bfs())
	        while ((ans = dfs(s, Inf<T>::value))) maxf += ans;
	    return maxf;
	}
public:
	Flow (int _n, int m, int _s, int _t) : n(_n), hd(_n + 1), e(m + 1), s(_s), t(_t){};
	void add (int u, int v, T w) {
		Add (u, v, w);
		Add (v, u, 0);
	}
	T max_flow() {
		return query();
	}
};


int main() {
	int n, m, s, t;
	std :: cin >> n >> m >> s >> t;
	Flow <long long> f(n + 1, m * 2 + 1, s, t); 
	for (int i = 1, u, v, w; i <= m; ++i) {
		std::cin >> u >> v >> w;
		f.add(u, v, w);
	}
	std::cout<<f.max_flow()<<'\n';
	return 0;
} 
