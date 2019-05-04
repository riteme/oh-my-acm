/**
 * title: 左偏树
 * category: 数据结构
 * description: leftist_tree.md
 */

#include <stdio.h>
#include <algorithm>

using namespace std;

const int maxn = 1001000;
#define ACM_BEGIN
struct node {
    int x , i , dist;
    node *ll , *rr;
} pool[maxn] , *t[maxn];
int n , m;
int a[maxn];
int c[maxn] , f[maxn];
int getdist ( node *id ) {
    if ( id == NULL ) return -1;
    return id -> dist;
}
node *merge ( node *id1 , node *id2 ) {
    if ( id1 == NULL ) return id2;
    if ( id2 == NULL ) return id1;
    if ( id1 -> x > id2 -> x ) swap ( id1 , id2 );
    id1 -> rr = merge ( id1 -> rr , id2 );
    if ( getdist ( id1 -> ll ) < getdist ( id1 -> rr ) ) swap ( id1 -> ll , id1 -> rr );
    id1 -> dist = getdist ( id1 -> rr ) + 1;
    return id1;
}
int find ( int x ) {
    int i , t;
    for ( i = x ; c[i] > 0 ; i = c[i] ) ;
    while ( x != i ) {
        t = c[x];
        c[x] = i;
        x = t;
    }
    return i;
}
void Union ( int x , int y ) {
    t[x] = merge ( t[x] , t[y] );
    c[x] += c[y];
    c[y] = x;
}
#define ACM_END
void work () {
    int i , x , y , tmp;
    char op[3];
    scanf ( "%d" , &n );
    for ( i = 1 ; i <= n ; i++ ) {
        scanf ( "%d" , &a[i] );
        t[i] = &pool[i];
        t[i] -> x = a[i];
        t[i] -> i = i;
        c[i] = -1;
    }
    scanf ( "%d" , &m );
    for ( i = 1 ; i <= m ; i++ ) {
        scanf ( "%s%d" , op + 1 , &x );
        if ( op[1] == 'M' ) {
            scanf ( "%d" , &y );
            if ( f[x] == 0 && f[y] == 0 && find ( x ) != find ( y ) ) {
                Union ( find ( x ) , find ( y ) );
            }
        }
        else {
            if ( f[x] == 1 ) {
                printf ( "0\n" );
                continue;
            }
            tmp = find ( x );
            //printf ( "%d\n" , tmp );
            printf ( "%d\n" , t[tmp] -> x );
            f[t[tmp]->i] = 1;
            t[tmp] = merge ( t[tmp] -> ll , t[tmp] -> rr );
        }
    }
}
int main () {
    //FILE *fpr = freopen ( "bzoj1455.in" , "r" , stdin );
    //FILE *fpw = freopen ( "bzoj1455.out" , "w" , stdout );
    work ();
    return 0;
}
