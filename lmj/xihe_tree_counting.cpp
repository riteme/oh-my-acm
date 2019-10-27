/**
 * title: xihe_tree_counting
 * category: 数据结构 
 * description: xihe_tree_counting.md
 */
#include <stdio.h>
#include <algorithm>

typedef long long LL;

using namespace std;

#define ACM_BEGIN
LL n , mod;
LL dp[5][5100];
LL f[5100];
void work () {
	LL i , j , k;
	scanf ( "%lld%lld" , &n , &mod );
	f[1] = dp[1][1] = 1;
	for ( i = 2 ; i <= n ; i++ ) {
		for ( j = 1 ; j < i ; j++ ) {
			for ( k = 4 ; k >= 2 ; k-- ) {
				dp[k][i] = (dp[k][i]+f[j]*dp[k-1][i-j]) % mod;
				if ( k == 4 ) {
					dp[k][i] = (dp[k][i]+f[j]*dp[k][i-j]) % mod;
				}
			}
		}
		f[i] = (dp[2][i]+dp[3][i]+dp[4][i]+dp[4][i]) % mod;
		dp[1][i] = f[i];
	}
	for ( i = 1 ; i <= n ; i++ ) {
		printf ( "%lld\n" , f[i] );
	}
}
#define ACM_END
int main () {
	work ();
	return 0;
}

