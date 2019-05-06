/**
 * title: ntt
 * category: 数据结构
 * description: /dev/null
 */
#include <stdio.h>
#include <algorithm>
using namespace std;
const long long maxn = 120000;
const long long mod = 998244353;
const long long omega = 3;
long long a[maxn*4] , b[maxn*4] , c[maxn*4] , d[maxn*4];
long long n , m , N , in;
long long pow ( long long f , long long x ) {long long s = 1;while ( x ) {if ( x % 2 ) s = (s*f) % mod;f = (f*f) % mod; x >>= 1;}return s;}
long long inv ( long long x ) {return pow ( x , mod - 2 );}
long long rev ( long long x ) {long long i , y;i = 1; y = 0;while ( i < N ) {y = y * 2 + (x%2);i <<= 1; x >>= 1;}return y;}
void br ( long long *x ) {long long i;for ( i = 0 ; i < N ; i++ ) d[rev(i)] = x[i];for ( i = 0 ; i < N ; i++ ) x[i] = d[i];}
void FFT ( long long *x , long long f ) {
  long long i , j , s , k;
  long long w , wm , u , t;
  br ( x );
  for ( s = 2 ; s <= N ; s *= 2 ) {
    k = s / 2;
    wm = pow ( omega , (mod-1) / s );
    if ( f == -1 ) wm = inv ( wm );
    for ( i = 0 ; i < N ; i += s ) {
      w = 1;
      for ( j = 1 ; j <= k ; j++ ) {
        u = x[i+j-1]; t = (x[i+j-1+k]*w) % mod;
        x[i+j-1] = (u + t) % mod;
        x[i+j-1+k] = (u - t + mod) % mod;
        w = (w*wm) % mod;
      }
    }
  }
  if ( f == -1 ) for ( i = 0 ; i < N ; i++ ) x[i] = (x[i] * in) % mod;
}
void work () {
  long long i;
  scanf ( "%lld%lld" , &n , &m );
  N = 1;
  while ( N < n + m + 2 ) N = N * 2;
  for ( i = 0 ; i <= n ; i++ ) scanf ( "%lld" , &a[i] );
  for ( i = 0 ; i <= m ; i++ ) scanf ( "%lld" , &b[i] );
  in = inv ( N );
  FFT ( a , 1 ); FFT ( b , 1 );
  for ( i = 0 ; i < N ; i++ ) c[i] = (a[i]*b[i]) % mod;
  FFT ( c , -1 );
  for ( i = 0 ; i <= n + m ; i++ ) printf ( "%lld%c" , c[i] , i==n+m?'\n':' ' );
}
int main () {
  work ();
  return 0;
}

