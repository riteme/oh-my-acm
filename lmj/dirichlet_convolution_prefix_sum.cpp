/**
 * title: dirichlet_convolution_prefix_sum
 * category: 数论 
 * description: dirichlet_convolution_prefix_sum.md
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

const long long mod = 998244353;
const long long T = 500000;
long long n , m;
long long a[12];
vector < long long > factor[1200000];
long long val[2200000] , rev[2200000] , tot;//val:1,2,...,T,n/x,...,n
long long f[2200000] , sf[2200000];//sf[x]=sum i=1...val[x] f[i]
long long sgn[120] , lcm[120];
void clear () {
	long long i;
	for ( i = 1 ; i <= tot ; i++ ) {
		val[i] = f[i] = sf[i] = 0;
	}
	tot = 0;
}
long long getpos ( long long x ) {
	if ( x <= T ) return x;
	return rev[n/x];
}
void predo () {
	long long i , j , k;
	for ( i = 1 ; i <= T && i <= n ; i++ ) {
		val[++tot] = i;
	}
	if ( T < n ) {
		for ( i = T ; i >= 1 ; i-- ) {
			if ( n / i > T && val[tot] != n / i ) {
				val[++tot] = n / i;
				rev[i] = tot;
			}
		}
	}
	for ( i = 1 ; i <= m ; i++ ) {
		for ( j = a[i] ; j <= T && j <= n ; j += a[i] ) {
			f[j] = 1;
		}
	}
	for ( i = 2 ; i <= T && i <= n ; i++ ) {
		for ( auto j : factor[i] ) {
			if ( j != 1 && j != i ) f[i] = (f[i] + f[j] * f[i/j]) % mod;
		}
	}
	for ( i = 1 ; i <= T && i <= n ; i++ ) {
		sf[i] = (sf[i-1] + f[i]) % mod;
	}
}
long long getsp ( long long x ) {
	long long i , ret = 0;
	for ( i = 1 ; i < (1<<m) ; i++ ) {
		ret = (ret + mod + sgn[i] * (x / lcm[i])) % mod;
	}
	return ret;
}
void work () {
	long long i , j , g;
	scanf ( "%lld%lld" , &n , &m );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%lld" , &a[i] );
	}
	for ( i = 1 ; i < (1<<m) ; i++ ) {
		lcm[i] = 1;
		if ( __builtin_popcount ( i ) % 2 == 1 ) sgn[i] = 1;
		else sgn[i] = -1;
		for ( j = 1 ; j <= m ; j++ ) {
			if ( i & (1<<(j-1)) ) {
				g = __gcd ( lcm[i] , a[j] );
				lcm[i] = lcm[i] / g * a[j];
			}
		}
	}
	predo ();
	if ( n <= T ) {
		printf ( "%lld\n" , sf[n] );
		return ;
	}
	for ( i = T + 1 ; i <= tot ; i++ ) {
		for ( j = 1 ; j * j <= val[i] ; j++ ) {
			sf[i] = (sf[i] + 2*sf[getpos(val[i]/j)]*f[j]) % mod;
		}
		j--;
		sf[i] = (sf[i] + mod - sf[j]*sf[j]%mod) % mod;
		sf[i] = (sf[i] + getsp(val[i])) % mod;
	}
	printf ( "%lld\n" , sf[tot] );
}
int main () {
	int t , i , j;
	scanf ( "%d" , &t );
	for ( i = 1 ; i <= T ; i++ ) {
		for ( j = i ; j <= T ; j += i ) factor[j].push_back ( i );
	}
	while ( t-- ) {
		work ();
		clear ();
	}
	return 0;
}

