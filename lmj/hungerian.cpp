/**
 * title: hungerian
 * category: 图论
 * description: hungerian.md
 */
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

#define ACM_BEGIN
const int maxn = 120000;
struct node {
	int v , f;
	node *next , *rev;
} pool[maxn*10] , *g[maxn*2];
int top;
int n , m;
int S , T;
int match[maxn*2];
int level[maxn*2];
int key[maxn*2] , vis[maxn*2];
int ans[maxn] , cnt;
void add ( int u , int v ) {
	node *tmp1 = &pool[++top] , *tmp2 = &pool[++top];
	tmp1 -> v = v; tmp1 -> f = 1; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
	tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
bool makelevel () {
	int i , k;
	queue < int > q;
	for ( i = S ; i <= T ; i++ ) {
		level[i] = -1;
	}
	level[S] = 0;
	q.push ( S );
	while ( q.size () ) {
		k = q.front (); q.pop ();
		for ( node *j = g[k] ; j ; j = j -> next )
			if ( j -> f && level[j->v] == -1 ) {
				level[j->v] = level[k] + 1;
				q.push ( j -> v );
				if ( j -> v == T ) return true;
			}
	}
	return false;
}
int find ( int k , int key ) {
	if ( k == T ) return key;
	int i , s = 0;
	for ( node *j = g[k] ; j ; j = j -> next ) {
		if ( j -> f && level[j->v] == level[k] + 1 && s < key ) {
			i = find ( j -> v , min ( key - s , j -> f ) );
			j -> f -= i;
			j -> rev -> f += i;
			s += i;
		}
	}
	if ( s == 0 ) level[k] = -1;
	return s;
}
int dinic () {
	int flow = 0;
	while ( makelevel () == true ) flow += find ( S , 9999999 );
	return n - 1 - flow;
}
void dfs ( int i ) {
	key[i] = 0;
	vis[i] = 1;
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> v != S && j -> v != T ) {
		if ( j -> v != match[i] ) {
			if ( vis[match[j->v]] ) continue;
			dfs ( match[j->v] );
		}
	}
}
void work () {
	int i , u , v;
	scanf ( "%d%d" , &n , &m );
	S = 0; T = 2 * n + 1;
	for ( i = 1 ; i <= n ; i++ ) {
		add ( S , 2 * i - 1 );
		add ( i * 2 , T );
	}
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		add ( 2 * u - 1 , 2 * v );
	}
	int out = dinic ();
	printf ( "%d\n" , out );
	for ( i = 1 ; i <= n * 2 ; i += 2 ) {
		for ( node *j = g[i] ; j ; j = j -> next ) {
			if ( j -> v >= 1 && j -> f == 0 ) {
				match[i] = j -> v;
				match[j->v] = i;
			}
		}
	}
	for ( i = 1 ; i <= 2 * n ; i++ ) key[i] = 1;
	for ( i = 1 ; i <= n * 2 ; i++ ) {
		if ( !match[i] && key[i] == 1 ) {
			dfs ( i );
		}
	}
	//for ( i = 1 ; i <= n * 2 ; i++ ) {
	//	printf ( "%d\n" , key[i] );
	//}
}
#define ACM_END
int main () {
	work ();
	return 0;
}

