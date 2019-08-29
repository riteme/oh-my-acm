/**
 * title: 序列splay
 * category: 数据结构
 * description: /dev/null
 */
#include<bits/stdc++.h>
#define inf 1<<29
#define N 500020
using namespace std;
inline int read() {
  int x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return x*f;
}
#define ACM_BEGIN
int n,m,sz,rt;
char ch[10];
int tr[N][2],fa[N],v[N],sum[N];
int mx[N],lx[N],rx[N];
int st[N],size[N],top,tag[N];
bool rev[N];
void pushup(int u) {
  size[u]=1,sum[u]=v[u];int l=tr[u][0],r=tr[u][1];
  if(l)size[u]+=size[l],sum[u]+=sum[l];
  if(r)size[u]+=size[r],sum[u]+=sum[r];
  mx[u]=v[u];if(l)mx[u]=max(mx[u],mx[l]);if(r)mx[u]=max(mx[u],mx[r]);
  if(l&&r)mx[u]=max(mx[u],rx[l]+v[u]+lx[r]);
  else if(l)mx[u]=max(mx[u],rx[l]+v[u]);
  else if(r)mx[u]=max(mx[u],v[u]+lx[r]);
  lx[u]=0;if(l)lx[u]=lx[l];rx[u]=0;if(r)rx[u]=rx[r];
  if(!l)lx[u]=max(lx[u],v[u]);if(!r)rx[u]=max(rx[u],v[u]);
  if(!l&&r)lx[u]=max(lx[u],v[u]+lx[r]);if(!r&&l)rx[u]=max(rx[u],v[u]+rx[l]);
  if(l)lx[u]=max(lx[u],sum[l]+v[u]);if(r)rx[u]=max(rx[u],sum[r]+v[u]);
  if(l&&r)lx[u]=max(lx[u],sum[l]+v[u]+lx[r]),rx[u]=max(rx[u],sum[r]+v[u]+rx[l]);
}
void work(int k,int c) {
  tag[k]=c,v[k]=c,sum[k]=size[k]*c;
  mx[k]=(c>0?c*size[k]:c),lx[k]=rx[k]=(c>0?c*size[k]:0);
}
void rve(int k) {
  rev[k]^=1;
  swap(lx[k],rx[k]);
  swap(tr[k][0],tr[k][1]);
}
void pushdown(int u) {
  int l=tr[u][0],r=tr[u][1];
  if(tag[u]!=12345) {
    if(l)work(l,tag[u]);if(r)work(r,tag[u]);
    tag[u]=12345;
  }
  if(rev[u]) {
    if(l)rve(l);if(r)rve(r);
    rev[u]^=1;
}}
void rotate(int x,int &k) {
  int y=fa[x],z=fa[y];
  int l=(tr[y][1]==x),r=l^1;
  if(y==k)k=x;
  else tr[z][tr[z][1]==y]=x;
  fa[x]=z,fa[y]=x,fa[tr[x][r]]=y;
  tr[y][l]=tr[x][r],tr[x][r]=y;
  pushup(y);pushup(x);
}
void splay(int x,int &k) {
  while(x!=k) {
    int y=fa[x],z=fa[y];
    if(y!=k) {
      if(tr[y][0]==x^tr[z][0]==y)
        rotate(x,k);
      else rotate(y,k);
    }
    rotate(x,k);
}}
int find(int k,int rk) {
  pushdown(k);
  int l=tr[k][0],r=tr[k][1];
  if(size[l]>=rk)return find(l,rk);
  else if(size[l]+1==rk)return k;
  else return find(r,rk-size[l]-1);
}
int split(int l,int r) {
  int x=find(rt,l),y=find(rt,r+2);
  splay(x,rt),splay(y,tr[x][1]);
  return tr[y][0];
}
int a[N];
void newnode(int k,int c)
{v[k]=sum[k]=c,mx[k]=c,tag[k]=12345,lx[k]=rx[k]=(c>0?c:0),size[k]=1,rev[k]=0;}
int build(int l,int r) {
  if(l>r)return 0;int mid=(l+r)>>1,now;
  now=++sz;newnode(now,a[mid-1]);
  tr[now][0]=build(l,mid-1);if(tr[now][0])fa[tr[now][0]]=now;
  tr[now][1]=build(mid+1,r);if(tr[now][1])fa[tr[now][1]]=now;
  pushup(now);return now;
}
int Build(int l,int r) {
  if(l>r)return 0;int mid=(l+r)>>1,now;
  if(top)now=st[top--];else now=++sz;newnode(now,a[mid]);
  tr[now][0]=Build(l,mid-1);if(tr[now][0])fa[tr[now][0]]=now;
  tr[now][1]=Build(mid+1,r);if(tr[now][1])fa[tr[now][1]]=now;
  pushup(now);return now;
}
void insert(int x,int tot) {
  for(int i=0;i<=tot+2;i++)a[i]=0;
  for(int i=1;i<=tot;i++)a[i]=read();
  int l=find(rt,x+1),r=find(rt,x+2);
  splay(l,rt),splay(r,tr[l][1]);
  tr[r][0]=Build(1,tot),fa[tr[r][0]]=r;
  pushup(r),splay(r,rt);
}
void clr(int k){tag[k]=12345,tr[k][0]=tr[k][1]=fa[k]=rev[k]=v[k]=sum[k]=mx[k]=lx[k]=rx[k]=size[k]=0;}
void rec(int k) {
  if(!k)return;
  rec(tr[k][0]);rec(tr[k][1]);
  st[++top]=k,clr(k);
}
void del(int x,int tot) {
  int l=x,r=x+tot-1,k=split(l,r);
  int fk=fa[k];tr[fk][0]=fa[k]=0;rec(k);
  splay(fk,rt);
}
void make_same(int x,int tot,int c)
{int l=x,r=x+tot-1,k=split(l,r);work(k,c);if(fa[k])splay(fa[k],rt);}
void rever(int x,int tot)
{int l=x,r=x+tot-1,k=split(l,r);rve(k);if(fa[k])splay(fa[k],rt);}
int get_sum(int x,int tot) {
  int l=x,r=x+tot-1,k=split(l,r);
  return sum[k];
}
#define ACM_END
int main() {
  n=read(),m=read();a[0]=a[n+1]=(-1<<29);
  for(int i=1;i<=n;i++)a[i]=read();
  rt=build(1,n+2);
  int now=0;
  for(int i=1;i<=m;i++) {
    scanf("%s",ch);
    if(ch[0]=='I'){int x=read(),tot=read();insert(x,tot);}
    else if(ch[0]=='D'){int x=read(),tot=read();del(x,tot);}
    else if(ch[0]=='M'&&ch[2]=='K'){int x=read(),tot=read(),c=read();make_same(x,tot,c);}
    else if(ch[0]=='R'){int x=read(),tot=read();rever(x,tot);}
    else if(ch[0]=='G'){int x=read(),tot=read();now++;printf("%d\n",get_sum(x,tot));}
    else now++,printf("%d\n",mx[rt]);
}}
