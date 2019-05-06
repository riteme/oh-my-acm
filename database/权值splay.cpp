/**
 * title: 权值splay 
 * category: 数据结构 
 * description: /dev/null
 */
#include<bits/stdc++.h> 
#define N 2000020
#define inf 1LL<<50
#define mod 1000000
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll n,kind,rt,sz,fa[N],num[N];
ll tr[N][2],size[N],v[N],ans;
void pushup(ll k){size[k]=size[tr[k][0]]+size[tr[k][1]]+num[k];}
void rotate(ll x,ll &k)
{
	ll y=fa[x],z=fa[y],l,r;
	l=tr[y][1]==x;r=l^1;
	if(y==k)k=x;
	else tr[z][tr[z][1]==y]=x;
	fa[x]=z,fa[tr[x][r]]=y,fa[y]=x;
	tr[y][l]=tr[x][r],tr[x][r]=y;
	pushup(y);pushup(x);
}
void splay(ll x,ll &k)
{
	while(x!=k)
	{
		ll y=fa[x],z=fa[y];
		if(y!=k)
		{
			if(tr[y][0]==x^tr[z][0]==y)
				rotate(x,k);
			else rotate(y,k);
		}rotate(x,k);
	}
}
void insert(ll &k,ll x,ll last)
{
	if(!k){k=++sz;v[k]=x;size[k]=num[k]=1;fa[k]=last;splay(k,rt);return ;}
	if(x==v[k])num[k]++;
    else if(x>v[k])insert(tr[k][1],x,k);
	else insert(tr[k][0],x,k);
}
ll t1,t2;
ll find(ll x,ll k)
{
	if(!k)return 0;
	if(x==v[k])return k;
	else if(x>v[k])return find(x,tr[k][1]);
	else return find(x,tr[k][0]);
}
void ask_before(ll x,ll k)
{
	if(!k)return ;
	if(v[k]<x){t1=k;ask_before(x,tr[k][1]);}
	else ask_before(x,tr[k][0]);
}
void ask_after(ll x,ll k)
{
	if(!k)return ;
	if(v[k]>x){t2=k;ask_after(x,tr[k][0]);}
//	else if(v[k]==x)return ;
	else ask_after(x,tr[k][1]);
}
void del(ll x,ll k)
{
	if(num[k]>1)
	{
		num[k]--,size[k]--;
		splay(k,rt);return;
	}
	t1=t2=-1;
	ask_before(x,rt);
	ask_after(x,rt);
	if(t1==-1&&t2==-1)
	{
		if(num[rt]==1)rt=0;
		else size[rt]--,num[rt]--;
	}
	else if(t1==-1)
	{
		splay(t2,rt);
		tr[rt][0]=0;
		pushup(rt);	
	}
	else if(t2==-1)
	{
		splay(t1,rt);
		tr[rt][1]=0;
		pushup(rt);
	}
	else
	{
		splay(t1,rt);
		splay(t2,tr[t1][1]);
		tr[t2][0]=0;
		pushup(t2);pushup(t1);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("my.txt","w",stdout);
	n=read();kind=-1;
	for(ll i=1;i<=n;i++)
	{
		ll f=read(),x=read();
		if(kind==-1)insert(rt,x,0),kind=f;
		else
		{
			if(kind==f)insert(rt,x,0);
			else
			{
				t1=t2=-1;
				ask_before(x,rt);
				ask_after(x,rt);
				if(t1==-1&&t2==-1)
				{
					insert(rt,x,0);
					kind=f;continue;
				}
				ll a=(t1==-1)?inf:abs(v[t1]-x);
				ll b=(t2==-1)?inf:abs(v[t2]-x);
				ans=(ans+min(a,b))%mod;
				ans%=mod;
				if(a>b)swap(t1,t2);
				del(v[t1],t1);
			}
		}
	}printf("%lld\n",ans);
}

