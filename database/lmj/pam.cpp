/**
 * title: pam
 * category: 字符串
 * description: /dev/null
 */

#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int NN = 310000;
struct node {
    int len , cnt,ch[30] , fail;
} p[NN];
int top,n,last;
char z[NN];
long long ans;
void work () {
    int i , tmp;
    scanf ( "%s" , z + 1 );
    n = strlen ( z + 1 );
    top = 2;
    p[1].fail = 2; p[2].fail = 1;
    p[1].len = 0; p[2].len = -1;
    z[0] = '$';
    last = 1;
    for ( i = 1 ; i <= n ; i++ ) {
        while ( z[i] != z[i-p[last].len-1] ) last = p[last].fail;
        if ( !p[last].ch[z[i]-'a'+1] ) {
            p[last].ch[z[i]-'a'+1] = ++top;
            p[top].len = p[last].len + 2;
            tmp = p[last].fail;
            while ( z[i] != z[i-p[tmp].len-1] ) tmp = p[tmp].fail;
            if ( p[top].len > 1 && p[tmp].ch[z[i]-'a'+1] ) p[top].fail = p[tmp].ch[z[i]-'a'+1];
            else p[top].fail = 1;
        }
        last = p[last].ch[z[i]-'a'+1];
        p[last].cnt++;
    }
    for ( i = top ; i >= 1 ; i-- ) p[p[i].fail].cnt += p[i].cnt;
    for ( i = 1 ; i <= top ; i++ ) {
        //printf ( "%d %d\n" , p[i].len , p[i].cnt );
        ans = max ( ans , (long long)p[i].len * p[i].cnt );
    }
    printf ( "%lld\n" , ans );
}
int main () {
    work ();
    return 0;
}
