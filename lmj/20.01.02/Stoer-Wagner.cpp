/**
 * title: Stoer-Wagner
 * category: 网络流
 * description: Stoer-Wagner.md
 */


#include <stdio.h>
#include <algorithm>

using namespace std;

int n , m , s;
int cost[510][510];
int exist[310];
int w[310] , now[310];
int ans;
void clear () {
	int i , j;
	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
			cost[i][j] = 0;
		}
	}
}
int get ( int a , int &s , int &t ) {
	int i , mx , mi;
	t = a;
	for ( i = 1 ; i <= n ; i++ ) now[i] = 0;
	now[a] = 1;
	for ( i = 1 ; i <= n ; i++ ) if ( exist[i] ) {
		w[i] = cost[a][i];
	}
	while ( 1 ) {
		mx = -1;
		for ( i = 1 ; i <= n ; i++ ) {
			if ( exist[i] && !now[i] ) {
				if ( mx < w[i] ) {
					mx = w[i];
					mi = i;
				}
			}
		}
		if ( mx == -1 ) break;
		now[mi] = 1;
		s = t; t = mi;
		for ( i = 1 ; i <= n ; i++ ) {
			if ( exist[i] && !now[i] ) {
				w[i] += cost[mi][i];
			}
		}
	}
	return w[t];
}
void merge ( int x , int y ) {
	int i;
	for ( i = 1 ; i <= n ; i++ ) {
		cost[x][i] += cost[y][i];
		cost[i][x] += cost[i][y];
	}
	exist[y] = 0;
}
void work () {
	int i , j , s , t , u , v , c;
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d%d" , &u , &v , &c );
		cost[u][v] += c; cost[v][u] += c;
	}
	for ( i = 1 ; i <= n ; i++ ) exist[i] = 1;
	ans = 2147483647;
	for ( i = 1 ; i < n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
			if ( exist[j] ) break;
		}
		ans = min ( ans , get ( j , s , t ) );
		merge ( s , t );
	}
	printf ( "%d\n" , ans );
	clear ();
}
int main () {
	int _;
	while ( scanf ( "%d%d%d" , &n , &m , &_ ) ) {
		if ( n == 0 && m == 0 && _ == 0 ) break;
		work ();
	}
	return 0;
}
