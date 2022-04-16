/**
 * title: pam_end_modify
 * category: ×Ö·û´® 
 * description: pam_end_modify.md
 */
struct quick {
	long long f[30];
};
struct node {
	long long len , cnt,ch[30] , fail;
	quick q;
} p[NN];
long long top,n,last,m,l;
long long lst[NN];
char z[NN] , s[11];
void append ( long long i ) {
	long long tmp;
	if ( z[i] != z[i-p[last].len-1] )
		last = p[last].q.f[z[i]-'a'+1];
	if ( !p[last].ch[z[i]-'a'+1] ) {
		p[last].ch[z[i]-'a'+1] = ++top;
		p[top].len = p[last].len + 2;
		tmp = p[last].q.f[z[i]-'a'+1];
		if ( p[top].len > 1 && p[tmp].ch[z[i]-'a'+1] ) p[top].fail = p[tmp].ch[z[i]-'a'+1];
		else p[top].fail = 1;
		p[top].q = p[p[top].fail].q;
		p[top].q.f[z[i-p[p[top].fail].len]-'a'+1] = p[top].fail;
	}
	last = p[last].ch[z[i]-'a'+1];
	p[last].cnt++;
	lst[i] = last;
}
void pop () {
	p[lst[l]].cnt--;
	last = lst[l-1];
	l--;
}
void work () {
	long long i , op;
	scanf ( "%lld%lld" , &n , &m );
	scanf ( "%s" , z + 1 );
	l = strlen ( z + 1 );
	top = 2;
	p[1].fail = 2; p[2].fail = 1;
	p[1].len = 0; p[2].len = -1;
	for ( i = 1 ; i <= 26 ; i++ ) {
		p[1].q.f[i] = 2;
		p[2].q.f[i] = 1;
	}
	
	z[0] = '$';
	last = 2;
	lst[0] = 2;
	for ( i = 1 ; i <= l ; i++ ) {
		append ( i );
	}
	printf ( "%lld\n" , ans );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%lld" , &op );
		if ( op == 1 ) {
			scanf ( "%s" , s + 1 );
			z[++l] = s[1];
			append ( l );
		}
		else {
			pop ();
		}
		printf ( "%lld\n" , ans );
	}
}
