/**
 * title: Pohlig_Hellman
 * category: 数论
 * description: Pohlig_Hellman.md
 */
typedef long long LL;
LL pfactor[1200] , totf;
LL gene[1200];
void exgcd(LL a,LL b,LL &x,LL &y) {
  if(b==0){ x=1; y=0; return;}
  exgcd(b,a%b,x,y);
  LL tp=x;
  x=y; y=tp-a/b*y;
}
LL inv ( LL a , LL mod ) {
  LL x , y;
  exgcd ( a , mod , x , y );
  return (x%mod+mod)%mod;
}
LL qmul ( LL a , LL b , LL m ) {
  a %= m; b %= m;
  LL r = a*b,s=(long double)(a)*b/m;
  return ((r-m*s)%m+m)%m;
}
LL fast_mul ( LL a , LL b , LL c , LL mod ) {
  return qmul(qmul(a,b,mod),c,mod);
}
pair<LL,LL> crt ( pair<LL,LL> a , pair<LL,LL> b ) {
  if ( a.first == -1 ) return b;
  a.first = fast_mul(a.first,b.second,inv(b.second,a.second),a.second*b.second) + fast_mul(b.first,a.second,inv(a.second,b.second),a.second*b.second);
  a.second *= b.second;
  a.first %= a.second;
  return a;
}
LL mpow ( LL f , LL x , LL mod ) {
  LL s = 1;
  while ( x ) {
    if ( x % 2 ) s = qmul(s,f,mod);
    f = qmul(f,f,mod); x >>= 1;
  } return s;
}
pair<LL,LL> solve ( LL g , LL h , LL mod , LL prime , LL e , LL p ) {//mod=prime^e
  LL j , k , r = mpow ( g , mod / prime , p ) , x = 0 , hh;
  LL ret = 0 , nowp = mod / prime , pp = 1;
  gene[0] = 1;
  for ( k = 1 ; k <= prime - 1 ; k++ ) {
    gene[k] = qmul (gene[k-1],r,p);
  }
  for ( k = 0 ; k <= e - 1 ; k++ ) {
    h = qmul(h,inv(mpow(g,x,p),p),p);
    hh = mpow ( h , nowp , p );
    for ( j = 0 ; j <= prime - 1 ; j++ ) {
      if ( gene[j] == hh ) break;
    }
    nowp = nowp / prime;
    x = j * pp;
    ret += x;
    pp = pp * prime;
  } return make_pair(ret,mod);
}
LL getlog ( LL a , LL root , LL p ) {
  LL i , j , tp , tmp;
  pair<LL,LL> ret , rem;
  tp = p - 1;
  rem.first = -1;
  for ( i = 2 ; tp != 1 ; i++ ) {
    if ( tp % i == 0 ) {
      tmp = 1; j = 0;
      while ( tp % i == 0 ) {
        tmp = tmp * i;
        j++; tp /= i;
      }
      ret = solve ( mpow ( root , p / tmp , p ) , mpow ( a , p / tmp , p ) , tmp , i , j , p );
      rem = crt ( rem , ret );
  }} return rem.first;
}
LL getroot ( LL p ) {
  LL i , j , tp = p - 1;
  totf = 0;
  for ( i = 2 ; tp != 1 ; i++ ) {
    if ( tp % i == 0 ) {
      pfactor[++totf] = i;
      while ( tp % i == 0 ) tp /= i;
  }}
  for ( i = 2 ; i < p ; i++ ) {
    for ( j = 1 ; j <= totf ; j++ ) {
      if ( mpow ( i , (p-1)/pfactor[j] , p ) == 1 ) break;
    }
    if ( j == totf + 1 ) return i;
  } return -1;
}
LL work ( LL p , LL a , LL b ) {  // return x, such that a^x = b (mod p)
  LL i , j , rt , la , lb , x , y , g;
  rt = getroot ( p );
  la = getlog ( a , rt , p );  // rt^la = a (mod p)
  lb = getlog ( b , rt , p );
  // x*la = lb (mod p-1)
  g = __gcd ( la , p - 1 );
  exgcd ( la , p - 1 , x , y );
  if ( lb % g != 0 ) return -1;
  x = (x%(p-1)+(p-1))%(p-1);
  return qmul ( x , (lb/g) , (p - 1)/__gcd(la,p-1) );
}
