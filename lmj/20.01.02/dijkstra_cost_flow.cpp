/**
 * title: dijkstra费用流
 * category: 网络流
 * description: dijkstra_cost_flow.md
 */


#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	int v , c , f;
	node *next , *rev;
} pool[510000] , *g[120000] , *from[120000];
struct so {
	int i , c;
};
int top;
int n , m;
int dis[120000] , f[120000] , h[102000];
int s , t;
int tot;
bool operator < ( so x1 , so x2 ) {
	return x1.c > x2.c;
}
void clear () {
	int i;
	for ( i = 1 ; i <= top ; i++ ) pool[i] = pool[0];
	for ( i = 1 ; i <= t ; i++ ) {
		g[i] = NULL;
		from[i] = NULL;
		h[i] = 0;
	}
	top = 0;
	tot = 0;
}
void add ( int u , int v , int f , int c ) {
	node *tmp1 = &pool[++top] , *tmp2 = &pool[++top];
	tmp1 -> v = v; tmp1 -> f = f; tmp1 -> c = c; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
	tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> c = -c; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
void spfa () {
	int i , k;
	queue < int > q;
	for ( i = 1 ; i <= t ; i++ ) {
		dis[i] = 1000000000;
		f[i] = 0;
	}
	dis[s] = 0; f[s] = 1;
	q.push ( s );
	while ( q.size() ) {
		k = q.front (); q.pop();
		f[k] = 0;
		for ( node *j = g[k] ; j ; j = j -> next )
			if ( j -> f && dis[j->v] > dis[k] + j -> c ) {
				dis[j->v] = dis[k] + j -> c;
				from[j->v] = j;
				if ( !f[j->v] ) q.push ( j -> v );
				f[j->v] = 1;
			}
	}
	for ( i = 1 ; i <= t ; i++ ) {
		h[i] = dis[i];
	}
}
void dij () {
	int i;
	priority_queue < so > q;
	so k , tmp;
	for ( i = 1 ; i <= t ; i++ ) {
		dis[i] = 1000000000;
		f[i] = 0;
	}
	dis[s] = 0;
	k.i = s; k.c = 0;
	q.push ( k );
	while ( q.size() ) {
		k = q.top (); q.pop();
		if ( f[k.i] ) continue;
		f[k.i] = 1;
		for ( node *j = g[k.i] ; j ; j = j -> next ) {
			if ( j -> f && dis[j->v] > dis[k.i] + j -> c + h[k.i] - h[j->v] ) {
				dis[j->v] = dis[k.i] + j -> c + h[k.i] - h[j->v];
				from[j->v] = j;
				tmp.i = j -> v; tmp.c = dis[j->v];
				q.push ( tmp );
			}
		}
	}
	for ( i = 1 ; i <= t ; i++ ) h[i] += dis[i];
}
int find () {
	int i , ret = 0 , flow = 100000;
	for ( i = t ; i != s ; i = from[i] -> rev -> v ) flow = min ( flow , from[i] -> f );
	for ( i = t ; i != s ; i = from[i] -> rev -> v ) {
		from[i] -> f -= flow;
		from[i] -> rev -> f += flow;
	}
	tot += flow;
	return flow * h[t];
}
void dinic () {
	int ans = 0;
	spfa ();
	while ( h[t] < 1000000000 ) {
		ans += find ();
		dij ();
	}
	if ( tot != n ) printf ( "NO\n" );
	else printf ( "%d\n" , ans );
}
void work () {
	int i , u , v , c;
	//scanf ( "%d%d" , &n , &m );
	n = 1000; m = 10000;
	for ( i = 1 ; i <= m ; i++ ) {
		//scanf ( "%d%d%d" , &u , &v , &c );
		u = rand () % n + 1;
		do {
			v = rand () % n + 1;
		} while ( u == v );
		c = rand () + 1;
		add ( 1 + u , 1 + n + v , 1 , c );
		add ( 1 + v , 1 + n + u , 1 , c );
	}
	for ( i = 1 ; i <= n ; i++ ) {
		add ( 1 , 1 + i , 1 , 0 );
		add ( 1 + n + i , 1 + n + n + 1 , 1 , 0 );
	}
	s = 1; t = 1 + n + n + 1;
	dinic ();
	clear ();
}
int main () {
	int t;
	scanf ( "%d" , &t );
	for ( int _ = 1 ; _ <= t ; _++ ) {
		printf ( "Case %d: " , _ );
		work ();
	}
	return 0;
}
