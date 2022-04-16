/**
 * title: characteristic_polynomial
 * category: สýัง
 * description: characteristic_polynomial.md 
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define vi vector<long long>

const long long mod = 998244353;
long long ksm ( long long f , long long x ) {
	long long s = 1;
	while ( x ) {
		if ( x % 2 == 1 ) s = s * f % mod;
		f = f * f % mod; x = x / 2;
	}
	return s % mod;
}
long long inv ( long long x ) {
	return ksm ( x , mod - 2 );
}
#define ACM_BEGIN
struct matrix {
	long long n , m;
	long long a[310][310];
	void output () {
		int i , j;
		for ( i = 1 ; i <= n ; i++ ) {
			for ( j = 1 ; j <= m ; j++ ) {
				printf ( "%lld " , a[i][j] );
			}
			printf ( "\n" );
		}
	}
	void Hessenberg () {
		long long i , j , k , c;
		//assert ( n == m );
		for ( i = 2 ; i <= n ; i++ ) {
			for ( j = i ; j <= n ; j++ ) {
				if ( a[j][i-1] ) break;
			}
			if ( j == n + 1 ) continue;  
			for ( k = 1 ; k <= n ; k++ ) {
				swap ( a[i][k] , a[j][k] );
			}
			for ( k = 1 ; k <= n ; k++ ) {
				swap ( a[k][i] , a[k][j] );
			}
			for ( j = i + 1 ; j <= n ; j++ ) {
				c = a[j][i-1] * inv ( a[i][i-1] ) % mod;
				for ( k = 1 ; k <= n ; k++ ) {
					a[j][k] = (a[j][k] - c * a[i][k]) % mod;
					if ( a[j][k] < 0 ) a[j][k] += mod;
				}
				for ( k = 1 ; k <= n ; k++ ) {
					a[k][i] = (a[k][i] + c * a[k][j]) % mod;
				}
			}
		}
	}
} x0 , x1;
#define ACM_END
long long n , m , t , a;
long long co;
long long ans;
vi operator + ( vi x1 , vi x2 ) {
	if ( x1.size() < x2.size () ) x1.resize ( x2.size () );
	long long i;
	for ( i = 0 ; i < x2.size () ; i++ ) {
		x1[i] = (x1[i] + x2[i]) % mod;
	}
	return x1;
}
vi operator * ( vi x1 , long long x2 ) {
	long long i;
	for ( i = 0 ; i < x1.size () ; i++ ) {
		x1[i] = (x1[i] * x2) % mod;
	}
	return x1;
}
vi operator * ( vi x1 , vi x2 ) {
	vi y(x1.size()+x2.size()-1);
	long long i , j;
	for ( i = 0 ; i < x1.size () ; i++ )
		for ( j = 0 ; j < x2.size () ; j++ ) {
			y[i+j] = (y[i+j] + x1[i]*x2[j]) % mod;
		}
	return y;
}
long long getsum ( long long a , long long l ) {
	if ( a == 1 ) return l % mod;
	return (ksm(a,l)+mod-1) * inv ( a-1 ) % mod;
}
void gauss () {
	long long i , j , k , c;
	for ( i = 1 ; i <= x1.n ; i++ ) {
		for ( j = i ; j <= x1.n ; j++ ) {
			if ( x1.a[j][i] ) break;
		}
		if ( j == x1.n + 1 ) {
			printf ( "0\n" );
			exit(0);
		}
		for ( k = 1 ; k <= x1.m ; k++ ) {
			if ( j != i ) co = mod-co;
			swap ( x1.a[i][k] , x1.a[j][k] );
			swap ( x0.a[i][k] , x0.a[j][k] );
		}
		for ( j = 1 ; j <= x1.n ; j++ ) {
			if ( j == i ) continue;
			c = x1.a[j][i] * inv ( x1.a[i][i] ) % mod;
			for ( k = 1 ; k <= x1.m ; k++ ) {
				x1.a[j][k] = (x1.a[j][k] - c * x1.a[i][k]) % mod;
				if ( x1.a[j][k] < 0 ) x1.a[j][k] += mod;
				x0.a[j][k] = (x0.a[j][k] - c * x0.a[i][k]) % mod;
				if ( x0.a[j][k] < 0 ) x0.a[j][k] += mod;
			}
		}
	}
	for ( i = 1 ; i <= x1.n ; i++ ) {
		co = co * x1.a[i][i] % mod;
		c = inv ( x1.a[i][i] );
		for ( k = 1 ; k <= x1.m ; k++ ) {
			x0.a[i][k] = x0.a[i][k] * c % mod;
		}
		x1.a[i][i] = 1;
	}
}
#define ACM_BEGIN
vi characteristic_polynomial ( matrix &x ) {
	vi f[310] , tmp;
	long long i , j , c;
	x0.Hessenberg ();
	for ( i = 1 ; i <= x.n ; i++ )
		for ( j = 1 ; j <= x.n ; j++ )
			x.a[i][j] = (mod - x.a[i][j]) % mod;
	f[x.n+1].resize ( 1 );
	f[x.n+1][0] = 1;
	for ( i = x.n ; i >= 1 ; i-- ) {
		tmp.resize (2);
		tmp[0] = x.a[i][i]; tmp[1] = 1;
		f[i] = f[i+1] * tmp;//O(nm) multiplication
		c = 1;
		for ( j = i + 1 ; j <= x.n ; j++ ) {
			c = c * x.a[j][j-1] % mod;
			f[i] = f[i] + f[j+1] * (c*x.a[i][j]%mod*((j-i)%2==0?1:mod-1)%mod);
		}
	}
	return f[1];
}
#define ACM_END
void work () {
	long long i , j , u , v , a1 , b1 , a2 , b2;
	vi tmp;
	scanf ( "%lld%lld%lld%lld" , &n , &m , &t , &a );
	x0.n = x0.m = x1.n = x1.m = n - 1;
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%lld%lld%lld%lld%lld%lld" , &u , &v , &a1 , &b1 , &a2 , &b2 );
		a1 = a1 * inv ( b1 ) % mod;
		a2 = a2 * inv ( b2 ) % mod;
		x0.a[u][u] = (x0.a[u][u] + a2) % mod;
		x0.a[v][v] = (x0.a[v][v] + a2) % mod;
		x0.a[u][v] = (x0.a[u][v] + mod - a2) % mod;
		x0.a[v][u] = (x0.a[v][u] + mod - a2) % mod;
		a1 = (a1+mod-a2) % mod;
		x1.a[u][u] = (x1.a[u][u] + a1) % mod;
		x1.a[v][v] = (x1.a[v][v] + a1) % mod;
		x1.a[u][v] = (x1.a[u][v] + mod - a1) % mod;
		x1.a[v][u] = (x1.a[v][u] + mod - a1) % mod;
	}
	if ( m == 0 ) {
		printf ( "0\n" );
		exit(0);
	}
	co = 1;
	gauss ();
	//x0.output ();
	//x1.output ();
	//printf ( "%lld\n" , co );
	for ( i = 1 ; i <= n - 1 ; i++ ) {
		for ( j = 1 ; j <= n - 1 ; j++ ) {
			x0.a[i][j] = (mod-x0.a[i][j]) % mod;
		}
	}
	tmp = characteristic_polynomial ( x0 );
	ans = 0;
	for ( i = 0 ; i < tmp.size () ; i++ ) {
		tmp[i] = (tmp[i] * co) % mod;
		//printf ( "%lld " , tmp[i] );
		ans = (ans + tmp[i] * getsum ( ksm ( inv(a) , i ) , t )) % mod;
	}
	printf ( "%lld\n" , ans );
}
int main () {
	//freopen ( "b.in" , "r" , stdin );
	work ();
	return 0;
}

