/**
 * title: Gomory-hu_tree
 * category: ÍøÂçÁ÷
 * description: Gomory-hu_tree.md
 */

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	int v , f , ff;
	node *next , *rev;
} poolp[40000] , *g[900];
struct tree {
	int v , c;
	tree *next;
} poolt[20000] , *gt[900];
int topp , topt;
int n , m;
int color , col[900];
int vis[900];
int index , cut[900] , ans;
int level[900];
void addt ( int u , int v , int c ) {
	tree *tmp1 = &poolt[++topt] , *tmp2 = &poolt[++topt];
	tmp1 -> v = v; tmp1 -> c = c; tmp1 -> next = gt[u]; gt[u] = tmp1;
	tmp2 -> v = u; tmp2 -> c = c; tmp2 -> next = gt[v]; gt[v] = tmp2;
	cut[++index] = c;
}
void dfs ( int i , int c , int cc ) {
	vis[i] = 1;
	if ( col[i] == c ) col[i] = cc;
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> f && vis[j->v] == 0 ) dfs ( j -> v , c , cc );
}
void clear () {
	int i;
	for ( i = 1 ; i <= topp ; i++ ) poolp[i].f = poolp[i].ff;
	for ( i = 1 ; i <= n ; i++ ) vis[i] = 0;
}
bool makelevel ( int s , int t ) {
	int i , k;
	queue < int > q;
	for ( i = 1 ; i <= n ; i++ ) level[i] = -1;
	level[s] = 1; q.push ( s );
	while ( q.size () != 0 ) {
		k = q.front (); q.pop ();
		for ( node *j = g[k] ; j ; j = j -> next )
			if ( j -> f && level[j->v] == -1 ) {
				level[j->v] = level[k] + 1;
				if ( j -> v == t ) return true;
				q.push ( j -> v );
			}
	}
	return false;
}
int find ( int k , int key , int t ) {
	if ( k == t ) return key;
	int i , s = 0;
	for ( node *j = g[k] ; j ; j = j -> next )
		if ( j -> f && level[j->v] == level[k] + 1 && s < key ) {
			i = find ( j -> v , min ( key - s , j -> f ) , t );
			j -> f -= i;
			j -> rev -> f += i;
			s += i;
		}
	if ( s == 0 ) level[k] = -1;
	return s;
}
int dinic ( int s , int t ) {
	int flow = 0;
	while ( makelevel ( s , t ) == true ) flow += find ( s , 999999999 , t );
	return flow;
}
void addp ( int u , int v , int f ) {
	node *tmp1 = &poolp[++topp] , *tmp2 = &poolp[++topp];
	tmp1 -> v = v; tmp1 -> f = f; tmp1 -> ff = f; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
	tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> ff = 0; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
void solve ( int c ) {
	int i , s , t = -1 , tmp;
	for ( i = 1 ; i <= n ; i++ ) if ( col[i] == c ) {
		s = i;
		break;
	}
	for ( i++ ; i <= n ; i++ ) if ( col[i] == c ) {
		t = i;
		break;
	}
	if ( t == -1 ) return ;
	clear ();
	addt ( s , t , dinic ( s , t ) );
	color++;
	dfs ( s , c , color );
	color++;
	for ( i = 1 ; i <= n ; i++ ) if ( col[i] == c ) col[i] = color;
	tmp = color;
	solve ( tmp ); solve ( tmp - 1 );
}
void work () {
	int i , u , v , f;
	scanf ( "%d%d" , &n , &m );
	for ( i = 1 ; i <= n ; i++ ) col[i] = 1;
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d%d" , &u , &v , &f );
		addp ( u , v , f );
		addp ( v , u , f );
	}
	color = 1;
	solve ( 1 );
	sort ( cut + 1 , cut + 1 + index );
	for ( i = 1 ; i <= index ; i++ ) if ( i == 1 || cut[i] != cut[i-1] ) ans++;
	printf ( "%d\n" , ans );
}
int main () {
	work ();
	return 0;
}
