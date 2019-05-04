/**
 * title: euler_tour
 * category: 图论
 * description: /dev/null
 */
#include <stdio.h>
#include <algorithm>
#include <stack>

using namespace std;

const int maxm = 70000;
struct node {
    int v , taboo , f;
    node *next;
} pool[maxm*2] , *g[maxm];
int top;
int n;
int ans[maxm*2] , index;
void add ( int u , int v , int f ) {
    //printf ( "%d %d\n" , u , v );
    node *tmp = &pool[++top];
    tmp -> v = v; tmp -> f = f; tmp -> next = g[u]; g[u] = tmp;
}
#define ACM_BEGIN
stack < int > s;
void dfs ( int i ) {
    for ( node *j = g[i] ; j ; j = j -> next ) if ( !j -> taboo ) {
        s.push ( j -> f );
        j -> taboo = 1;
        dfs ( j -> v );
        ans[++index] = s.top ();
        s.pop ();
    }
}
#define ACM_END
void work () {
    int i;
    scanf ( "%d" , &n );
    for ( i = 0 ; i <= (1<<(n-1)) - 1 ; i++ ) {
        add ( i , (i*2) & ((1<<(n-1))-1) , 0 );
        add ( i , (i*2+1) & ((1<<(n-1))-1) , 1 );
    }
    dfs ( 0 );
    for ( i = 1 ; i <= index ; i++ ) printf ( "%d" , ans[i] );
    printf ( "\n" );
}
int main () {
    work ();
    return 0;
}
