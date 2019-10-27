/**
 * title: fwt
 * category: 数据结构
 * description: /dev/null
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

long long m;
long long lim[5][5];
long long a[5][5000];
long long b[5][5000] , x[5000] , last[5000];
unsigned long long ans;
void clear () {
	int i;
	for ( i = 0 ; i <= 2048 ; i++ ) {
		a[1][i] = a[2][i] = a[3][i] = 0;
		b[1][i] = b[2][i] = b[3][i] = 0;
		last[i] = x[i] = 0;
	}
	ans = 0;
}
void FWT ( long long *x , long long f ) {
    long long i , j , s , k;
    long long u , t;
    for ( s = 2 ; s <= m ; s = s * 2 ) {
        k = s / 2;
        for ( i = 0 ; i < m ; i += s ) {
            for ( j = 1 ; j <= k ; j++ ) {
                u = x[i+j-1]; t = x[i+j-1+k];
                x[i+j-1] = (u + t);
                x[i+j-1+k] = (u - t);
                if ( f == -1 ) {
                    x[i+j-1] = (x[i+j-1]/2);
                    x[i+j-1+k] = (x[i+j-1+k]/2);
                }
            }
        }
    }
}
long long chk ( long long x , long long lim ) {
	if ( 0 <= x && x <= lim ) return 1;
	return 0;
}
void work () {
	long long i , j , k;
	m = 2048;
	clear ();
	for ( i = 1 ; i <= 2 ; i++ ) {
		for ( j = 1 ; j <= 3 ; j++ ) {
			scanf ( "%lld" , &lim[i][j] );
		}
	}
	for ( i = 0 ; i <= 2000 ; i++ ) {
		for ( j = 1 ; j <= 3 ; j++ ) {
			for ( k = 0 ; k <= lim[1][j] ; k++ ) {
				if ( chk ( k + i , lim[2][j] ) )
					a[j][k^(k+i)]++;
				if ( i != 0 && chk ( k - i , lim[2][j] ) )
					a[j][k^(k-i)]++;
			}
		}
		for ( j = 1 ; j <= 3 ; j++ ) {
			for ( k = 0 ; k <= 2047 ; k++ ) {
				b[j][k] = a[j][k];
			}
		}
		FWT ( b[1] , 1 );
		FWT ( b[2] , 1 );
		FWT ( b[3] , 1 );
		for ( k = 0 ; k <= 2047 ; k++ ) {
			x[k] = b[1][k] * b[2][k] * b[3][k];
		}
		FWT ( x , -1 );
		for ( k = 0 ; k <= 2047 ; k++ ) {
			ans += (k^i)*(x[k]-last[k]);
			last[k] = x[k];
		}
	}
	printf ( "%llu\n" , ans );
}
int main () {
	int t;
	scanf ( "%d" , &t );
	for ( int i = 1 ; i <= t ; i++ ) {
		printf ( "Case #%d: " , i );
		work ();
	}
	return 0;
}

