/**
 * title: mtt_and_Bernoulli_number
 * category: 数据结构
 * description: mtt_and_Bernoulli_number.md
 */

#include <stdio.h>
#include <algorithm>
#include <math.h>

#define ll long long
#define vi vector <int>
#define vc vector <complex>
#define pb push_back
#define mod 1000000007

using namespace std;

struct complex {
	double x , y;
	complex ():x(0),y(0){}
	complex (const double &_x,const double &_y):x(_x),y(_y){}
};
inline complex operator + (const complex &a ,const complex &b) {return complex(a.x+b.x,a.y+b.y);}
inline complex operator - (const complex &a ,const complex &b) {return complex(a.x-b.x,a.y-b.y);}
inline complex operator * (const complex &a ,const complex &b) {return complex(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);}
inline complex conj ( const complex &a ) {return complex (a.x,-a.y);}

const double pi = acos ( -1 );

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
vi rev;
vc w;
int mx = -1;
void init( int m ) {
	mx = m;
	int N = (1<<m);
	w.resize ( N );
	for ( int i = 0 ; i < N ; i++ ) w[i] = complex (cos(2*pi*i/N),sin(2*pi*i/N));
}
void calr(int m) {
	rev.resize(1 << m);
	if (mx < m) init(m);
	rev[0] = 0;
	for (int j = 0; j < m; j++)
		for (int k = 0; k < (1 << j); k++)
			rev[k | (1 << j)] = rev[k] + (1 << (m - j - 1));
}
void dft(vc& a) {
	int n = a.size(), r = 0; // 保证 a 是 2 幂
	while ((1 << r) < n) r++;
	calr(r);
	for (int i = 0; i < n; i++)
		if (rev[i] > i)
			swap(a[rev[i]], a[i]);
	for (int i = 1,lyc=(1<<mx-1); i < n; i <<= 1,lyc>>=1) {
		for (int j = 0; j < n; j += (i << 1)) {
			for (int k = 0,now=0; k < i; k++) {
				complex mr = a[i + j + k]*w[now];
				a[i + j + k] = a[j + k]-mr;
				a[j + k] = a[j + k]+mr;
				now += lyc;
			}
		}
	}
}
vi operator * (vi a, vi b) {
	int l = a.size() + b.size() - 1 , N;
	if ((ll)a.size() * b.size() < 100) {
		vi fn(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				fn[i + j] = add(fn[i + j], mul(a[i], b[j]));
		return fn;
	}
	int i , r = 0;
	while ((1 << r) < l) r++;
	N = 1<<r;
	a.resize(N), b.resize(N);

	for ( i = 0 ; i < N ; i++ ) (a[i] += mod) %= mod, (b[i] += mod) %= mod;
	vc x(N) , y(N);
	vc dfta(N) , dftb(N) , dftc(N) , dftd(N);

	for(i=0;i<N;i++) x[i] = complex(a[i] & 32767, a[i] >> 15);
	for(i=0;i<N;i++) y[i] = complex(b[i] & 32767, b[i] >> 15);
	dft(x); dft(y);
	for(i=0;i<N;i++) {
		int j = (N - i) & (N - 1);
		static complex da, db, dc, dd;
		da = (x[i] + conj(x[j])) * complex(0.5, 0);
		db = (x[i] - conj(x[j])) * complex(0, -0.5);
		dc = (y[i] + conj(y[j])) * complex(0.5, 0);
		dd = (y[i] - conj(y[j])) * complex(0, -0.5);
		dfta[j] = da * dc;
		dftb[j] = da * dd;
		dftc[j] = db * dc;
		dftd[j] = db * dd;
	}
	for(i=0;i<N;i++) x[i] = dfta[i] + dftb[i] * complex(0, 1);
	for(i=0;i<N;i++) y[i] = dftc[i] + dftd[i] * complex(0, 1);
	dft(x); dft(y);
	for(i=0;i<N;i++)
	{
		int da = (ll)(x[i].x / N + 0.5) % mod;
		int db = (ll)(x[i].y / N + 0.5) % mod;
		int dc = (ll)(y[i].x / N + 0.5) % mod;
		int dd = (ll)(y[i].y / N + 0.5) % mod;
		a[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
	}

	a.resize(l);
	for ( i = 0 ; i < l ; i++ )
		if ( a[i] < 0 ) a[i] += mod;
	return a;
}
vi inv(vi a) {
	int n = a.size() , r=0;
	vi g(1) , h;
	while ((1 << r) < n) r++;
	a.resize ( 1<<r );
	g[0] = power ( a[0] , mod - 2 );
	for ( int i = 2 ; i <= (1<<r) ; i = i * 2 ) {
		h.resize ( i );
		for ( int j = 0 ; j < i ; j++ ) h[j] = a[j];
		h = g * (g*h); g.resize ( i );
		for ( int j = 0 ; j < i ; j++ )
			g[j] = sub ( mul (g[j],2),h[j]);
	}
	g.resize (n);
	for ( int i = 0 ; i < n ; i++ )
		if ( g[i] < 0 ) g[i] += mod;
	return g;
}

vi B;
vi getber ( long long len ) {
	vi ret(len+1);
	ret[0] = 1;
	for ( long long i = 1 ; i <= len ; i++ ) {
		//faster 0.2s by calculating inverses in linear time with len=400000
		ret[i] = (ll)ret[i-1] * power ( i + 1 , mod - 2 ) % mod;
	}
	ret = inv(ret);
	return ret;
}
void predo () {
	B = getber ( 400001 );
}
int main() {
	int t;
	predo ();
	return 0;
}
