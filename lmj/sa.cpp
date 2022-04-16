/**
 * title: suffix_array
 * category: ×Ö·û´®
 * description: null
 */
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxn = 120000;
struct so {
	int a , b , i;
} A[maxn] , B[maxn];
int n;
char z[maxn];
int f[30];
int rank[maxn] , sa[maxn] , height[maxn];
int cnt[maxn];
void work () {
	int i , j , k, l;
	scanf ( "%s" , z + 1 );
	n = strlen ( z + 1 );
	for ( i = 1 ; i <= n ; i++ ) f[z[i]-'a'+1] = 1;
	for ( i = 1 ; i <= 26 ; i++ ) f[i] += f[i-1];
	for ( i = 1 ; i <= n ; i++ ) rank[i] = f[z[i]-'a'+1];
	l = 1;
	while ( l <= n ) {
		for ( i = 1 ; i <= n ; i++ ) A[i].a = rank[i], A[i].b = i+l>n?0:rank[i+l], A[i].i = i;
		for ( i = 1 ; i <= n ; i++ ) cnt[i] = 0;
		for ( i = 1 ; i <= n ; i++ ) cnt[A[i].b]++;
		for ( i = 1 ; i <= n ; i++ ) cnt[i] += cnt[i-1];
		for ( i = n ; i >= 1 ; i-- ) B[cnt[A[i].b]--] = A[i];
		for ( i = 1 ; i <= n ; i++ ) cnt[i] = 0;
		for ( i = 1 ; i <= n ; i++ ) cnt[B[i].a]++;
		for ( i = 1 ; i <= n ; i++ ) cnt[i] += cnt[i-1];
		for ( i = n ; i >= 1 ; i-- ) A[cnt[B[i].a]--] = B[i];
		for ( i = 1 ; i <= n ; i++ ) rank[A[i].i] = (A[i].a==A[i-1].a&&A[i].b==A[i-1].b&&i!=1)?rank[A[i-1].i]:rank[A[i-1].i]+1;
		l = l * 2;
	}
	for ( i = 1 ; i <= n ; i++ ) sa[rank[i]] = i;
	k = 0;
	for ( i = 1 ; i <= n ; height[rank[i++]] = k )
		for ( k=k?k-1:0 , j = sa[rank[i]-1] ; z[i+k] == z[j+k] ; k++ ) ;
	for ( i = 1 ; i <= n ; i++ ) printf ( "%d%c" , sa[i] , i==n?'\n':' ' );
	for ( i = 2 ; i <= n ; i++ ) printf ( "%d%c" , height[i] , i==n?'\n':' ' );
}
int main () {
	work ();
	return 0;
}

