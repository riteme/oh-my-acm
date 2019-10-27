/**
 * title: xihe_tree
 * category: 数据结构 
 * description: xihe_tree.md
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define ACM_BEGIN
const int maxn = 120000;
struct tree {
	int l , r , lazy;
	int mn;
	tree *ll , *rr;
} poolt[maxn*2] , *t;
struct edge {
	int v;
	edge *next;
} poole[maxn*2];
struct node {
	int fa , l , r , kl , kr;//[l,r] represents its range in a[], [kl,kr] represents its range of value
	int kind;//0 for xi, 1 for he
	edge *son;//sons from left to right
} p[maxn*2];
int topt , tope , tot;//tot: number of nodes in xihe-tree
int n , m , root;
int a[maxn];
int id[maxn];//id[i]=label of (a[i],a[i]) in xihe-tree
int lst[maxn*2];//if p[i] is he, lst[i]=the last son -> l,lst[i]=0 if p[i] is xi
int s1[maxn] , s2[maxn] , tp1 , tp2;
int st[maxn*2] , tops;
int dep[maxn*2] , go[18][maxn*2];
void add ( int u , int v ) {
	edge *tmp = &poole[++tope];
	tmp -> v = v; tmp -> next = p[u].son; p[u].son = tmp;
	//printf ( "%d %d\n" , u , v );
}
void reverse ( int i ) {
	edge *tmp = NULL , *t2;
	while ( p[i].son ) {
		t2 = p[i].son -> next;
		p[i].son -> next = tmp;
		tmp = p[i].son;
		p[i].son = t2;
	}
	p[i].son = tmp;
}
void buildtree ( tree *id , int l , int r ) {
	id -> l = l; id -> r = r;
	if ( l == r ) return ;
	int mid = (l+r)/2;
	id -> ll = &poolt[++topt]; id -> rr = &poolt[++topt];
	buildtree ( id -> ll , l , mid ); buildtree ( id -> rr , mid + 1 , r );
}
void pushdown ( tree *id ) {
	if ( id -> lazy ) {
		id -> ll -> lazy += id -> lazy;
		id -> ll -> mn += id -> lazy;
		id -> rr -> lazy += id -> lazy;
		id -> rr -> mn += id -> lazy;
		id -> lazy = 0;
	}
}
void change ( tree *id , int l , int r , int x ) {
	//printf ( "%d %d %d %d %d\n" , id -> l , id -> r , l , r , x );
	if ( id -> l == l && id -> r == r ) {
		id -> mn += x;
		id -> lazy += x;
		return ;
	}
	pushdown ( id );
	int mid = (id->l+id->r)/2;
	if ( r <= mid ) change ( id -> ll , l , r , x );
	else {
		if ( l > mid ) change ( id -> rr , l , r , x );
		else {
			change ( id -> ll , l , mid , x );
			change ( id -> rr , mid + 1 , r , x );
		}
	}
	id -> mn = min ( id -> ll -> mn , id -> rr -> mn );
}
int querypoint ( tree *id , int l ) {
	if ( id -> l == id -> r ) return id -> mn;
	pushdown ( id );
	int mid = (id->l+id->r)/2;
	if ( l <= mid ) return querypoint ( id -> ll , l );
	else return querypoint ( id -> rr , l );
}
int query ( tree *id ) {
	if ( id -> l == id -> r ) return id -> l;
	pushdown ( id );
	if ( id -> ll -> mn == 0 ) return query ( id -> ll );
	else return query ( id -> rr );
}
bool chk ( int x ) {
	if ( x == 0 || querypoint ( t , x ) != 0 ) return false;
	return true;
}
void dfs ( int i ) {
	/*printf ( "%d:" , i );
	for ( edge *j = p[i].son ; j ; j = j -> next ) {
		printf ( "%d " , j -> v );
	}
	printf ( "\n" );*/
	for ( edge *j = p[i].son ; j ; j = j -> next ) {
		p[j->v].fa = i;
		go[0][j->v] = i;
		dep[j->v] = dep[i] + 1;
		dfs ( j -> v );
		p[i].kl = min ( p[i].kl ,  p[j->v].kl );
		p[i].kr = max ( p[i].kr ,  p[j->v].kr );
	}
}
int lca ( int u , int v ) {
	int i;
	if ( dep[u] < dep[v] ) swap ( u , v );
	for ( i = 17 ; i >= 0 ; i-- ) if ( dep[go[i][u]] >= dep[v] ) u = go[i][u];
	if ( u == v ) return u;
	for ( i = 17 ; i >= 0 ; i-- ) if ( go[i][u] != go[i][v] ) {
		u = go[i][u];
		v = go[i][v];
	}
	//printf ( "%d %d\n" , u , v );
	return go[0][u];
}
int jump ( int u , int x ) {
	int i;
	for ( i = 0 ; i <= 17 ; i++ ) {
		if ( x % 2 ) u = go[i][u];
		x >>= 1;
	}
	return u;
}
void work () {
	int i , j , now , tmp , u , v , l;
	scanf ( "%d" , &n );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%d" , &a[i] );
	}
	t = &poolt[++topt];
	buildtree ( t , 1 , n );
	tops = 0;
	for ( i = 1 ; i <= n ; i++ ) {
		while ( tp1 && a[s1[tp1]] > a[i] ) {
			change ( t , s1[tp1-1] + 1 , s1[tp1] , a[s1[tp1]] );
			tp1--;
		}
		while ( tp2 && a[s2[tp2]] < a[i] ) {
			change ( t , s2[tp2-1] + 1 , s2[tp2] , -a[s2[tp2]] );
			tp2--;
		}
		change ( t , s1[tp1] + 1 , i , -a[i] ); s1[++tp1] = i;
		change ( t , s2[tp2] + 1 , i , a[i] ); s2[++tp2] = i;
		
		id[i] = ++tot; p[tot].l = p[tot].r = i; p[tot].kind = 0;
		now = tot;
		tmp = query ( t );
		//printf ( "%d %d %d\n" , i , now , tmp );
		while ( tops && tmp <= p[st[tops]].l ) {
			if ( p[st[tops]].kind == 1 && chk ( lst[st[tops]] ) ) {
				p[st[tops]].r = i;
				add ( st[tops] , now );
				now = st[tops--];
			}
			else {
				if ( tops && chk ( p[st[tops]].l ) ) {
					p[++tot].kind = 1;
					p[tot].l = p[st[tops]].l; p[tot].r = i; lst[tot] = p[now].l;
					add ( tot , st[tops--] ); add ( tot , now );
					now = tot;
				}
				else {
					add ( ++tot , now );
					do {
						add ( tot , st[tops--] );
					} while ( tops && !chk ( p[st[tops]].l ) );
					p[tot].l = p[st[tops]].l; p[tot].r = i;
					add ( tot , st[tops--] );
					now = tot;
				}
			}
		}
		st[++tops] = now;
		change ( t , 1 , i , -1 );
	}
	root = st[1];
	for ( i = 1 ; i <= tot ; i++ ) {
		if ( p[i].kind == 1 ) {
			reverse ( i );
		}
		p[i].kl = n + 1;
	}
	for ( i = 1 ; i <= n ; i++ ) {
		p[id[i]].kl = p[id[i]].kr = a[i];
	}
	dep[root] = 1;
	dfs ( root );
	
	for ( i = 1 ; i <= 17 ; i++ )
		for ( j = 1 ; j <= tot ; j++ )
			go[i][j] = go[i-1][go[i-1][j]];
	scanf ( "%d" , &m );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		u = id[u]; v = id[v];
		l = lca ( u , v );
		//printf ( "%d %d %d\n" , u , v , l );
		if ( p[l].kind == 1 ) {
			u = jump ( u , dep[u] - dep[l] - 1 );
			v = jump ( v , dep[v] - dep[l] - 1 );
			printf ( "%d %d\n" , p[u].l , p[v].r );
		}
		else printf ( "%d %d\n" , p[l].l , p[l].r );
	}
}
#define ACM_END
int main () {
	work ();
	return 0;
}

