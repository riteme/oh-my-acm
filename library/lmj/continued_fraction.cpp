/**
 * title: continued_fraction
 * category: 数论
 * description: continued_fraction.md
 */
long long dec1[1200] , dec2[1200] , len1 , len2;
long long num , dom;
void getfrac ( long long *d , long long &l , long long a , long long b ) {
  l = 1;
  d[1] = a / b;
  a %= b;
  while ( a != 0 ) {
    swap ( a , b );
    d[++l] = a / b;
    a %= b;
}}
void work () {
  long long i;
  getfrac ( dec1 , len1 , a , b );
  getfrac ( dec2 , len2 , c , d );
  dec1[len1+1] = 2147483647777777777ll;
  dec2[len2+1] = 2147483647777777777ll;
  for ( i = 1 ; i <= len1 && i <= len2 ; i++ ) {
    if ( dec1[i] != dec2[i] ) break;
  }
  dec1[i] = min ( dec1[i] , dec2[i] ) + 1;
  num = dec1[i]; dom = 1;
  for ( i-- ; i >= 1 ; i-- ) {
    swap ( num , dom );
    num = num + dom * dec1[i];
  }
  printf ( "%lld %lld\n" , num , dom );
}
