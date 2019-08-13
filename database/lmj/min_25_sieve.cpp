/**
 * title: min_25_sieve
 * category: 数论
 * description: min_25_sieve.md
 */
typedef long long LL;
const LL NN = 420000;
const LL block = 100000;
const LL mod = 1000000007;
const LL inv2 = 500000004;
LL n, p[1200000] , prime[NN] , tot;
LL value[NN] , cnt , limit , pos[NN];
LL sumh[NN] , h0[NN] , h1[NN];
LL h[NN];  // sum of h[1..value[x]]
LL g[NN];
LL getpos ( LL x ) { return x<=limit?x:pos[n/x]; }
void predo () {
  LL i , j;
  for ( i = 2 ; i <= block ; i++ ) {
    if ( !p[i] )
      prime[++tot] = i;
    for ( j = 1 ; j <= tot && i * prime[j] <= block ; j++ ) {
      p[i*prime[j]] = 1;
      if ( i % prime[j] == 0 ) break;
  }}
  cnt = 0;
  for ( i = 1 ; i * i <= n ; i++ ) value[++cnt] = i;
  i--; limit = i;
  for ( ; i >= 1 ; i-- ) if ( n / i != value[cnt] ) {
    value[++cnt] = n / i;
    pos[i] = cnt;
  }
  for ( i = 1 ; i <= tot ; i++ )
    sumh[i] = (sumh[i-1] + prime[i]) % mod;
  for ( i = 1 ; i <= cnt ; i++ ) {//cal h from 2 to i
    h0[i] = ((value[i]-1)%mod*((value[i]+2)%mod)%mod*inv2) % mod;//modulo before multiply
    h1[i] = (value[i] - 1) % mod;
  }
  for ( i = 1 ; i <= tot ; i++ ) {
    for ( j = cnt ; prime[i] * prime[i] <= value[j] ; j-- ) {
      h0[j] = ( (h0[j] - prime[i] * (h0[getpos(value[j]/prime[i])]-sumh[i-1]) ) % mod );
      if ( h0[j] < 0 ) h0[j] += mod;
      h1[j] = ( (h1[j] - 1 * (h1[getpos(value[j]/prime[i])]-(i-1)) ) % mod );
      if ( h1[j] < 0 ) h1[j] += mod;
  }}
  for ( i = 1 ; i <= cnt ; i++ )//f(p)=p-1
    h[i] = ( h0[i] - h1[i] + mod ) % mod;
}
LL getf ( LL p , LL e ) { return p ^ e; }
void min25 () {
  LL i , j , e , now , tmp;
  for ( j = cnt ; j >= 1 ; j-- ) g[j] = h[j];
  for ( i = tot ; i >= 1 ; i-- )
    for ( j = cnt ; prime[i] * prime[i] <= value[j] ; j-- )
      for ( e = 1 , now = prime[i] ; now * prime[i] <= value[j] ; e++ , now = now * prime[i] )
        g[j] = ( g[j] + getf(prime[i],e) * (g[getpos(value[j]/now)]-h[prime[i]]+mod) + getf(prime[i],e+1) ) % mod;
  printf ( "%lld\n" , (g[cnt] + 1) % mod );
}
void work () {
  scanf ( "%lld" , &n );
  predo ();
  min25 ();
}
