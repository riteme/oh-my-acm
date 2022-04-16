/**
 * title: dominator_tree
 * category: Í¼ÂÛ 
 * description: dominator_tree.md 
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int n , m , x , y;
int dfn[220000] , fa[220000] , idom[220000] , sdom[220000];
int idfn[220000] , index;
vector < int > g[220000] , pred[220000] , bucket[220000];
int c[220000] , mn[220000];
int out[220000] , cnt;
void clear () {
	int i;
	for ( i = 1 ; i <= n ; i++ ) {
		dfn[i] = fa[i] = idom[i] = sdom[i] = 0;
		idfn[i] = 0;
		g[i].clear ();
		pred[i].clear ();
		bucket[i].clear ();
	}
	index = 0;
}
void add ( int u , int v ) {
	g[u].push_back(v);
	pred[v].push_back(u);
}
void dfs ( int i , int from ) {
	dfn[i] = ++index;
	idfn[index] = i;
	for ( auto j : g[i] ) if ( j != from && !dfn[j] ) {
		fa[j] = i;
		dfs ( j , i );
	}
}
void link ( int a , int b ) {
	c[b] = a;
}
int find ( int x ) {
	if ( c[x] == -1 ) return x;
	int t = find ( c[x] );
	if ( dfn[sdom[mn[c[x]]]] < dfn[sdom[mn[x]]] ) mn[x] = mn[c[x]];
	c[x] = t;
	return t;
}
int eval ( int x ) {
	find ( x );
	return mn[x];
}
void solve () {
	int i , now , tmp;
	dfs ( x , -1 );
	for ( i = 1 ; i <= n ; i++ ) {
		sdom[i] = i;
		c[i] = -1;
		mn[i] = i;
	}
	for ( i = n ; i >= 2 ; i-- ) {
		now = idfn[i];
		if ( now == 0 ) continue;//All vertices are not visited
		for ( auto j : pred[now] ) {
			if ( dfn[j] == 0 ) continue;
			tmp = eval ( j );
			if ( dfn[sdom[tmp]] < dfn[sdom[now]] ) sdom[now] = sdom[tmp];
		}
		bucket[sdom[now]].push_back(now);
		link ( fa[now] , now );
		for ( auto j : bucket[fa[now]] ) {
			tmp = eval ( j );
			if ( sdom[tmp] == sdom[j] ) idom[j] = fa[now];
			else idom[j] = tmp;
		}
		bucket[fa[now]].clear ();
	}
	sdom[idfn[1]] = idom[idfn[1]] = 0;
	for ( i = 2 ; i <= n ; i++ ) {
		if ( idfn[i] == 0 ) break;
		if ( idom[idfn[i]] != sdom[idfn[i]] )
			idom[idfn[i]] = idom[idom[idfn[i]]];
	}
}
void work () {
	int i , u , v;
	scanf ( "%d%d" , &n , &m );
	scanf ( "%d%d" , &x , &y );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		add ( u , v );
	}
	solve ();
	cnt = 0;
	for ( y ; y != x ; y = idom[y] ) {
		out[++cnt] = y;
	}
	out[++cnt] = x;
	printf ( "%d\n" , cnt );
	for ( i = cnt ; i >= 1 ; i-- ) {
		printf ( "%d%c" , out[i] , i==1?'\n':' ' );
	}
}
int main () {
	int t;
	scanf ( "%d" , &t );
	while ( t-- ) {
		work ();
		clear ();
	}
	return 0;
}

