/**
 * title: lct
 * category: 数据结构
 * description: /dev/null
 */

#include <stdio.h>
#include <algorithm>

using namespace std;

//long long
const long long maxn = 120000;
const long long mod = 51061;
#define ACM_BEGIN
struct node {
  long long x;
  long long lm , lp , rev;
  long long s , siz;
  long long ch[4] , fa;
} p[maxn];
#define ACM_END
long long n , q;
char z[12];
void output () {
  for ( long long i = 1 ; i <= n ; i++ )
    printf ( "i%lld fa%lld l%lld r%lld x%lld lm%lld lp%lld rev%lld s%lld siz%lld\n" , i , p[i].fa , p[i].ch[0] , p[i].ch[1] , p[i].x , p[i].lm , p[i].lp , p[i].rev , p[i].s , p[i].siz );
}
void update ( long long x ) {
  p[x].s = p[x].x; p[x].siz = 1;
  if ( p[x].ch[0] ) {
    p[x].s += p[p[x].ch[0]].s; p[x].s %= mod;
    p[x].siz += p[p[x].ch[0]].siz;
  }
  if ( p[x].ch[1] ) {
    p[x].s += p[p[x].ch[1]].s; p[x].s %= mod;
    p[x].siz += p[p[x].ch[1]].siz;
  }
}
void pushdown ( long long x ) {
  if ( p[x].rev ) {
    if ( p[x].ch[0] ) {
      swap ( p[p[x].ch[0]].ch[0] , p[p[x].ch[0]].ch[1] );
      p[p[x].ch[0]].rev ^= 1;
    }
    if ( p[x].ch[1] ) {
      swap ( p[p[x].ch[1]].ch[0] , p[p[x].ch[1]].ch[1] );
      p[p[x].ch[1]].rev ^= 1;
    }
    p[x].rev = 0;
  }
  if ( p[x].lm != 1 ) {
    if ( p[x].ch[0] ) {
      p[p[x].ch[0]].x *= p[x].lm; p[p[x].ch[0]].x %= mod;
      p[p[x].ch[0]].lm *= p[x].lm; p[p[x].ch[0]].lm %= mod;
      p[p[x].ch[0]].lp *= p[x].lm; p[p[x].ch[0]].lp %= mod;
      p[p[x].ch[0]].s *= p[x].lm; p[p[x].ch[0]].s %= mod;
    }
    if ( p[x].ch[1] ) {
      p[p[x].ch[1]].x *= p[x].lm; p[p[x].ch[1]].x %= mod;
      p[p[x].ch[1]].lm *= p[x].lm; p[p[x].ch[1]].lm %= mod;
      p[p[x].ch[1]].lp *= p[x].lm; p[p[x].ch[1]].lp %= mod;
      p[p[x].ch[1]].s *= p[x].lm; p[p[x].ch[1]].s %= mod;
    }
    p[x].lm = 1;
  }
  if ( p[x].lp ) {
    if ( p[x].ch[0] ) {
      p[p[x].ch[0]].x += p[x].lp; p[p[x].ch[0]].x %= mod;
      p[p[x].ch[0]].lp += p[x].lp; p[p[x].ch[0]].lp %= mod;
      p[p[x].ch[0]].s += p[x].lp * p[p[x].ch[0]].siz; p[p[x].ch[0]].s %= mod;
    }
    if ( p[x].ch[1] ) {
      p[p[x].ch[1]].x += p[x].lp; p[p[x].ch[1]].x %= mod;
      p[p[x].ch[1]].lp += p[x].lp; p[p[x].ch[1]].lp %= mod;
      p[p[x].ch[1]].s += p[x].lp * p[p[x].ch[1]].siz; p[p[x].ch[1]].s %= mod;
    }
    p[x].lp = 0;
  }
}
#define ACM_BEGIN
void cut ( long long x , long long kind ) {
  p[p[x].ch[kind]].fa *= -1;
  p[x].ch[kind] = 0;
  update ( x );
}
void down ( long long x ) {
  if ( p[x].fa > 0 ) down ( p[x].fa );
  pushdown ( x );
}
void rotate ( long long x , long long kind ) {
  long long y = p[x].fa;
  if ( p[y].fa > 0 ) p[p[y].fa].ch[y==p[p[y].fa].ch[1]] = x;
  p[x].fa = p[y].fa;
  if ( p[x].ch[kind^1] ) p[p[x].ch[kind^1]].fa = y;
  p[y].ch[kind] = p[x].ch[kind^1];
  p[y].fa = x;
  p[x].ch[kind^1] = y;
  update ( y ); update ( x );
}
void splay ( long long x ) {
  down ( x );
  for ( ; p[x].fa > 0 ; rotate ( x , x==p[p[x].fa].ch[1]) )
    if ( p[p[x].fa].fa > 0 && (x==p[p[x].fa].ch[1]) == (p[x].fa==p[p[p[x].fa].fa].ch[1]) )
      rotate ( p[x].fa , x==p[p[x].fa].ch[1] );
}
void access ( long long x ) {
  splay ( x );
  cut ( x , 1 );
  for ( ; p[x].fa != 0 ; ) {
    splay ( -p[x].fa );
    cut ( -p[x].fa , 1 );
    p[-p[x].fa].ch[1] = x;
    update ( -p[x].fa );
    p[x].fa *= -1;
    splay ( x );
  }
}
void makeroot ( long long x ) {
  access ( x );
  p[x].rev ^= 1;
  swap ( p[x].ch[0] , p[x].ch[1] );
}
void link ( long long x , long long y ) {
  makeroot ( y );
  p[y].fa = -x;
}
#define ACM_END
void work () {
  long long i , u , v , c , u1 , v1;
  scanf ( "%lld%lld" , &n , &q );
  for ( i = 1 ; i <= n ; i++ ) p[i].x = p[i].s = p[i].lm = 1;
  for ( i = 1 ; i < n ; i++ ) {
    scanf ( "%lld%lld" , &u , &v );
    link ( u , v );
  }
  for ( i = 1 ; i <= q ; i++ ) {
    scanf ( "%s%lld%lld" , z + 1 , &u , &v );
    if ( z[1] == '+' ) {
      scanf ( "%lld" , &c );
      makeroot ( u );
      access ( v );
      p[v].lp += c; p[v].lp %= mod;
      p[v].s += p[v].siz * c; p[v].s %= mod;
      p[v].x += c; p[v].x %= mod;
    }
    if ( z[1] == '-' ) {
      scanf ( "%lld%lld" , &u1 , &v1 );
      makeroot ( u );
      access ( v );
      p[u].fa = 0; p[v].ch[0] = 0;
      update ( v );
      link ( u1 , v1 );
    }
    if ( z[1] == '*' ) {
      scanf ( "%lld" , &c );
      makeroot ( u );
      access ( v );
      p[v].lp *= c; p[v].lp %= mod;
      p[v].lm *= c; p[v].lm %= mod;
      p[v].s *= c; p[v].s %= mod;
      p[v].x *= c; p[v].x %= mod;
    }
    if ( z[1] == '/' ) {
      makeroot ( u );
      access ( v );
      printf ( "%lld\n" , p[v].s % mod );
    }
    //output ();
  }
}
int main () {
  //FILE *fpr = freopen ( "bzoj2631.in" , "r" , stdin );
  //FILE *fpw = freopen ( "bzoj2631.out" , "w" , stdout );
  work ();
  return 0;
}
