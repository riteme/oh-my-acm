/**
 * title: Link-Cut Tree (splay)
 * category: 数据结构
 * rank: 998244353
 * description: lct-splay.md
 */

/**
 * Simplified splay tree, c approx 3.16+
 */

#include <cassert>

#include <algorithm>

//#include "lct.h"

using std::swap;

#define NMAX 100
#define ACM_BEGIN
static struct Node {
	int w, sum; //optional
	int fa, lch, rch; bool rev;
} m[NMAX + 1];
inline void push(int x) {
	if (m[x].rev) {
		swap(m[x].lch, m[x].rch);
		m[m[x].lch].rev ^= 1;
		m[m[x].rch].rev ^= 1;
		m[x].rev = 0;
}}
inline void pull(int x) { m[x].sum = m[x].w + m[m[x].lch].sum + m[m[x].rch].sum; }
#define ROT(name, lch, rch) \
inline void name(int x) { \
	int y = m[x].lch; \
	m[m[y].rch].fa = x; \
	m[x].lch = m[y].rch; \
	m[y].rch = x; \
	if (m[x].fa > 0) { \
		int p = m[x].fa; \
		if (m[p].lch == x) m[p].lch = y; \
		else m[p].rch = y; \
	} \
	m[y].fa = m[x].fa; \
	m[x].fa = y; \
	/*m[y].sum = m[x].sum; */ \
	pull(x); \
	pull(y); \
}
ROT(lrot, lch, rch)
ROT(rrot, lch, rch)
inline void access(int x) {
	if (m[x].fa > 0) access(m[x].fa);
	push(x);
}
inline void splay(int x, bool ac = false) {
	if (!ac) access(x);
	while (m[x].fa > 0) {
		int p = m[x].fa, p2 = m[p].fa;
		if (p2 > 0) {
			if (m[p].lch == x && m[p2].lch == p) lrot(p2);
			else if (m[p].rch == x && m[p2].rch == p) rrot(p2);
		}
		if (m[p].lch == x) lrot(p);
		else rrot(p);
}}
auto splice(int x) -> int {
	int p = -m[x].fa;
	splay(p);
	m[m[p].rch].fa = -p;
	m[p].rch = x;
	m[x].fa = p;
	pull(p);
	return p;
}
void expose(int x) {
	splay(x);
	m[m[x].rch].fa = -x;
	m[x].rch = 0;
	pull(x);
	while (m[x].fa) x = splice(x);
}
void link(int x, int y) {
	splay(y);
	m[y].fa = -x;
	//expose(y);
}
void fastcut(int x) {
	splay(x); //假定父亲已被 expose
	m[x].fa = 0;
}
void cut(int x) {
	expose(x);
	splay(x);
	int y = m[x].lch;
	if (!y) return;
	push(y);
	while (m[y].rch) {
		y = m[y].rch;
		push(y);
	}
	splay(y, true);
	m[m[y].rch].fa = 0;
	m[y].rch = 0;
	pull(y);
}
void evert(int x) {
	expose(x);
	splay(x);
	m[x].rev ^= 1;
}
#define ACM_END

void set(int x, int v) {
	splay(x);
	m[x].sum += v - m[x].w;
	m[x].w = v;
}

void toggle(int x) {
	splay(x);
	m[x].sum += m[x].w ? 1 : -1;
	m[x].w ^= 1;
}

auto count(int x, int y) -> int {
	if (x == y) return 0;
	if (x < y) swap(x, y);
	expose(x);
	expose(y);
	splay(x);
	int r = m[x].sum;
	if (m[x].fa != -y) {
		expose(-m[x].fa);
		splay(y);
		r += m[y].sum;
	}
	return r;
}
