/**
 * title: Lagrange polynomial interpolation
 * category: 数学 
 * description: Lagrange_polynomial_interpolation.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

//long long
typedef long long LL;
const LL mod = 998244353;
LL n , m;
LL xx[120000] , yy[120000];
LL ans1 , ans2;
LL ksm ( LL f , LL x ) {
	LL s = 1;
	while ( x ) {
		if ( x % 2 ) s = s * f % mod;
		f = f * f % mod; x = x / 2;
	}
	return s % mod;
}
LL inv ( LL x ) {
	return ksm ( x , mod - 2 );
}
LL lagrange ( LL tot , LL *x , LL *y , LL k ) {
	//cal f(k) s.t. f(x[i])=y[i]
	LL i , j , ret = 0 , tmp , t2;
	k %= mod;
	for ( i = 1 ; i <= tot ; i++ ) {
		tmp = y[i]; t2 = 1;
		for ( j = 1 ; j <= tot ; j++ ) {
			if ( i == j ) continue;
			tmp = tmp * ((k-x[j]+mod)%mod) % mod;
			t2 = t2 * ((x[i]-x[j]+mod)%mod) % mod;
		}
		ret = (ret + tmp * inv ( t2 ) % mod)%mod;
	}
	return ret % mod;
}
LL pre[120000] , suf[120000] , fac[120000] , ifac[120000];
void predo () {
	LL i;
	fac[0] = 1;
	for ( i = 1 ; i <= m + 3 ; i++ ) fac[i] = (fac[i-1]*i) % mod;
	ifac[m+3] = inv ( fac[m+3] );
	for ( i = m + 2 ; i >= 0 ; i-- ) ifac[i] = (ifac[i+1]*(i+1)) % mod;
}
LL lagrange_continuous ( LL tot , LL x , LL *y , LL k ) {
	//cal f(k) s.t. f(x+i-1)=y[i]
	LL i , ret = 0 , tmp;
	pre[0] = 1; suf[tot+1] = 1;
	k %= mod;
	for ( i = 1 ; i <= tot ; i++ ) pre[i] = (pre[i-1] * (k-(x+i-1)%mod+mod)) % mod;
	for ( i = tot ; i >= 1 ; i-- ) suf[i] = (suf[i+1] * (k-(x+i-1)%mod+mod)) % mod;
	for ( i = 1 ; i <= tot ; i++ ) {
		tmp = y[i] * pre[i-1] % mod * suf[i+1] % mod * ifac[i-1] % mod * ifac[tot-i] % mod;
		if ( (tot-i) % 2 == 1 ) tmp = mod - tmp;
		ret = (ret + tmp) % mod;
	}
	return ret % mod;
}
void work () {
	LL i;
	scanf ( "%lld%lld" , &n , &m );
	predo ();
	for ( i = 1 ; i <= m + 2 ; i++ ) {
		xx[i] = i;
		yy[i] = (yy[i-1] + ksm ( i , m )) % mod;
	}
	ans1 = lagrange ( m + 2 , xx , yy , n - 1 );
	for ( i = 1 ; i <= m + 3 ; i++ ) {
		xx[i] = i;
		yy[i] = (yy[i-1] + ksm ( i , m + 1 )) % mod;
	}
	ans2 = lagrange_continuous ( m + 3 , 1 , yy , n - 1 );
	if ( m == 0 ) ans1++;
	printf ( "%lld\n" , ( n - ans2 * inv ( ans1 ) % mod + mod ) % mod );
}
int main () {
	work ();
	return 0;
}

