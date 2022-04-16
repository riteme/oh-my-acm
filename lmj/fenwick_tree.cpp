/**
 * title: fenwick_tree
 * category: 数据结构 
 * description: fenwick_tree.md
 */
int n , m , k;
int a[510][510];
int s[510][510] , si[510][510] , sj[510][510] , sij[510][510];
int lowbit ( int x ) {
	return x & (-x);
}
void add ( int x , int y , int del ) {
	int i , j;
	for ( i = x ; i <= n ; i += lowbit(i) )
		for ( j = y ; j <= m ; j += lowbit(j) ) {
			s[i][j] = (s[i][j] + del) % mod;
			si[i][j] = (si[i][j] + del * x) % mod;
			sj[i][j] = (sj[i][j] + del * y) % mod;
			sij[i][j] = (sij[i][j] + del * x * y) % mod;
		}
}
void range_add ( int x1 , int y1 , int x2 , int y2 , int del ) {
	add ( x1 , y1 , del );
	add ( x1 , y2 + 1 , -del );
	add ( x2 + 1 , y1 , -del );
	add ( x2 + 1 , y2 + 1 , del );
}
int query ( int x , int y ) {
	int i , j , ret = 0;
	for ( i = x ; i ; i -= lowbit(i) )
		for ( j = y ; j ; j -= lowbit(j) ) {
			ret += (x+1) * (y+1) % mod * s[i][j] % mod;
			ret -= (x+1) * sj[i][j] % mod;
			ret -= (y+1) * si[i][j] % mod;
			ret += sij[i][j];
			ret = ret % mod;
		}
	if ( ret < 0 ) ret += mod;
	return ret;
}
int range_query ( int x1 , int y1 , int x2 , int y2 ) {
	int ret;
	ret = (query(x2,y2) - query (x1-1,y2) - query (x2,y1-1) + query (x1-1,y1-1)) % mod;
	if ( ret < 0 ) ret += mod;
	return ret;
}
