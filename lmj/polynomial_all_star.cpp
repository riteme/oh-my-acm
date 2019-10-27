/**
 * title: polynomial_all_star
 * category: 多项式
 * description: /dev/null
 */
#include <bits/stdc++.h>
#define ll long long
#define vi vector <int>
#define pb push_back
#define mod 998244353
using namespace std;
inline int add(int a, int b) {
	a += b;
	return (a < mod) ? a : (a - mod);
}
inline int sub(int a, int b) {
	a -= b;
	return (a < 0) ? a + mod : a;
}
inline int mul(int a, int b) {
	return (ll)a * b % mod;
}
int power(int a, int b) {
	if (!b) return 1;
	int u = power(a, b >> 1);
	u = mul(u, u);
	if (b & 1) u = mul(u, a);
	return u;
}
vi rev, roots;
int mx = -1;
void init() {
	mx = 23;
	roots.resize(1 << mx);
	for (int j = 1; j <= mx; j++) {
		int mn = power(3, (mod - 1) >> j);
		for (int i = 0; i < (1 << (j - 1)); i++) {
			int npl = (1 << (j - 1)) | i;
			if (i == 0) roots[npl] = 1;
			else roots[npl] = mul(mn, roots[npl - 1]); 
		}
	}
}
void calr(int m) {
	rev.resize(1 << m);
	if (mx == -1) init();
	rev[0] = 0;
	for (int j = 0; j < m; j++)
		for (int k = 0; k < (1 << j); k++) 
			rev[k | (1 << j)] = rev[k] + (1 << (m - j - 1));
}
void dft(vi& a) {
	int n = a.size(), r = 0; // 保证 a 是 2 幂 
	while ((1 << r) < n) r++;
	calr(r);
	for (int i = 0; i < n; i++)
		if (rev[i] > i)
			swap(a[rev[i]], a[i]);
	for (int i = 1; i < n; i <<= 1) {
		for (int j = 0; j < n; j += (i << 1)) {
			for (int k = 0; k < i; k++) {
				int mr = mul(a[i + j + k], roots[i + k]);
				a[i + j + k] = sub(a[j + k], mr);
				a[j + k] = add(a[j + k], mr);
			}
		}
	}
}
vi operator * (vi a, vi b) {
	int l = a.size() + b.size() - 1;
	if ((ll)a.size() * b.size() < 100) {
		vi fn(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				fn[i + j] = add(fn[i + j], mul(a[i], b[j]));
		return fn;
	}
	int r = 0;
	while ((1 << r) < l) r++;
	a.resize(1 << r), b.resize(1 << r);
	dft(a);
	dft(b);
	int bk = power(1 << r, mod - 2);
	for (int i = 0; i < (1 << r); i++)
		a[i] = mul(mul(a[i], b[i]), bk);
	reverse(a.begin() + 1, a.end());
	dft(a);
	a.resize(l);
	return a;
}
vi inv(vi a) {
	int n = a.size(), m = (n + 1) >> 1;
	if (n == 1)
		return vi(1, power(a[0], mod - 2));
	vi k = inv(vi(a.begin(), a.begin() + m));
	int r = 0;
	while ((1 << r) < (2 * n)) r++;
	int sz = (1 << r), inv_sz = power(sz, mod - 2);
	calr(r);
	a.resize(sz), k.resize(sz);
	dft(a), dft(k);
	for (int i = 0; i < sz; i++)
		k[i] = mul(k[i], sub(2, mul(a[i], k[i])));
	reverse(k.begin() + 1, k.end());
	dft(k);
	for (int i = 0; i < sz; i++)
		k[i] = mul(k[i], inv_sz);
	k.resize(n);
	return k;
} 
void otp(vi a) {
	for (int i = 0; i < a.size(); i++)
		printf("%d ", a[i]);
	printf("\n");
}
vi operator / (vi a, vi b) {
	int n = a.size(), m = b.size();
	if (n < m) return vi(1, 0);
	reverse(a.begin(), a.end()), 
	reverse(b.begin(), b.end());
	a.resize(n - m + 1);
	b.resize(n - m + 1);
	a = a * inv(b);
	a.resize(n - m + 1);
	reverse(a.begin(), a.end());
	return a; 
} 
vi operator - (vi a, vi b) {
	if (a.size() < b.size())
		a.resize(b.size());
	for (int i = 0; i < b.size(); i++)
		a[i] = sub(a[i], b[i]);
	return a;
}
vi operator + (vi a, vi b) {
	if (a.size() < b.size())
		a.resize(b.size());
	for (int i = 0; i < b.size(); i++)
		a[i] = add(a[i], b[i]);
	return a;
}
vi operator % (vi a, vi b) {
	vi f = a - b * (a / b);
	f.resize(b.size() - 1);
	return f;
}
vi dw(vi f) {
	//求导
	int n = f.size();
	if (n == 1) return vi{0};
	vi g(n - 1);
	for (int i = 0; i < n - 1; i++) 
		g[i] = mul(f[i + 1], (i + 1));
	return g;
} 
vi bk; // reverse 
vi up(vi f) {
	//积分 
	int n = f.size();
	vi g(n + 1);
	if (bk.size() <= n) {
		int ur = bk.size();
		bk.resize(n + 1);
		for (int i = max(ur, 1); i <= n; i++) {
			if (i == 1) bk[i] = 1;
			else bk[i] = mul(mod / i + 1, bk[mul(i, mod / i + 1)]);
		//	if (mul(i, bk[i]) != 1) cout << "WAAA" << endl;
		}
	} 
	for (int i = 1; i <= n; i++)
		g[i] = mul(f[i - 1], bk[i]);
	return g;
}
vi caly(vi f, vi x) {
	//多点求值
	int n = x.size();
	vector <vi> mt(2 * n);
	for (int i = 0; i < n; i++) {
		mt[i + n].resize(2);
		mt[i + n][0] = sub(0, x[i]), mt[i + n][1] = 1;
	//	cout << mt[i + n].size() << endl;
	}
	for (int i = n - 1; i >= 1; i--)
		mt[i] = mt[i * 2] * mt[i * 2 + 1];
	vector <vi> nf(2 * n);
	nf[1] = f % mt[1];
	for (int i = 2; i < 2 * n; i++)
		nf[i] = nf[i / 2] % mt[i];
	vi y(n);
	for (int i = 0; i < n; i++)
		y[i] = nf[i + n][0];
	return y;  
} 
vi calf(vi x, vi y) {
	//插值
	int n = x.size();
	vector <vi> mt(2 * n);
	for (int i = 0; i < n; i++) {
		mt[i + n].resize(2);
		mt[i + n][0] = sub(0, x[i]), mt[i + n][1] = 1;
	}
	for (int i = n - 1; i >= 1; i--)
		mt[i] = mt[i * 2] * mt[i * 2 + 1];
	vi u = dw(mt[1]), v = caly(u, x);
	vector <vi> sm(2 * n);
	for (int i = 0; i < n; i++)
		sm[i + n] = vi(1, mul(y[i], power(v[i], mod - 2)));
	for (int i = n - 1; i >= 1; i--)
		sm[i] = mt[i * 2 + 1] * sm[i * 2] + mt[i * 2] * sm[i * 2 + 1];
	return sm[1]; 
}
vi ln(vi x) {
	// 保证 x[0] = 1
	int n = x.size();
	vi t = up(dw(x) * inv(x));
	t.resize(n);
	return t;
}
vi exp(vi f) {
	vi x = vi(1, 1);
	while (x.size() < f.size()) {
		int er = min(x.size() * 2, f.size());
		vi q = x, r = vi(f.begin(), f.begin() + er);
		r[0] = add(r[0], 1);
		x.resize(er);
		r = r - ln(x);
		r = r * q;
		r.resize(x.size()), x = r;
	}
	return x;
}
vi ez_pow(vi f, int b) {
	f = ln(f);
	for (int j = 0; j < f.size(); j++)
		f[j] = mul(f[j], b);
	return exp(f);
}
vi power(vi f, int b) {
	// b > mod 且常数项不是1 时需要改动 (把int 改成ll ,因为b只能对mod * (mod - 1) 取模） 
	int pl = f.size();
	for (int j = 0; j < f.size(); j++) 
		if (f[j]) {
			pl = j;
			break;
		}
	if (1ll * b * pl >= f.size()) return vi(f.size(), 0);
	int mv = b * pl, mt = power(f[pl], mod - 2), ca = power(f[pl], b);
	vi g = vi(f.begin() + pl, f.end());
	for (int j = 0; j < g.size(); j++)
		g[j] = mul(g[j], mt);
	g = ez_pow(g, b);
	vi fn(f.size());
	for (int j = 0; j < f.size(); j++)
		if (j < mv) fn[j] = 0;
		else fn[j] = mul(ca, g[j - mv]);
	return fn;
}
int main() {
	return 0;
}
