/**
 * title: 2sat
 * category: 图论 
 * description: 2sat.md
 */
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

#define ACM_BEGIN
const int maxn = 1200;
struct node {
	int v;
	node *next;
} pool[maxn*maxn*4] , *g[maxn*2] , *g1[maxn*2];
int top;
int n;
char z1[200] , z2[200];
int start[maxn] , end[maxn] , last[maxn];
int low[maxn*2] , dfn[maxn*2] , index;
int st[maxn*2] , ins[maxn*2] , tops;
int col[maxn*2] , color;
int block[maxn*2] , l[maxn*2] , r[maxn*2] , topb;
int in[maxn*2] , taboo[maxn*2];
int ans[maxn*2];
queue < int > q;
int get ( int x ) {
	if ( x % 2 == 0 ) return x - 1;
	else return x + 1;
}
void add ( int u , int v ) {
	node *tmp = &pool[++top];
	tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;
	//printf ( "%d %d\n" , u , v );
}
void add1 ( int u , int v ) {
	node *tmp = &pool[++top];
	tmp -> v = v; tmp -> next = g1[u]; g1[u] = tmp;
	//printf ( "%d %d\n" , u , v );
}
int check ( int l1 , int r1 , int l2 , int r2 ) {
	//printf ( "%d %d %d %d\n" , l1 , r1 , l2 , r2 );
	if ( r1 <= l2 || r2 <= l1 ) return 0;
	return 1;
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
		l[color] = topb + 1;
		while ( st[tops] != i ) {
			col[st[tops]] = color;
			block[++topb] = st[tops];
			ins[st[tops]] = 0;
			tops--;
		}
		col[i] = color;
		block[++topb] = i;
		r[color] = topb;
		ins[i] = 0;
		tops--;
	}
}
void dfs ( int i ) {
	taboo[i] = 2;
	for ( node *j = g1[i] ; j ; j = j -> next ) {
		if ( !taboo[j->v] ) dfs ( j -> v );
	}
}
void work () {
	int i , k , t1 , t2 , t3 , t4;
	scanf ( "%d" , &n );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%s%s%d" , z1 + 1 , z2 + 1 , &last[i] );
		start[i] = (z1[1]-'0')*600+(z1[2]-'0')*60+(z1[4]-'0')*10+(z1[5]-'0');
		end[i] = (z2[1]-'0')*600+(z2[2]-'0')*60+(z2[4]-'0')*10+(z2[5]-'0');
	}
	for ( i = 1 ; i <= n ; i++ ) {
		for ( int j = i + 1 ; j <= n ; j++ ) {
			t1 = check ( start[i] , start[i] + last[i] , start[j] , start[j] + last[j] );
			t2 = check ( start[i] , start[i] + last[i] , end[j] - last[j] , end[j] );
			t3 = check ( end[i] - last[i] , end[i] , start[j] , start[j] + last[j] );
			t4 = check ( end[i] - last[i] , end[i] , end[j] - last[j] , end[j] );
			if ( t1 == 1 ) {
				add ( i * 2 - 1 , j * 2 );
				add ( j * 2 - 1 , i * 2 );
			}
			if ( t2 == 1 ) {
				add ( i * 2 - 1 , j * 2 - 1 );
				add ( j * 2 , i * 2 );
			}
			if ( t3 == 1 ) {
				add ( i * 2 , j * 2 );
				add ( j * 2 - 1 , i * 2 - 1 );
			}
			if ( t4 == 1 ) {
				add ( i * 2 , j * 2 - 1 );
				add ( j * 2 , i * 2 - 1 );
			}
		}
	}
	for ( i = 1 ; i <= n * 2 ; i++ ) if ( !dfn[i] ) tarjan ( i );
	//printf ( "%d\n" , tops );
	//for ( i = 1 ; i <= n * 2 ; i++ ) printf ( "%d %d\n" , dfn[i] , low[i] );
	//printf ( "%d\n" , color );
	/*for ( i = 1 ; i <= color ; i++ ) {
		for ( int j = l[i] ; j <= r[i] ; j++ ) printf ( "%d " , block[j] );
		printf ( "\n" );
	}*/
	for ( i = 1 ; i <= n ; i++ ) {
		if ( col[i*2] == col[i*2-1] ) {
			printf ( "NO\n" );
			return ;
		}
	}
	for ( i = 1 ; i <= n * 2 ; i++ )
		for ( node *j = g[i] ; j ; j = j -> next ) {
			if ( col[i] != col[j->v] ) {
				add1 ( col[j->v] , col[i] );
				in[col[i]]++;
			}
		}
	for ( i = 1 ; i <= color ; i++ ) if ( in[i] == 0 ) q.push ( i );
	while ( q.size () ) {
		//for ( i = 1 ; i <= color ; i++ ) printf ( "%d " , in[i] );
		//printf ( "\n" );
		k = q.front ();
		q.pop ();
		if ( taboo[k] ) continue;
		taboo[k] = 1;
		for ( i = l[k] ; i <= r[k] ; i++ ) {
			//printf ( "%d %d\n" , k , col[get(block[i])] );
			dfs ( col[get(block[i])] );
			ans[block[i]] = 1;
		}
		for ( node *j = g1[k] ; j ; j = j -> next ) if ( !taboo[j->v] ) {
			in[j->v]--;
			if ( in[j->v] == 0 ) q.push ( j -> v ); 
		}
	}
	printf ( "YES\n" );
	for ( i = 1 ; i <= n ; i++ ) {
		if ( ans[i*2-1] ) {
			printf ( "%02d:%02d %02d:%02d\n" , 
				start[i]/60 , start[i]%60 ,
				(start[i]+last[i])/60 , (start[i]+last[i])%60 );
		}
		else {
			printf ( "%02d:%02d %02d:%02d\n" , 
				(end[i]-last[i])/60 , (end[i]-last[i])%60 ,
				end[i]/60 , end[i]%60 );
		}
	}
}
#define ACM_END
int main () {
	work ();
	return 0;
}
