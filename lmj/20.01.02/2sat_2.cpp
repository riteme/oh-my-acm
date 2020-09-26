/**
 * title: 2sat_2
 * category: Í¼ÂÛ 
 * description: null
 */
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	int v;
	node *next;
} pool[8110000] , *g[1610000] , *g1[1610000];
struct ran {
	int l , r , i;
} r1[410000] , r2[410000];
int top;
int n , p , M , m;
int x[410000] , y[410000];
int ol[410000];
int dfn[1610000] , low[1610000] , index;
int st[1610000] , ins[1610000] , tops;
int col[1610000] , color;
int in[1610000];
int ord[1610000] , indexord;
int ans[1610000] , cnt , fre;
int flag;
bool cmp1 ( ran x1 , ran x2 ) {
	return x1.l < x2.l;
}
bool cmp2 ( ran x1 , ran x2 ) {
	return x1.r < x2.r;
}
void add ( int u , int v ) {
	node *tmp = &pool[++top];
	//printf ( "  %d %d\n" , u , v );
	tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;
}
void add1 ( int u , int v ) {
	node *tmp = &pool[++top];
	//printf ( "add1 %d %d\n" , u , v );
	tmp -> v = v; tmp -> next = g1[u]; g1[u] = tmp;
}
void tarjan ( int i ) {
	dfn[i] = low[i] = ++index;
	ins[i] = 1;
	st[++tops] = i;
	for ( node *j = g[i] ; j ; j = j -> next ) {
		if ( !dfn[j->v] ) {
			tarjan ( j -> v );
			low[i] = min ( low[i] , low[j->v] );
		}
		else if ( ins[j->v] ) low[i] = min ( low[i] , dfn[j->v] );
	}
	if ( low[i] == dfn[i] ) {
		color++;
		while ( st[tops] != i ) {
			col[st[tops]] = color;
			ins[st[tops]] = 0;
			tops--;
		}
		col[i] = color;
		ins[i] = 0;
		tops--;
	}
}
void solve () {
	int i , k;
	queue < int > q;
	for ( i = 1 ; i <= p + p + M + M ; i++ ) {
		if ( !dfn[i] ) tarjan ( i );
	}
	for ( i = 1 ; i <= p + p + M + M ; i++ ) {
		for ( node *j = g[i] ; j ; j = j -> next ) {
			if ( col[i] != col[j->v] ) {
				add1 ( col[i] , col[j->v] );
				in[col[j->v]]++;
			}
		}
	}
	for ( i = 1 ; i <= p ; i++ ) {
		if ( col[i] == col[i+p] ) {
			printf ( "-1\n" );
			flag = 1;
			return ;
		}
	}
	for ( i = 1 ; i <= color ; i++ ) if ( in[i] == 0 ) q.push ( i );
	while ( q.size () ) {
		k = q.front (); q.pop ();
		ord[k] = ++indexord;
		//printf ( "k %d\n" , k );
		for ( node *j = g1[k] ; j ; j = j -> next ) {
			in[j->v]--;
			if ( in[j->v] == 0 ) q.push ( j -> v );
		}
	}
	for ( i = 1 ; i <= p ; i++ ) {
		if ( ord[col[i]] > ord[col[i+p]] ) ans[++cnt] = i;
	}
}
void work () {
	int i , j , u , v;
	scanf ( "%d%d%d%d" , &n , &p , &M , &m );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		add ( u + p , v );
		add ( v + p , u );
	}
	for ( i = 1 ; i <= p ; i++ ) {
		scanf ( "%d%d" , &r1[i].l , &r1[i].r );
		ol[i] = r1[i].l;
		r1[i].i = i;
		r2[i] = r1[i];
	}
	sort ( r1 + 1 , r1 + 1 + p , cmp1 );
	sort ( r2 + 1 , r2 + 1 + p , cmp2 );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		add ( u , v + p );
		add ( v , u + p );
	}
	for ( i = 1 ; i <= p ; i++ ) {
		if ( r1[i].r != M ) {
			add ( p + p + M + r1[i].r , p + r1[i].i );
			add ( r1[i].i , p + p + r1[i].r + 1 );
		}
		if ( r1[i].l != 1 ) {
			add ( p + p + r1[i].l , p + r1[i].i );
			add ( r1[i].i , p + p + M + r1[i].l - 1 );
		}
	}
	for ( i = 1 ; i <= M ; i++ ) {
		if ( i != M ) {
			add ( p + p + i , p + p + i + 1 );
		}
		if ( i != 1 ) {
			add ( p + p + M + i , p + p + M + i - 1 );
		}
	}
	solve ();
	if ( flag == 1 ) return ;
	/*for ( i = 1 ; i <= p * 4 ; i++ ) {
		printf ( "%d " , col[i] );
	}
	printf ( "\n" );*/
	/*for ( i = 1 ; i <= color ; i++ ) {
		printf ( "block %d:" , i );
		for ( j = l[i] ; j <= r[i] ; j++ ) {
			printf ( "%d " , block[j] );
		}
		printf ( "\n" );
	}*/
	/*for ( i = 1 ; i <= color ; i++ ) {
		printf ( "%d " , ord[i] );
	}
	printf ( "\n" );*/
	sort ( ans + 1 , ans + 1 + cnt );
	for ( i = 1 ; i <= cnt ; i++ ) {
		fre = max ( fre , ol[ans[i]] );
	}
	printf ( "%d %d\n" , cnt , fre );
	for ( i = 1 ; i <= cnt ; i++ ) {
		printf ( "%d%c" , ans[i] , i==cnt?'\n':' ' );
	}
}
int main () {
	work ();
	return 0;
}

