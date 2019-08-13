/**
 * title: block_forest_data_structure
 * category: 图论
 * description: block_forest_data_structure.md
 */
struct node {
  int v , u; node *next;
} pooln[maxn*4] , *gn[maxn];
struct tree {
  int v; tree *next;
} poolt[maxn*4] , *gt[maxn*2];
int topt , topn;
int n , m , tot;
int kind[maxn*2] , dfn[maxn] , low[maxn] , index;
stack <node*> st;
void add ( int u , int v ) {
  node *tmp = &pooln[++topn];
  tmp -> v = v; tmp -> u = u; tmp -> next = gn[u]; gn[u] = tmp;
}
void addt ( int u , int v ) {
  tree *tmp = &poolt[++topt];
  tmp -> v = v; tmp -> next = gt[u]; gt[u] = tmp;
}
void tarjan ( int i , int from ) {
  dfn[i] = low[i] = ++index;
  for ( node *j = gn[i] ; j ; j = j -> next ) if ( j -> v != from ) {
    if ( !dfn[j->v] || dfn[i] > dfn[j->v] ) st.push(j);
    if ( !dfn[j->v] ) {
      tarjan ( j -> v , i );
      low[i] = min ( low[i] , low[j->v] );
      if ( low[j->v] >= dfn[i] ) {
        if ( st.top() == j ) {
          addt ( i , j -> v , j -> prob );
          addt ( j -> v , i , j -> prob );
          st.pop();
        } else {
          tot++;
          kind[tot] = 1;
          while ( st.top() != j ) {
            node *k = st.top ();
            st.pop();
            addt ( tot , k -> u , k -> prob );
            addt ( k -> u , tot , k -> prob );
          }
          addt ( tot , i , j -> prob );
          addt ( i , tot , j -> prob );
          st.pop();
    }}}
    else low[i] = min ( low[i] , dfn[j->v] );
}}
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