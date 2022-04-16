/**
 * title: lichao_segment_tree
 * category: 数据结构
 * description: lichao_segment_tree.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

const int maxn = 51000;
struct line {
	int x1 , y1 , x2 , y2;
};
struct node {
	int l , r , cov;
	line t;
	node *ll , *rr;
} pool[maxn*4] , *t;
int top;
int n , m;
void buildtree ( node *id , int l , int r ) {
	id -> l = l; id -> r = r;
	if ( l == r ) return ;
	int mid = (id->l+id->r)/2;
	id -> ll = &pool[++top]; id -> rr = &pool[++top];
	buildtree ( id -> ll , l , mid ); buildtree ( id -> rr , mid + 1 , r );
}
double geth ( line l , int x ) {
	if ( l.x1 == l.x2 ) return l.y1;
	double ret = ( ((double)x) - l.x1 ) * (l.y2-l.y1) / (l.x2-l.x1) + l.y1;
	return ret;
}
void add ( node *id , int l , int r , line x ) {
	int mid = (id->l+id->r)/2;
	if ( id -> l == l && id -> r == r ) {
		if ( id -> cov == 0 ) {
			id -> cov = 1;
			id -> t = x;
		}
		else {
			double x1 , x2 , x3 , t1 , t2 , t3;
			line y;
			x1 = geth ( x , l ); x2 = geth ( x , mid ); x3 = geth ( x , r );
			t1 = geth ( id -> t , l ); t2 = geth ( id -> t , mid ); t3 = geth ( id -> t , r );
			if ( t1 >= x1 && t3 >= x3 ) return ;
			if ( t1 <= x1 && t3 <= x3 ) {
				id -> t = x;
				return ;
			}
			if ( x2 > t2 ) swap ( id -> t , x );
			if ( (t1>=x1) == (t2>=x2) ) {
				add ( id -> rr , mid + 1 , r , x );
			}
			else add ( id -> ll , l , mid , x );
		}
		return ;
	}
	if ( r <= mid ) add ( id -> ll , l , r , x );
	else {
		if ( l > mid ) add ( id -> rr , l , r , x );
		else {
			add ( id -> ll , l , mid , x );
			add ( id -> rr , mid + 1 , r , x );
		}
	}
}
double query ( node *id , int x ) {
	if ( id -> l == id -> r ) {
		if ( id -> cov == 1 ) return geth ( id -> t , x );
		else return -1000000000.0;
	}
	int mid = (id->l+id->r)/2;
	double tmp;
	if ( id -> cov == 1 ) tmp = geth ( id -> t , x );
	else tmp = -1000000000.0;
	if ( x <= mid ) return max ( tmp , query ( id -> ll , x ) );
	else return max ( tmp , query ( id -> rr , x ) );
}
void work () {
	int i , op , x;
	double ans;
	line tmp;
	scanf ( "%d%d" , &n , &m );
	t = &pool[++top];
	buildtree ( t , 1 , 100000 );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%d%d%d%d" , &tmp.x1 , &tmp.y1 , &tmp.x2 , &tmp.y2 );
		if ( tmp.x1 > tmp.x2 ) {
			swap ( tmp.x1 , tmp.x2 );
			swap ( tmp.y1 , tmp.y2 );
		}
		if ( tmp.x1 == tmp.x2 ) {
			tmp.y1 = tmp.y2 = max ( tmp.y1 , tmp.y2 );
		}
		if ( tmp.x1 > 100000 || tmp.x2 < 1 ) continue;
		add ( t , max ( 1 , tmp.x1 ) , min ( 100000 , tmp.x2 ) , tmp );
	}
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d" , &op );
		if ( op == 0 ) {
			scanf ( "%d%d%d%d" , &tmp.x1 , &tmp.y1 , &tmp.x2 , &tmp.y2 );
			if ( tmp.x1 > tmp.x2 ) {
				swap ( tmp.x1 , tmp.x2 );
				swap ( tmp.y1 , tmp.y2 );
			}
			if ( tmp.x1 == tmp.x2 ) {
				tmp.y1 = tmp.y2 = max ( tmp.y1 , tmp.y2 );
			}
			if ( tmp.x1 > 100000 || tmp.x2 < 1 ) continue;
			add ( t , max ( 1 , tmp.x1 ) , min ( 100000 , tmp.x2 ) , tmp );
		}
		else {
			scanf ( "%d" , &x );
			ans = query ( t , x );
			//printf ( "%lf\n" , query ( t , x ) );
			if ( ans < -100000000.0 ) ans = 0.0;
			printf ( "%lf\n" , ans );
		}
	}
}
int main () {
	work ();
	return 0;
}

