/**
 * title: dsu_on_tree
 * category: 数据结构 
 * description: dsu_on_tree.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

struct node {
	int v;
	node *next;
} pool[210000] , *g[120000];
int top;
int n;
int a[120000];
int son[120000] , siz[120000];
int ex[1200000][23][2];
long long ans;
void add ( int u , int v ) {
	node *tmp = &pool[++top];
	tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;
}
void dfs1 ( int i , int from ) {
	siz[i] = 1;
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
		dfs1 ( j -> v , i );
		siz[i] += siz[j->v];
		if ( siz[j->v] > siz[son[i]] ) son[i] = j -> v;
	}
}
void changenum ( int i , int f ) {
	for ( int k = 0 ; k <= 19 ; k++ ) {
		ex[a[i]][k][(i&(1<<k))!=0] += f;
	}
}
void addtree ( int i , int from , int f ) {
	changenum ( i , f );
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
		addtree ( j -> v , i , f );
	}
}
void getans ( int i , int from , int val ) {
	int x;
	x = val ^ a[i];
	for ( int k = 0 ; k <= 19 ; k++ ) {
		ans += ((1ll*ex[x][k][(i&(1<<k))==0]) << k);
	}
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
		getans ( j -> v , i , val );
	}
}
void dfs2 ( int i , int from , int clr ) {
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
		if ( j -> v != son[i] ) dfs2 ( j -> v , i , 1 );
	}
	if ( son[i] ) dfs2 ( son[i] , i , 0 );
	//printf ( "%d %d %d\n" , i , clr , ans );
	for ( node *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
		if ( j -> v == son[i] ) continue;
		getans ( j -> v , i , a[i] );
		addtree ( j -> v , i , 1 );
	}
	//printf ( "%d %d\n" , i , ans );
	changenum ( i , 1 );
	//这里刚好根节点不会和子产生贡献 
	if ( clr ) {
		addtree ( i , from , -1 );
	}
}
void work () {
	int i , u , v;
	scanf ( "%d" , &n );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%d" , &a[i] );
	}
	for ( i = 1 ; i < n ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		add ( u , v );
		add ( v , u );
	}
	dfs1 ( 1 , -1 );
	dfs2 ( 1 , -1 , 0 );
	printf ( "%lld\n" , ans );
}
int main () {
	work ();
	return 0;
}

