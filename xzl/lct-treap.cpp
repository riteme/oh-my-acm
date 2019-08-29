/**
 * title: Link-Cut Tree (treap)
 * category: 数据结构
 * description: lct-treap.md
 * rank: 998244354
 */

/**
 * Weighted treap
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <random>
#include <algorithm>

//#include "lct.h"

using std::swap;


// inline int mrand(int n) {
//     static struct Init {
//         Init() {
//             std::random_device rd;
//             srand(rd());
//         }
//     } init;
//     assert(n);
//     return rand() % n;
// }

inline int mrand(int n) {
	static struct Init {
		unsigned int a;
		Init() {
			std::random_device rd;
			a = rd();
		}
	} dat;
	dat.a ^= dat.a << 13;
	dat.a ^= dat.a >> 17;
	dat.a ^= dat.a << 5;
	assert(n);
	return dat.a % n;
}

#define NMAX 100

#define ACM_BEGIN
#define STACKSIZE 64
static struct Node {
	int val, mx, pos; //optional
	int wt, size, fa, lch, rch; bool rev;
} m[NMAX + 1];
inline void push(int x) {
	if (m[x].rev) {
		swap(m[x].lch, m[x].rch);
		m[m[x].lch].rev ^= 1;
		m[m[x].rch].rev ^= 1;
		m[x].rev = 0;
}}
inline auto update(int x) -> int { /*...*/; return x; }
static auto join2(int x, int y) -> int {
	if (!x) return y;
	if (!y) return x;
	int w = mrand(m[x].size + m[y].size);
	if (w < m[x].size) {
		push(x);
		m[x].rch = join2(m[x].rch, y);
		m[m[x].rch].fa = x;
		return update(x);
	}
	push(y);
	m[y].lch = join2(x, m[y].lch);
	m[m[y].lch].fa = y;
	return update(y);
}
static auto join(int x, int u, int y) -> int {
	if (!x && !y) return u;
	int w = mrand(m[x].size + m[u].wt + m[y].size);
	if (w < m[x].size) {
		push(x);
		m[x].rch = join(m[x].rch, u, y);
		m[m[x].rch].fa = x;
		return update(x);
	} else if (w >= m[x].size + m[u].wt) {
		push(y);
		m[y].lch = join(x, u, m[y].lch);
		m[m[y].lch].fa = y;
		return update(y);
	}
	m[u].lch = x;
	m[u].rch = y;
	m[x].fa = m[y].fa = u;
	return update(u);
}
struct Triple { int l, r, p; };
static auto split(int x) -> Triple {
	static int stk[STACKSIZE], tail = 0, y = x;
	do {
		stk[tail++] = y;
		y = m[y].fa;
	} while (y > 0);
	for (int i = tail - 1; i >= 0; i--) push(stk[i]);
	int l = m[x].lch, r = m[x].rch, t = m[stk[tail - 1]].fa;
	for (int i = 1; i < tail; i++) {
		int u = stk[i];
		if (stk[i - 1] == m[u].lch) {
			m[u].lch = r;
			r = m[r].fa = u;
		} else {
			m[u].rch = l;
			l = m[l].fa = u;
		} update(u);
	}
	m[l].fa = m[r].fa = m[x].lch = m[x].rch = m[x].fa = 0;
	//m[x].size = m[x].wt;
	m[x].mx = m[x].val;
	m[x].pos = x;
	return {l, r, t};
}
#define REWEIGHT(x, d) \
	m[x].wt += d; \
	m[x].size = m[x].wt;
inline void reweight(int x, int d) {
	auto t = split(x);
	REWEIGHT(x, d);
	x = join(t.l, x, t.r);
	m[x].fa = t.p;
}
auto splice(int x) -> int {
	int p = -m[x].fa;
	auto t = split(p);
	m[t.r].fa = -p;
	REWEIGHT(p, m[t.r].size - m[x].size);
	x = join(t.l, p, x);
	m[x].fa = t.p;
	return x;
}
void expose(int x) {
	auto t = split(x);
	m[t.r].fa = -x;
	REWEIGHT(x, m[t.r].size);
	x = join2(t.l, x);
	m[x].fa = t.p;
	while (m[x].fa) x = splice(x);
}
void link(int x, int y) {
	while (m[y].fa > 0) y = m[y].fa;
	expose(x);
	m[y].fa = -x;
	reweight(x, m[y].size);
	//expose(y);
}
void fastcut(int x) {
	while (m[x].fa > 0) x = m[x].fa;
	if (m[x].fa) reweight(-m[x].fa, -m[x].size);
	m[x].fa = 0;
}
void cut(int x) {
	expose(x);
	split(x);
	m[x].size = m[x].wt;
}
void evert(int x) {
	expose(x);
	while (m[x].fa) x = m[x].fa;
	m[x].rev ^= 1;
}
#define ACM_END

void set(int x, int v) {
	m[x].val = v;
	if (v > m[x].mx) {
		m[x].mx = v;
		m[x].pos = x;
	}
	while (m[x].fa > 0) {
		int p = m[x].fa;
		//chkmax(m[p], m[x]);
		x = p;
	}
}

auto query(int x, int y) -> int {
	evert(x);
	expose(y);
	while (m[x].fa) x = m[x].fa;
	while (m[y].fa) y = m[y].fa;
	return x != y ? 0 : m[x].pos;
}

auto get(int x) -> int {
	return m[x].val;
}
