/**
 * title: Josephus_problem
 * category: 常识 
 * description: Josephus_problem.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

long long n , m , k;
void work () {
	long long i , x , t;
	scanf ( "%lld%lld%lld" , &n , &m , &k );
	if ( k == 1 ) {
		printf ( "%lld\n" , m );
		return ;
	}
	if ( m < k ) {
		x = (k - 1) % (n-m+1) + 1;
		for ( i = 2 ; i <= m ; i++ ) {
			x = (x + k - 1) % (n-m+i) + 1;
		}
		printf ( "%lld\n" , x );
	}
	else {
		x = (k - 1) % (n-m+1) + 1;
		i = 1;
		while ( i < m ) {
			//printf ( "%lld %lld\n" , i , x );
			if ( (x+k-1) >= (n-m+i) ) {
				i++;
				x = (x + k - 1) % (n-m+i) + 1;
			}
			else {
				t = (n-m+i-1-x)/(k-1);
				if ( i + t < m ) {
					x += t * k;
					i += t;
				}
				else {
					x += (m-i) * k;
					i = m;
				}
			}
		}
		printf ( "%lld\n" , x );
	}
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

