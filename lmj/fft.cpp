/**
 * title: fft
 * category: 数据结构
 * description: /dev/null
 */
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

#define ACM_BEGIN
const int maxn = 120000;
const double pi = acos(-1);
struct complex {
  double r , i;
} a[maxn*4] , b[maxn*4] , c[maxn*4] , d[maxn*4];
complex operator + ( complex x1 , complex x2 ) {complex y;y.r = x1.r + x2.r;y.i = x1.i + x2.i;return y;}
complex operator - ( complex x1 , complex x2 ) {complex y;y.r = x1.r - x2.r;y.i = x1.i - x2.i;return y;}
complex operator * ( complex x1 , complex x2 ) {complex y;y.r = x1.r * x2.r - x1.i * x2.i;y.i = x1.r * x2.i + x1.i * x2.r;return y;}
int n , m , N;
int rev ( int x ) {int i , y;i = 1; y = 0;while ( i < N ) {y = y * 2 + (x%2);x >>= 1; i <<= 1;}return y;}
void br ( complex *x ) {int i;for ( i = 0 ; i < N ; i++ ) d[rev(i)] = x[i];for ( i = 0 ; i < N ; i++ ) x[i] = d[i];}
void FFT ( complex *x , int f ) {
  int i , j , s , k;
  complex w , wm , u , t;
  br ( x );
  for ( s = 2 ; s <= N ; s *= 2 ) {
    k = s / 2;
    wm.r = cos(2*pi/s); wm.i = sin(2*pi/s) * f;
    for ( i = 0 ; i < N ; i += s ) {
      w.r = 1.0; w.i = 0.0;
      for ( j = 1 ; j <= k ; j++ ) {
        u = x[i+j-1]; t = x[i+j-1+k] * w;
        x[i+j-1] = u + t;
        x[i+j-1+k] = u - t;
        w = w * wm;
  }}}
  if ( f == -1 ) for ( i = 0 ; i < N ; i++ ) x[i].r = x[i].r / N;
}
void work () {
  int i;
  scanf ( "%d%d" , &n , &m );
  N = 1;
  while ( N < n + m + 2 ) N = N * 2;
  for ( i = 0 ; i <= n ; i++ ) scanf ( "%lf" , &a[i].r );
  for ( i = 0 ; i <= m ; i++ ) scanf ( "%lf" , &b[i].r );
  FFT ( a , 1 ); FFT ( b , 1 );
  for ( i = 0 ; i < N ; i++ ) c[i] = a[i] * b[i];
  FFT ( c , -1 );
  for ( i = 0 ; i <= n + m ; i++ ) printf ( "%d%c" , int (c[i].r + 0.5) , i==n+m?'\n':' ' );
}
#define ACM_END
int main () {
  work ();
  return 0;
}

