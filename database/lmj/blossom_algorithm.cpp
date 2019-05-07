/**
 * title: blossom algorithm
 * category: 图论
 * description: /dev/null
 */
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
#define ACM_BEGIN
const int maxn = 510;
struct node {
  int v;
  node *next;
} pool[maxn*maxn*2] , *g[maxn];
int top,n , m,match[maxn];
int kind[maxn] , pre[maxn] , vis[maxn] , c[maxn];
queue < int > q;
int f[maxn],ans;
void add ( int u , int v ) {node *tmp = &pool[++top];tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;}
int find ( int x ) {int i , t;for ( i = x ; c[i] > 0 ; i = c[i] ) ;while ( c[x] > 0 ) {t = c[x];c[x] = i;x = t;}return i;}
void getpath ( int x , int tar , int root ) {
  int t;
  while ( x != root ) {t = match[x];match[tar] = x;match[x] = tar;tar = t;x = pre[t];}
  match[tar] = x;match[x] = tar;
}
int lca ( int u , int v , int root ) {
  int i;for ( i = 1 ; i <= n ; i++ ) f[i] = 0;
  while ( find ( u ) != root ) {u = find ( u );f[u] = 1;if ( !match[u] ) break;u = pre[match[u]];}
  f[root] = 1;
  while ( find ( v ) != root ) {v = find ( v );if ( f[v] == 1 ) return v;if ( !match[v] ) break;v = pre[match[v]];}
  return root;
}
void blossom ( int x , int y , int l ) {
  while ( find ( x ) != l ) {pre[x] = y;y = match[x];if ( kind[match[x]] == 2 ) {kind[match[x]] = 1;q.push ( match[x] );}if ( find ( x ) == x ) c[find(x)] = l;if ( find ( match[x] ) == match[x] ) c[find(match[x])] = l;x = pre[y];}
}
void bfs ( int x ) {
  int k , i , z;
  for ( i = 1 ; i <= n ; i++ ) {
    kind[i] = pre[i] = vis[i] = 0;c[i] = -1;
  }
  while ( q.size () ) q.pop ();q.push ( x );kind[x] = 1; vis[x] = 1;
  while ( q.size () ) {
    k = q.front (); q.pop ();
    for ( node *j = g[k] ; j ; j = j -> next ) {
      if ( !vis[j->v] ) {
        if ( !match[j->v] ) {
          getpath ( k , j -> v , x );
          return ;
        }
        else {
          kind[j->v] = 2;
          kind[match[j->v]] = 1;
          pre[j->v] = k;
          vis[j->v] = 1; vis[match[j->v]] = 1;
          q.push ( match[j->v] );
      }}
      else {
        if ( find ( k ) == find ( j -> v ) ) continue;
        if ( kind[find(j->v)] == 1 ) {
          z = lca ( k , j -> v , x );
          blossom ( k , j -> v , z );
          blossom ( j -> v , k , z );
}}}}}
void work () {
  int i , u , v;
  scanf ( "%d%d" , &n , &m );
  for ( i = 1 ; i <= m ; i++ ) {
    scanf ( "%d%d" , &u , &v );
    add ( u , v ); add ( v , u );
  }
  for ( i = 1 ; i <= n ; i++ ) {
    if ( !match[i] ) bfs ( i );
  }
  for ( i = 1 ; i <= n ; i++ ) if ( match[i] ) ans++;
  printf ( "%d\n" , ans / 2 );
  for ( i = 1 ; i <= n ; i++ ) printf ( "%d%c" , match[i] , i==n?'\n':' ' );
}
#define ACM_END
int main () {
  work ();
  return 0;
}
