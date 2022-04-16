/**
 * title: segment_tree_beats
 * category: 数据结构
 * description: segment_tree_beats.md
 */
#include <stdio.h>
#include <algorithm>

using namespace std;

struct node {
    int l , r;
    int lazy;
    int xr , num[32];
    int mn , mn2 , cnt;
    node *ll , *rr;
} pool[410000] , *t;
int top;
int n , q;
int a[220000];
int maxbit ( int x ) {
    int i;
    for ( i = 29 ; i >= 0 ; i-- ) {
        if ( x & (1<<i) ) return i;
    }
    return 0;
}
void update ( node *id ) {
    id -> xr = id ->ll -> xr ^ id ->rr ->xr;
    for ( int i = 0 ; i <= 29 ; i++ ) {
        id -> num[i] = id -> ll ->num[i] +id -> rr->num[i];
    }
    id -> mn = min (id ->ll->mn, id->rr->mn);
    id -> cnt = 0;
    if ( id -> ll -> mn == id -> mn ) {
        id -> cnt += id -> ll ->cnt;
    }
    if ( id -> rr -> mn == id -> mn ) {
        id -> cnt += id -> rr ->cnt;
    }
    int m2;
    if ( id -> ll -> mn == id ->mn ) {
        m2 = id -> ll ->mn2;
    }
    else m2 = id ->ll->mn;
    if (id ->rr->mn==id->mn)
        m2 = min (m2,id->rr->mn2);
    else m2 = min(m2,id->rr->mn);
    id ->mn2 = m2;
}
void pushdown ( node *id ) {
    if ( id -> lazy ) {
        if ( id ->ll->mn <= id->lazy ) {
            id -> ll -> lazy = id->lazy;
            if ( id -> ll -> cnt % 2 == 1 ) {
                id -> ll -> xr ^= id -> ll -> mn ^id->lazy;
            }
            int bt;
            if (id -> ll ->mn != 0 ) {
                bt = maxbit (id -> ll -> mn);
                for (int i = bt ; i >= 0 ; i-- ) {
                    if ( id -> ll ->mn & (1<<i) )
                        id -> ll -> num[i] -= id ->ll ->cnt;
                }
            }
            bt = maxbit (id->ll->lazy);
            for (int i = bt ; i >= 0 ; i-- ) {
                if ( id->lazy & (1<<i) )
                    id -> ll ->num[i] += id ->ll->cnt;
            }
            id -> ll -> mn = id->lazy;
        }


        if ( id ->rr->mn <= id->lazy ) {
            id -> rr -> lazy = id->lazy;
            if ( id -> rr -> cnt % 2 == 1 ) {
                id -> rr -> xr ^= id -> rr -> mn ^id->lazy;
            }
            int bt;
            if (id -> rr ->mn != 0 ) {
                bt = maxbit (id -> rr -> mn);
                for (int i = bt ; i >= 0 ; i-- ) {
                    if ( id -> rr ->mn & (1<<i) )
                        id -> rr -> num[i] -= id ->rr ->cnt;
                }
            }
            bt = maxbit (id->rr->lazy);
            for (int i = bt ; i >= 0 ; i-- ) {
                if ( id->lazy & (1<<i) )
                    id -> rr ->num[i] += id ->rr->cnt;
            }
            id -> rr -> mn = id->lazy;
        }


        id -> lazy = 0;
    }
}
void changepoint (node *id , int x ) {
    id -> mn = x;
    id -> cnt = 1;
    id -> mn2 = 2147483647;
    id -> xr = x;
    if ( x != 0 ) {
        int bt = maxbit ( x );
        for ( int i = bt ; i >= 0 ; i-- ) {
            if ( x & (1<<i) ) id->num[i] = 1;
            else id ->num[i] = 0;
        }
    }
}
void buildtree ( node *id , int l , int r ) {
    id -> l = l; id -> r = r;
    id -> lazy = 0;
    if ( l == r ) {
        changepoint ( id  , a[l] );
        return ;
    }
    id ->ll = &pool[++top];
    id ->rr = &pool[++top];
    int mid =(l+r)/2;
    buildtree ( id -> ll , l , mid );
    buildtree (id -> rr , mid + 1 , r );
    update (id );
}
void change (node *id , int l , int  r , int x ) {
    if ( id ->l != id -> r ) pushdown ( id );
    int mid = (id->l+id->r)/2;
    if (id ->l == l &&id -> r == r ) {
        if ( id -> l == id -> r ) {
            if ( x > id -> mn ) changepoint ( id , x );
            return ;
        }
        if ( x <= id ->mn ) return ;
        if ( id ->mn <= x && x <= id ->mn2 ) {
            id -> lazy = x;
            if ( id -> cnt % 2 == 1 ) {
                id -> xr ^= id ->mn ^x;
            }
            int bt;
            if (id ->mn != 0 ) {
                bt = maxbit (id -> mn);
                for (int i = bt ; i >= 0 ; i-- ) {
                    if ( id ->mn & (1<<i) )
                        id -> num[i] -= id ->cnt;
                }
            }
            bt = maxbit (x);
            for (int i = bt ; i >= 0 ; i-- ) {
                if ( x & (1<<i) )
                    id -> num[i] += id ->cnt;
            }
            id -> mn = x;
        }
        else {
            change ( id ->ll , l , mid , x );
            change (id -> rr , mid +1 ,r , x);
            update ( id );
        }
        return ;
    }
    if (r <= mid ) change ( id ->ll , l , r , x );
    else {
        if (l >mid ) change (id ->rr , l , r , x );
        else {
            change ( id ->ll , l , mid , x );
            change ( id -> rr , mid +1 , r , x );
        }
    }
    update (id );
}
int queryxor ( node *id , int l , int r ) {
    if (id -> l == l && id -> r == r ) return id ->xr;
    pushdown (id );
    int mid = (id->l+id->r)/2;
    if ( r <= mid ) return queryxor (id -> ll,l,r);
    else {
        if (l >mid ) return queryxor (id->rr,l,r);
        else return queryxor(id->ll,l,mid)^queryxor(id->rr,mid+1,r);
    }
}
int querynum (node *id, int l , int r , int x) {
    if ( id ->l == l && id ->r == r ) return id ->num[x];
    pushdown (id);
    int mid = (id->l+id->r)/2;
    if (r <= mid ) return querynum(id->ll,l,r,x);
    else {
        if ( l >mid ) return querynum (id ->rr , l , r , x);
        else {
            return querynum(id->ll,l,mid,x) +querynum(id->rr,mid+1,r,x);
        }
    }
}
void work () {
    int i , op , l , r , x , tmp;
    scanf ( "%d%d" , &n , &q );
    for ( i = 1 ; i <= n ; i++ ) {
        scanf ( "%d" ,&a[i] );
    }
    t = &pool[++top];
    buildtree ( t , 1 , n );
    for ( i = 1 ; i <= q ; i++ ) {
        scanf ( "%d%d%d%d" , &op , &l , &r , &x );
        if ( op == 1 ) {
            change ( t , l , r , x );
        }
        else {
            tmp = x ^ queryxor(t,l,r);
            if ( tmp == 0 ) {
                printf ( "0\n" );
            }
            else {
                int del = 0;
                if ( x > (tmp ^ x) ) del = 1;
                else del = 0;
                //printf ("%d %d %d\n" , del , x , tmp );
                printf ( "%d\n" , querynum ( t , l , r , maxbit ( tmp ) ) + del );
            }
        }
    }
}
int main () {
    work ();
    return 0;
}
