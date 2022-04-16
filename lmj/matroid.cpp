/**
 * title: matroid
 * category: 常识 
 * description: matroid.md
 */
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	long long v;
	node *next;
} pool[1200000] , *g[12000];
struct basis {
	long long a[66] , b[66] , id[66];
	
	basis () {
		long long i;
		for ( i = 0 ; i < 60 ; i++ )
			a[i] = b[i] = id[i] = 0;
	}
	bool add ( long long x , long long idd ) {
		long long i , frm = 0;
		for ( i = 59 ; i >= 0 ; i-- ) {
			if ( x & (1ll<<i) ) {
				if ( !a[i] ) {
					a[i] = x;
					b[i] = frm | (1ll<<i);
					id[i] = idd;
					return 1;
				}
				x ^= a[i];
				frm ^= b[i];
			}
		}
		return 0;
	}
	long long exp ( long long x ) {
		long long i , rep = 0;
		for ( i = 59 ; i >= 0 ; i-- ) {
			if ( x & (1ll<<i) ) {
				if ( !a[i] ) {
					return 0;
				}
				x ^= a[i];
				rep ^= b[i];
			}
		}
		return rep;
	}
} emp , now;
long long top;
long long n , m , tot;
long long a[6100] , hpnum[6100];
long long s , t;
long long dis[6100] , from[6100];
long long ans[120];
long long isans[6100] , cnt[6100] , num;
void clear () {
	long long i;
	for ( i = 1 ; i <= top ; i++ ) {
		pool[i] = pool[0];
	}
	for ( i = 1 ; i <= tot + 2 ; i++ ) {
		g[i] = NULL;
		dis[i] = -1;
		from[i] = 0;
	}
	top = 0;
}
void add ( long long u , long long v ) {
	node *tmp = &pool[++top];
	//printf ( "%lld %lld\n" , u , v );
	tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;
}
void bfs () {
	long long i , k;
	queue < long long > q;
	q.push ( s ); dis[s] = 0;
	while ( q.size () ) {
		k = q.front (); q.pop();
		//printf ( "%lld\n" , k );
		for ( node *j = g[k] ; j ; j = j -> next ) {
			if ( dis[j->v] == -1 ) {
				dis[j->v] = dis[k] + 1;
				from[j->v] = k;
				q.push ( j -> v );
				if ( j -> v == t ) return ;
			}
		}
	} 
}
bool augment () {
	long long i , j , del , express;
	now = emp;
	s = tot + 1; t = tot + 2;
	for ( i = 1 ; i <= num ; i++ ) {
		now.add ( a[ans[i]] , ans[i] );
	}
	clear ();
	for ( i = 1 ; i <= tot ; i++ ) {
		if ( now.exp ( a[i] ) == 0 ) {
			add ( s , i );
		}
		if ( cnt[hpnum[i]] == 0 ) {
			add ( i , t );
		}
	}
	for ( i = 1 ; i <= tot ; i++ ) {
		if ( isans[i] == 0 ) {
			express = now.exp ( a[i] );
			if ( express == 0 ) {
				for ( j = 1 ; j <= num ; j++ ) {
					add ( ans[j] , i );
				}
			}
			else {
				for ( j = 0 ; j <= 59 ; j++ ) {
					if ( express & (1ll<<j) ) {
						add ( now.id[j] , i );
					}
				}
			}
		}
	}
	for ( i = 1 ; i <= tot ; i++ ) {
		for ( j = 1 ; j <= num ; j++ ) {
			if ( isans[i] == 0 ) {
				if ( cnt[hpnum[i]] - (hpnum[ans[j]]==hpnum[i]) == 0 ) {
					add ( i , ans[j] );
				}
			}
		}
	}
	//printf ( "%lld\n" , num );
	bfs ();
	if ( dis[t] == -1 ) return false;
	del = 1;
	for ( i = from[t] ; i != s ; i = from[i] ) {
		if ( del == 1 ) {
			isans[i] = 1;
			cnt[hpnum[i]]++;
		}
		else {
			isans[i] = 0;
			cnt[hpnum[i]]--;
		}
		del = -del;
	}
	num = 0;
	for ( i = 1 ; i <= tot ; i++ ) {
		if ( isans[i] ) ans[++num] = i;
	}
	return true;
}
void work () {
	int i , j , k;
	scanf ( "%lld" , &n );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%lld" , &a[i] );
		hpnum[i] = i;
	}
	scanf ( "%lld" , &m );
	tot = n;
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%lld" , &k );
		for ( j = 1 ; j <= k ; j++ ) {
			scanf ( "%lld" , &a[++tot] );
			hpnum[tot] = n + i;
		}
	}
	while ( augment () == 1 ) ;
	if ( num == n + m ) {
		for ( i = n + 1 ; i <= tot ; i++ ) {
			if ( isans[i] ) printf ( "%lld\n" , a[i] );
		}
	}
	else printf ( "-1\n" );
}
int main () {
	work ();
	return 0;
}

