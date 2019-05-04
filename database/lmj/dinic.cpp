/**
 * title: dinic
 * category: 网络流
 * description: /dev/null
 */

#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
    int v , f;
    node *next , *rev;
} pool[120000] , *g[1000];
int top;
int n;
int sum;
int a[60] , b[60];
int map[60][60];
int level[1000];
void clear () {
    int i;
    sum = 0;
    for ( i = 1 ; i <= top ; i++ ) pool[i].v = pool[i].f = 0, pool[i].next = pool[i].rev = NULL;
    for ( i = 1 ; i <= 200 ; i++ ) g[i] = NULL;
    top = 0;
}
#define ACM_BEGIN
void add ( int u , int v , int f ) {
    node *tmp1 = &pool[++top] , *tmp2 = &pool[++top];
    tmp1 -> v = v; tmp1 -> f = f; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
    tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
bool makelevel () {
    int i , k;
    queue < int > q;
    for ( i = 1 ; i <= 1 + n + n + 1 ; i++ ) level[i] = -1;
    level[1] = 1; q.push ( 1 );
    while ( q.size () != 0 ) {
        k = q.front (); q.pop ();
        for ( node *j = g[k] ; j ; j = j -> next )
            if ( j -> f && level[j->v] == -1 ) {
                level[j->v] = level[k] + 1;
                q.push ( j -> v );
                if ( j -> v == 1 + n + n + 1 ) return true;
            }
    }
    return false;
}
int find ( int k , int key ) {
    if ( k == 1 + n + n + 1 ) return key;
    int i , s = 0;
    for ( node *j = g[k] ; j ; j = j -> next )
        if ( j -> f && level[j->v] == level[k] + 1 && s < key ) {
            i = find ( j -> v , min ( key - s , j -> f ) );
            j -> f -= i;
            j -> rev -> f += i;
            s += i;
        }
    if ( s == 0 ) level[k] = -1;
    return s;
}
void dinic () {
    int ans = 0;
    while ( makelevel () == true ) ans += find ( 1 , 99999 );
    //printf ( "%d\n" , ans );
    if ( ans == sum ) printf ( "^_^\n" );
    else printf ( "T_T\n" );
}
#define ACM_END
void work () {
    int i , j , x;
    clear ();
    scanf ( "%d" , &n );
    for ( i = 1 ; i <= n ; i++ ) scanf ( "%d" , &a[i] );
    for ( i = 1 ; i <= n ; i++ ) scanf ( "%d" , &b[i] );
    for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= n ; j++ ) scanf ( "%d" , &map[i][j] );
    for ( i = 1 ; i <= n ; i++ ) {
        if ( a[i] == 1 ) add ( 1 + n + i , 1 + n + n + 1 , 1 );
    }
    for ( i = 1 ; i <= n ; i++ ) {
        if ( (a[i]==0) || (a[i]==1 && b[i]==0) ) add ( 1 , 1 + i , 1 ), sum++;
    }
    for ( i = 1 ; i <= n ; i++ ) for ( j = 1 ; j <= n ; j++ ) {
        if ( map[i][j] == 1 || i == j ) add ( 1 + i , 1 + n + j , 1 );
    }
    dinic ();
}
int main () {
    //FILE *fpw = freopen ( "bzoj1433.out" , "w" , stdout );
    int t;
    scanf ( "%d" , &t );
    while ( t-- ) work ();
    return 0;
}
