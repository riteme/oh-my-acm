/**
 * title: min_25_seive_lattice_on_circle
 * category: 数论 
 * description: min_25_seive_lattice_on_circle.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL NN = 420000;
const LL block = 100000;
LL n , p[1200000] , prime[NN] , tot;
LL value[NN] , cnt , limit , pos[NN];
LL sumh[NN] , sumh1[NN] , h0[NN] , h1[NN];
LL h[NN] , g[NN];
void clear () {
	int i;
	for ( i = 0 ; i <= NN - 1 ; i++ ) {
		value[i] = sumh1[i] = pos[i] = sumh[i] = h0[i] = h1[i] = h[i] = g[i] = 0;
		prime[i] = 0;
	}
	tot = 0; cnt = limit = 0;
}
LL getpos ( LL x ) {
	return x<=limit?x:pos[n/x];
}
void predo () {
	LL i , j;
	for ( i = 2 ; i <= block ; i++ ) {
		if ( !p[i] )
			prime[++tot] = i;
		for ( j = 1 ; j <= tot && i * prime[j] <= block ; j++ ) {
			p[i*prime[j]] = 1;
			if ( i % prime[j] == 0 ) break;
		}
	}
	cnt = 0;
	for ( i = 1 ; i * i <= n ; i++ ) value[++cnt] = i;
	i--; limit = i;
	for ( ; i >= 1 ; i-- ) if ( n / i != value[cnt] ) {
		value[++cnt] = n / i;
		pos[i] = cnt;
	}
	LL tmp;
	for ( i = 1 ; i <= tot ; i++ ) {
		if ( prime[i] % 4 == 1 ) tmp = 3;
		else tmp = 1;
		if ( i == 1 ) tmp = 0;
		sumh[i] = (sumh[i-1] + tmp);
		if ( i != 1 )
			sumh1[i] = sumh1[i-1] + 1;
	}
	for ( i = 1 ; i <= cnt ; i++ ) {//cal h from 2 to i
		if ( value[i] <= 2 ) continue;
		h0[i] = value[i] - value[i] % 4;//modulo before multiply
		if ( value[i] % 4 >= 1 ) h0[i] += 3;
		if ( value[i] % 4 == 3 ) h0[i] += 1;
		h0[i] -= 4;
		if ( value[i] >= 2 ) h0[i] += 1;
		if ( value[i] == 1 ) h1[i] = 0;
		else if ( value[i] == 2 ) h1[i] = 0;
		else h1[i] = ((value[i]+1)/2-1);
	}
	for ( i = 2 ; i <= tot ; i++ ) {
		for ( j = cnt ; prime[i] * prime[i] <= value[j] ; j-- ) {
			if ( prime[i] % 4 == 1 )
				h0[j] = (h0[j] - 1 * (h0[getpos(value[j]/prime[i])]-sumh[i-1]) );
			else
				h0[j] = (h0[j] - ((h1[getpos(value[j]/prime[i])]-sumh1[i-1]) * 4 - (h0[getpos(value[j]/prime[i])]-sumh[i-1]) ) );
		}
		for ( j = cnt ; prime[i] * prime[i] <= value[j] ; j-- ) {
			h1[j] = ( (h1[j] - 1 * (h1[getpos(value[j]/prime[i])]-sumh1[i-1]) ) );
		}
	}
	for ( i = 1 ; i <= cnt ; i++ )
		h[i] = h0[i] + (i>1?1:0);
}
LL getf ( LL p , LL e ) {
	if ( p % 4 == 1 )
		return 2 * e + 1;
	else return 1;
}
void min25 () {
	LL i , j , e , now , tmp;
	for ( j = cnt ; j >= 1 ; j-- ) g[j] = h[j];
	for ( i = tot ; i >= 1 ; i-- )
		for ( j = cnt ; prime[i]*prime[i]<=value[j];j--)
			for ( e = 1 , now = prime[i];now*prime[i]<=value[j];e++,now=now*prime[i]) {
				g[j]=(g[j]+getf(prime[i],e)*(g[getpos(value[j]/now)]-h[prime[i]])+getf(prime[i],e+1) );
			}
	printf ( "%lld\n" , ((g[cnt]+1)-n)/2 );
}
void work () {
	scanf ( "%lld" , &n );
	predo ();
	min25 ();
	clear ();
}
int main () {
	int t;
	scanf ( "%d" , &t );
	while ( t-- ) work ();
	return 0;
}

