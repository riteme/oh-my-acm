/**
 * title: kdtree
 * category: 数据结构 
 * description: null
 */
//not checked
#include <stdio.h>
#include <algorithm>

using namespace std;

struct point {
	int x , y;
} a[120000];
struct node {
	int kind , nx , ny;
	int siz;
	int x[2] , y[2];
	node *ll , *rr;
} pool[120000] , *t;
int top;
int n;
long long k;
bool cmp1 ( point x1 , point x2 ) {
	return x1.x < x2.x;
}
bool cmp2 ( point x1 , point x2 ) {
	return x1.y < x2.y;
}
void update ( node *id ) {
	id -> x[0] = id -> x[1] = id -> nx;
	id -> y[0] = id -> y[1] = id -> ny;
	id -> siz = 1;
	if ( id -> ll ) {
		id -> x[0] = min ( id -> x[0] , id -> ll -> x[0] );
		id -> x[1] = max ( id -> x[1] , id -> ll -> x[1] );
		id -> y[0] = min ( id -> y[0] , id -> ll -> y[0] );
		id -> y[1] = max ( id -> y[1] , id -> ll -> y[1] );
		id -> siz += id -> ll -> siz;
	}
	if ( id -> rr ) {
		id -> x[0] = min ( id -> x[0] , id -> rr -> x[0] );
		id -> x[1] = max ( id -> x[1] , id -> rr -> x[1] );
		id -> y[0] = min ( id -> y[0] , id -> rr -> y[0] );
		id -> y[1] = max ( id -> y[1] , id -> rr -> y[1] );
		id -> siz += id -> rr -> siz;
	}
}
void buildtree ( node *id , int l , int r , int kind ) {
	int mid = (l+r)/2;
	id -> kind = kind;
	if ( kind == 0 ) nth_element ( a + l , a + mid , a + r + 1 , cmp1 );
	else nth_element ( a + l , a + mid , a + r + 1 , cmp2 );
	id -> nx = a[mid].x; id -> ny = a[mid].y;
	if ( l <= mid - 1 ) {
		id -> ll = &pool[++top];
		buildtree ( id -> ll , l , mid - 1 , kind ^ 1 );
	}
	if ( mid + 1 <= r ) {
		id -> rr = &pool[++top];
		buildtree ( id -> rr , mid + 1 , r , kind ^ 1 );
	}
	update ( id );
}
int getnear ( node *id , point now ) {
	int ret = 0;
	if ( id -> x[0] > now.x ) ret += id -> x[0] - now.x;
	if ( id -> x[1] < now.x ) ret += now.x - id -> x[1];
	if ( id -> y[0] > now.y ) ret += id -> y[0] - now.y;
	if ( id -> y[1] < now.y ) ret += now.y - id -> y[1];
	return ret;
}
int getfar ( node *id , point now ) {
	int ret = 0;
	ret += max ( abs(now.x-id->x[0]) , abs(now.x-id->x[1]) );
	ret += max ( abs(now.y-id->y[0]) , abs(now.y-id->y[1]) );
	return ret;
}
int cnt;
int query ( node *id , point now , int x ) {
	if ( !id ) return 0;
	if ( getfar ( id , now ) <= x ) {
		return id -> siz;
	}
	if ( getnear ( id , now ) > x ) return 0;
	cnt++;
	int ret = 0;
	if ( abs(id->nx-now.x) + abs(id->ny-now.y) <= x ) ret++;
	ret += query ( id -> ll , now , x ) + query ( id -> rr , now , x );
	return ret;
}
long long check ( int x ) {
	int i;
	long long ret;
	ret = 0;
	cnt = 0;
	for ( i = 1 ; i <= n ; i++ ) {
		ret += query ( t , a[i] , x );
	}
	printf ( "%d %d\n" , x , cnt );
	return (ret-n) / 2;
}
void work () {
	int i , l , r , mid;
	scanf ( "%d%lld" , &n , &k );
	for ( i = 1 ; i <= n ; i++ ) {
		//scanf ( "%d%d" , &a[i].x , &a[i].y );
		a[i].x = rand() * rand () % 100000000;
		a[i].y = rand() * rand () % 100000000;
	}
	t = &pool[++top];
	buildtree ( t , 1 , n , 0 );
	l = 0; r = 400000000;
	while ( l < r - 1 ) {
		mid = (l+r)/2;
		if ( check ( mid ) < k ) l = mid;
		else r = mid;
	}
	printf ( "%d\n" , r );
}
int main () {
	work ();
	return 0;
}

