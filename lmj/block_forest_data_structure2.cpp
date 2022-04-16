/**
 * title: block_forest_data_structure2
 * category: Í¼ÂÛ 
 * description: dev/null
 */
struct node {
	int v , u;
	node *next;
} pooln[maxn*4] , *gn[maxn];
struct tree {
	int v;
	tree *next;
} poolt[maxn*4] , *gt[maxn*2];
int topt , topn;
int n , m , tot;
int kind[maxn*2] , dfn[maxn] , low[maxn] , index;
stack <int> st;
void add ( int u , int v ) {
	node *tmp = &pooln[++topn];
	tmp -> v = v; tmp -> u = u; tmp -> next = gn[u]; gn[u] = tmp;
}
void addt ( int u , int v ) {
	tree *tmp = &poolt[++topt];
	tmp -> v = v; tmp -> next = gt[u]; gt[u] = tmp;
	//printf ( "@%d %d\n" , u , v );
}
void tarjan ( int i , int from ) {
	dfn[i] = low[i] = ++index;
	st.push(i);
	for ( node *j = gn[i] ; j ; j = j -> next ) if ( j -> v != from ) {
		if ( !dfn[j->v] ) {
			tarjan ( j -> v , i );
			low[i] = min ( low[i] , low[j->v] );
			if ( low[j->v] >= dfn[i] ) {
				tot++;
				kind[tot] = 1;
				addt ( i , tot , 0 );
				addt ( tot , i , 0 );
				do {
					int now = st.top();
					st.pop();
					addt ( tot , now , 0 );
					addt ( now , tot , 0 );
				} while ( now != j -> v );
			}
		}
		else low[i] = min ( low[i] , dfn[j->v] );
	}
}
void work () {
	int i , u , v , a , b;
	scanf ( "%d%d" , &n , &m );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d%d%d" , &u , &v , &a , &b );
		add ( u , v );
		add ( v , u );
	}
	tot = n;
	for ( i = 1 ; i <= n ; i++ ) kind[i] = 0;
	tarjan ( 1 , -1 );
}

