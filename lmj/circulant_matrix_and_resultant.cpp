/**
 * title: circulant_matrix_and_resultant
 * category: 数学 
 * description: circulant_matrix_and_resultant.md
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

#define vi vector<long long>

using namespace std;

const long long mod = 1000000007;
long long n;
long long a[5100] , b[5100] , p[5100] , pos1[5100];
long long vis[5100];
vi x , y;
long long ksm ( long long f , long long x ) {
	long long s = 1;
	while ( x ) {
		if ( x % 2 ) s = s * f % mod;
		f = f * f % mod; x = x / 2;
	}
	return s % mod;
}
long long inv ( long long x ) {
	return ksm ( x , mod - 2 );
}
long long resultant ( vi x1 , vi x2 ) {
	vi *p , *q;
	long long i , j , ret = 1 , co;
	p = &x1; q = &x2;
	while ( p -> size () != 1 && q -> size () != 1 ) {
		if ( p -> size () > q -> size () ) {
			swap ( p , q );
			if ( (p->size()-1) * (q->size()-1) % 2 == 1 ) {
				ret = -ret;
			}
		}
		co = inv ( (*p)[p->size()-1] ) * (*q)[q->size()-1] % mod;
		for ( i = p -> size () - 1 , j = q -> size () - 1 ; i >= 0 ; i-- , j-- ) {
			(*q)[j] = ((*q)[j]-co * ((*p)[i])) % mod;
		}
		for ( i = q -> size () - 1 ; i > 0 ; i-- ) {
			if ( (*q)[i] != 0 ) break;
		}
		ret = ret * ksm ( (*p)[p->size()-1] , q->size()-1 - i ) % mod;
		q -> resize ( i + 1 );
	}
	ret = ret * ksm ( (*p)[p->size()-1] , q -> size () - 1 ) % mod;
	ret = ret * ksm ( (*q)[q->size()-1] , p -> size () - 1 ) % mod;
	if ( ret < 0 ) ret += mod;
	return ret;
}
void work () {
	long long i , j , co , flag;
	long long ans;
	scanf ( "%lld" , &n );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%lld" , &a[i] );
	}
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%lld" , &p[i] );
	}
	co = 1;
	pos1[1] = 1; vis[1] = 1; flag = 1;
	for ( i = 2 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) if ( p[j] == pos1[i-1] ) {
			pos1[i] = j;
			if ( vis[j] == 1 ) flag = 0;
			vis[j] = 1;
			break;
		}
	}
	if ( flag == 0 ) {
		printf ( "0\n" );
		return ;
	}
	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = i + 1 ; j <= n ; j++ ) {
			if ( pos1[i] > pos1[j] ) co = -co;
		}
	}
	x.resize ( n );
	for ( i = 1 ; i <= n ; i++ ) b[i] = a[pos1[i]];
	for ( i = 0 ; i < n ; i++ ) {
		x[i] = b[i+1];
	}
	y.resize ( n + 1 );
	y[0] = mod - 1; y[n] = 1;
	ans = co * resultant ( y , x ) % mod;
	if ( ans < 0 ) ans += mod;
	printf ( "%lld\n" , ans );
}
int main () {
	work ();
	return 0;
}

