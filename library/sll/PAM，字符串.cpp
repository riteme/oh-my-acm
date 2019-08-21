#include<bits/stdc++.h>
using namespace std;

#define ACM_BEGIN
#define N 500020
int val[N], head[N], pos;
struct edge{int to,next;}e[N<<1];
void add(int a,int b) {pos++;e[pos].to=b,e[pos].next=head[a],head[a]=pos;}
struct Tree {
  char ch[N];
  int now,cnt,odd,even;
  int fail[N],len[N],go[N][26];
  void init() {
    now=cnt=0;
    odd=++cnt,even=++cnt;
    len[odd]=-1,len[even]=0;
    fail[odd]=fail[even]=odd;
    now=even;add(odd,even);
  }
  void insert(int pos,char c) {
    while(ch[pos-1-len[now]]!=c)now=fail[now];
    if(!go[now][c-'a']){
      go[now][c-'a']=++cnt;
      len[cnt]=len[now]+2;
      if(now==odd)fail[cnt]=even;
      else {
        int t=fail[now];
        while(ch[pos-1-len[t]]!=c)t=fail[t];
        fail[cnt]=go[t][c-'a'];
      }
      add(fail[cnt],cnt);
    }
    now=go[now][c-'a'];
    val[now]++;
  }
  void dfs(int u) {
    for(int i=head[u];i;i=e[i].next) {
      int v=e[i].to;
      dfs(v);
      val[u]+=val[v];
  }}
  long long cal() {
    long long ret=0;
    for(int i=3;i<=cnt;i++)
      ret=max(ret,1ll*len[i]*val[i]);
    return ret;
}} tree;
int main() {
  tree.init();
  scanf("%s",tree.ch+1);
  int len=strlen(tree.ch+1);
  for(int i=1;i<=len;i++)
    tree.insert(i,tree.ch[i]);
  tree.dfs(1);
  printf("%lld\n",tree.cal());
}
#define ACM_END