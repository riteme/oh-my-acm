/**
 * title: 费用流
 * category: 网络流
 * description: /dev/null
 */

#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	int v , f , c;
	node *next , *rev;
} pool[1200000] , *g[12000] , *from[12000];
int top;
int n , m;
char z[4][30][30];
int sum , flow , sum1;
int dis[12000] , f[12000];
int get ( int x , int y , int k ) {
	return (x-1)*m+y+n*m*k;
}
#define ACM_BEGIN
void add ( int u , int v , int f , int c ) {
	node *tmp1 = &pool[++top] , *tmp2 = &pool[++top];
	tmp1 -> v = v; tmp1 -> f = f; tmp1 -> c = c; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
	tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> c = -c; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
bool spfa () {
	int i , k;
	queue < int > q;
	for ( i = 1 ; i <= 1 + n*m*3 + 1 ; i++ ) dis[i] = 9999999, f[i] = 0;
	dis[1] = 0; f[1] = 1; q.push ( 1 );
	while ( q.size () != 0 ) {
		k = q.front (); q.pop (); f[k] = 0;
		for ( node *j = g[k] ; j ; j = j -> next )
			if ( j -> f && dis[j->v] > dis[k] + j -> c ) {
				dis[j->v] = dis[k] + j -> c;
				from[j->v] = j;
				if ( f[j->v] == 0 ) q.push ( j -> v );
				f[j->v] = 1;
			}
	}
	if ( dis[1+n*m*3+1] != 9999999 ) return true;
	return false;
}
int find () {
	int i , f = 999999;
	for ( i = 1+n*m*3+1 ; i != 1 ; i = from[i] -> rev -> v ) f = min ( f , from[i] -> f );
	flow += f;
	for ( i = 1+n*m*3+1 ; i != 1 ; i = from[i] -> rev -> v ) from[i] -> f -= f, from[i] -> rev -> f += f;
	return f * dis[1+n*m*3+1];
}
void dinic () {
	int ans = 0;
	while ( spfa () == true ) ans += find ();
	//printf ( "%d\n" , flow );
	if ( flow == sum && sum == sum1 ) printf ( "%d\n" , ans );
	else printf ( "-1\n" );
}
#define ACM_END
void work () {
	int i , j , x , y;
	scanf ( "%d%d" , &n , &m );
	for ( i = 1 ; i <= n ; i++ ) scanf ( "%s" , z[1][i] + 1 );
	for ( i = 1 ; i <= n ; i++ ) scanf ( "%s" , z[2][i] + 1 );
	for ( i = 1 ; i <= n ; i++ ) scanf ( "%s" , z[3][i] + 1 );
	sum = 0;
	for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= m ; j++ ) {
		if ( z[1][i][j] == '1' && z[2][i][j] == '1' ) z[1][i][j] = z[2][i][j] = 0;
	}
	for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= m ; j++ ) {
		if ( z[1][i][j] == '1' ) add ( 1 , 1 + get(i,j,1) , 1 , 0 ),sum++;
	}
	for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= m ; j++ ) {
		if ( z[2][i][j] == '1' ) {
			//add ( 1 + get(i,j,0) , 1 + get(i,j,2) , 1 , 0 );
			add ( 1 + get(i,j,0) , 1 + get(i,j,2) , 1 , 0 );
			add ( 1 + get(i,j,2) , 1 + n*m*3 + 1 , 1 , 0 );
			sum1++;
		}
	}
	for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= m ; j++ ) {
		if ( ( z[1][i][j] == '1' || z[2][i][j] == '1' ) && z[3][i][j] == '0' ) {
			printf ( "-1\n" );
			return ;
		}
		if ( z[1][i][j] == '1' || z[2][i][j] == '1' )
			add ( 1 + get(i,j,0) , 1 + get(i,j,1) , (z[3][i][j] - '0'-1)/2 , 0 );
		else
			add ( 1 + get(i,j,0) , 1 + get(i,j,1) , (z[3][i][j] - '0')/2 , 0 );
	}
	for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= m ; j++ ) {
		x = i; y = j-1;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i; y = j+1;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i-1; y = j-1;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i-1; y = j;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i-1; y = j+1;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i+1; y = j-1;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i+1; y = j;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
		x = i+1; y = j+1;
		if ( 1 <= x && x <= n && 1 <= y && y <= m ) add ( 1 + get(i,j,1) , 1 + get(x,y,0) , 99999 , 1 );
	}
	dinic ();
}
int main () {
	work ();
	return 0;
}
