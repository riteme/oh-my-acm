/**
 * title: minkowski_sum
 * category: 计算几何 
 * description: minkowski_sum.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long LL;
struct node {
	LL x , y;
	node ():x(0),y(0){}
	node ( LL xx , LL yy ) {x = xx; y = yy;}
} p[4][220000] , tt[220000];
LL n[4];
LL ans;
node operator + ( node x1 , node x2 ) {
	x1.x += x2.x; x1.y += x2.y;
	return x1;
}
node operator - ( node x1 , node x2 ) {
	x1.x -= x2.x; x1.y -= x2.y;
	return x1;
}
bool cmp ( node x1 , node x2 ) {
	if ( x1.x == x2.x ) return x1.y < x2.y;
	return x1.x < x2.x;
}
LL det ( node x1 , node x2 , node x3 ) {
	x3 = x3 - x1; x2 = x2 - x1;
	return x2.x * x3.y - x2.y * x3.x;
}
void convex ( node *x , LL &num ) {
	LL i , cnt , old;
	sort ( x + 1 , x + 1 + num , cmp );
	tt[cnt=1] = x[1];
	for ( i = 2 ; i <= num ; i++ ) {
		while ( cnt >= 2 && det ( tt[cnt-1] , tt[cnt] , x[i] ) >= 0 ) cnt--;
		tt[++cnt] = x[i];
	}
	old = cnt;
	for ( i = num - 1 ; i >= 1 ; i-- ) {
		while ( cnt >= old + 1 && det ( tt[cnt-1] , tt[cnt] , x[i] ) >= 0 ) cnt--;
		tt[++cnt] = x[i];
	}
	if ( cnt != 1 ) cnt--;
	for ( i = 1 ; i <= cnt ; i++ )
		x[i] = tt[i];
	num = cnt;
	//the first point doesn't repeat in the end
}
void merge ( node *y , node *x1 , node *x2 , LL num1 , LL num2 , LL &num3 ) {
	LL i , j;
	y[num3=1] = x1[1] + x2[1];
	x1[num1+1] = x1[1]; x2[num2+1] = x2[1];
	for ( i = 1 , j = 1 ; i <= num1 && j <= num2 ; ) {	
		if ( det (node(0,0),x1[i+1]-x1[i],x2[j+1]-x2[j]) > 0 )
			y[++num3] = x1[i] + x2[++j];
		else y[++num3] = x1[++i] + x2[j];
	}
	for ( ; i <= num1 ; i++ ) y[++num3] = x1[i] + x2[j];
	for ( ; j <= num2 ; j++ ) y[++num3] = x1[i] + x2[j];
}
void work () {
	LL i;
	scanf ( "%lld%lld" , &n[1] , &n[2] );
	for ( i = 1 ; i <= n[1] ; i++ )
		scanf ( "%lld%lld" , &p[1][i].x , &p[1][i].y );
	for ( i = 1 ; i <= n[2] ; i++ )
		scanf ( "%lld%lld" , &p[2][i].x , &p[2][i].y );
	convex ( p[1] , n[1] );
	convex ( p[2] , n[2] );
	merge ( p[3] , p[1] , p[2] , n[1] , n[2] , n[3] );
	convex ( p[3] , n[3] );
	p[3][n[3]+1] = p[3][1];
	for ( i = 1 ; i <= n[3] ; i++ ) {
		ans += det ( node(0,0) , p[3][i+1] , p[3][i] );
	}//calculating 2*area
	printf ( "%lld\n" , ans );
}
int main () {
	work ();
	return 0;
}

