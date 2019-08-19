/**
 * rank: 101
 */
#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 5000000

typedef long long i64;

struct UnionFind {
	UnionFind() { memset(fa, 0, sizeof(fa)); }
	int fa[2 * NMAX + 10];
	void clear(int n) { memset(fa + 1, 0, sizeof(int) * n); }
	int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
	int operator[](int x) { return find(x); }
};

#define ACM_BEGIN
#define INF 0x3f3f3f3f
struct Edge { int u, v, w, w0; };
struct Heap {
	Heap(Edge *_e) : e(_e), rk(1), sum(0), lch(NULL), rch(NULL) {}
	Edge *e; int rk, sum;
	Heap *lch, *rch;
	void push() {
		if (lch) lch->sum += sum;
		if (rch) rch->sum += sum;
		e->w += sum; sum = 0;
}};
inline Heap *meld(Heap *x, Heap *y) {
	if (!x) return y;
	if (!y) return x;
	if (x->e->w + x->sum > y->e->w + y->sum)
		swap(x, y);
	x->push();
	x->rch = meld(x->rch, y);
	if (!x->lch || x->lch->rk < x->rch->rk)
		swap(x->lch, x->rch);
	x->rk = x->rch ? x->rch->rk + 1 : 1;
	return x;
}
inline Edge *extract(Heap *&x) {
	Edge *r = x->e;
	x->push();
	x = meld(x->lch, x->rch);
	return r;
}
static vector<Edge> in[NMAX + 10];
static int n, m, fa[2 * NMAX + 10], nxt[2 * NMAX + 10];
static Edge *ed[2 * NMAX + 10];
static Heap *Q[2 * NMAX + 10];
static UnionFind id; // id[] & id.fa
void contract() {
	static bool mark[2 * NMAX + 10];
	//memset(mark + 1, 0, 2 * n);
	//id.clear(2 * n);
	for (int i = 1; i <= n; i++) {
		queue<Heap*> q;
		for (int j = 0; j < in[i].size(); j++)
			q.push(new Heap(&in[i][j]));
		while (q.size() > 1) {
			Heap *u = q.front(); q.pop();
			Heap *v = q.front(); q.pop();
			q.push(meld(u, v));
		} Q[i] = q.front();
	} mark[1] = true;
	for (int u = 1, u0 = 1, p; Q[u]; mark[u0 = u] = true) {
		do u = id[(ed[u] = extract(Q[u]))->u];
		while (u == u0 && Q[u]);
		if (u == u0) break;
		if (!mark[u]) continue;
		for (u0 = u, n++; u != n; u = p) {
			id.fa[u] = fa[u] = n;
			if (Q[u]) Q[u]->sum -= ed[u]->w;
			Q[n] = meld(Q[n], Q[u]);
			p = id[ed[u]->u];
			nxt[p == n ? u0 : p] = u;
}}}
i64 expand(int, int);
i64 _expand(int x) {
	i64 r = 0;
	for (int u = nxt[x]; u != x; u = nxt[u])
		if (ed[u]->w0 >= INF) return INF;
		else r += expand(ed[u]->v, u) + ed[u]->w0;
	return r;
}
i64 expand(int x, int t) {
	i64 r = 0;
	for ( ; x != t; x = fa[x])
		if ((r += _expand(x)) >= INF) return INF;
	return r;
}
#define ACM_END

inline void link(int u, int v, int w) {
	in[v].push_back({u, v, w, w});
}

int main() {
	int rt;
	scanf("%d%d%d", &n, &m, &rt);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		link(u, v, w);
	}
	for (int i = 1; i <= n; i++)  // ensure strong connectivity
		link(i > 1 ? i - 1 : n, i, INF);
#define ACM_BEGIN
//contract();
//i64 ans = expand(rt, n);
#define ACM_END
	contract();
	i64 ans = expand(rt, n);
	if (ans >= INF) puts("-1");
	else printf("%lld\n", ans);
	return 0;
}
