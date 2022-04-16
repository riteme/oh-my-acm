/**
 * title: Fiduccia's_algorithm_for_linear_recurrence
 * category: 多项式
 * description: Fiduccia's_algorithm_for_linear_recurrence.md
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
#define ACM_BEGIN
int linear_recurrence ( vi f , vi g , int n , int k ) {
	//f[x] = sigma_{i=1}^k g_{k-i} * f[x-i]
	//return f[n]
	int i , ans;
	vi ret , now;
	g.resize ( k + 1 );
	g[k] = 1;
	for ( i = 0 ; i < k ; i++ ) {
		g[i] = ((-g[i])%mod+mod)%mod;
	}
	ret.resize ( 1 );
	now.resize ( 2 );
	ret[0] = 1;
	now[0] = 0; now[1] = 1;
	while ( n ) {
		if ( n % 2 ) ret = ret * now % g;
		now = now * now % g; n = n / 2;
	}
	ans = 0;
	for ( i = 0 ; i < k ; i++ ) {
		ans = (ans + 1ll*f[i]*ret[i]) % mod;
	}
	return (ans+mod)%mod;
}
void work () {
	int i , n , k , x;
	vi f , g;
	scanf ( "%d%d" , &n , &k );
	g.resize ( k ); f.resize ( k );
	for ( i = 1 ; i <= k ; i++ ) {
		scanf ( "%d" , &x );
		g[k-i] = x;
	}
	for ( i = 1 ; i <= k ; i++ ) {
		scanf ( "%d" , &x );
		f[i-1] = x;
	}
	printf ( "%d\n" , linear_recurrence ( f , g , n , k ) );
}
#define ACM_END
int main() {
	work ();
	return 0;
}
