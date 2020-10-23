/**
 * title: weighted_blossom_algorithm
 * category: Í¼ÂÛ
 * description: weighted_blossom_algorithm.md
 */
#include <bits/stdc++.h>
#define pb emplace_back
using namespace std;
bool chkmax(int &a,int b){ return a<b?a=b,true:false; }
bool chkmin(int &a,int b){ return b<a?a=b,true:false; }
const int N=605,inf=1<<30,NUL=1,IN=2,OUT=3; // 1.5n,2w
struct solver {
	struct edge_t {
		int u,v,w;
		edge_t(){ u=v=w=0; }
		edge_t(int u,int v,int w):u(u),v(v),w(w){}
	} e[N][N];
	int nc,n,m,h[N],lk[N],fl[N],fc,match[N],in[N],mpos[N],col[N],from[N];
	vector<int> flower[N];
	void init(int n0){
		nc=n0,n=m=n0+(n0&1);
		for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) e[i][j]=edge_t(i,j,0);
	}
	void add(int u,int v,int c){ if(chkmax(e[u][v].w,c)) e[v][u]=e[u][v]; }
	int len(edge_t e){ return h[e.u]+h[e.v]-e.w*2; }
	int other(edge_t e,int x){ return in[e.u]+in[e.v]-x; }
	int slack(int x){ return mpos[x]?len(e[x][in[mpos[x]]])/(1+(col[x]==OUT)):inf; }
	void upd(int v,int u){ if(!mpos[u]||len(e[u][mpos[u]])>len(e[u][v])) mpos[u]=v; }
	void set(int x,int b){ in[x]=b; if(x>n) for(int y:flower[x]) set(y,b); }
	int lca(int u,int v){
		for(u=in[u],v=in[v],++fc;u||v;u=in[from[u]],v=in[from[v]]){
			if(fl[u]==fc) return u; if(u) fl[u]=fc;
			if(fl[v]==fc) return v; if(v) fl[v]=fc;
		}
		return 0;
	}
	void color(int x,int c){
		col[x]=c,mpos[x]=0;
		if(c!=IN){
			for(int y=1;y<=m;++y) if(y!=x&&in[y]==y&&col[y]!=IN){
				if(col[y]==OUT) upd(y,x);
				if(c==OUT) upd(x,y);
			}
		}
	}
	void contract(int u,int v,int p){
		int x=n+1; while(in[x]) ++x; chkmax(m,x);
		match[from[x]=match[x]=match[p]]=in[x]=x;
		vector<int> &c=flower[x];
		for(u=in[u];u!=p;u=in[from[u]]) c.pb(u);
		c.pb(p),reverse(c.begin(),c.end());
		for(v=in[v];v!=p;v=in[from[v]]) c.pb(v);
		for(int y:c) for(int k=1;k<=m;++k) if(!e[x][k].u||len(e[y][k])<len(e[x][k])) e[x][k]=e[k][x]=e[y][k];
		set(x,x); for(int y:c) mpos[y]=from[y]=match[y]=col[y]=0; color(x,OUT);
	}
	void decompose(int b){
		vector<int> &c=flower[b];
		for(int x:c) set(x,x);
		int len=c.size(),p,q; vector<int> cyc(len);
		int fr=other(e[in[from[b]]][b],in[from[b]]),bk=other(e[b][match[b]],match[b]);
		for(p=0;c[p]!=fr;++p); for(q=0;q<len;++q) cyc[q]=c[(p+q)%len]; for(p=0;cyc[p]!=bk;++p);
		if(p&1) reverse(cyc.begin()+1,cyc.end()),p=len-p; from[cyc[0]]=from[b];
		for(q=0;q<p;++q) color(cyc[q],(q&1)?OUT:IN),match[cyc[q]]=cyc[q^1],from[cyc[q+1]]=cyc[q];
		for(q=p+1;q<len;++q) color(cyc[q],NUL),match[cyc[((q-1)^1)+1]]=cyc[q];
		from[match[b]]=match[match[cyc[p]]=match[b]]=cyc[p],color(cyc[p],IN);
		match[b]=in[b]=mpos[b]=from[b]=match[b]=0; c.clear();
		for(int k=1;k<=m;++k) e[b][k]=e[k][b]=edge_t();
	}
	bool detect(int u,int v){
		u=in[u],v=in[v];
		vector<int> path;
		if(col[v]==OUT){
			int p=lca(u,v);
			if(!p){
				while(u) path.pb(u),u=in[from[u]];
				reverse(path.begin(),path.end());
				while(v) path.pb(v),v=in[from[v]];
			}else return contract(u,v,p),false;
		}else if(match[v]){
			return from[v]=u,color(v,IN),from[match[v]]=v,color(match[v],OUT),false;
		}else for(path.pb(v);u;u=in[from[u]]) path.pb(u);
		for(int i=0;i<path.size();++i) match[path[i]]=path[i^1];
		return true;
	}
	bool augment(){
		for(int x=1;x<=m;++x) mpos[x]=from[x]=0,col[x]=in[x]?NUL:0;
		for(int x=1;x<=m;++x) if(in[x]==x) color(x,match[x]?NUL:OUT);
		while(true){
			for(int x=1,c=1;c<=m;x=x%m+1,++c) if(in[x]==x&&col[x]!=IN&&!slack(x)) if(c=detect(mpos[x],x)) return true;
			for(int x=n+1,c=1;c<=m-n;x=(x-n)%(m-n)+n+1,++c) if(in[x]==x&&col[x]==IN&&!h[x]) decompose(x),c=0;
			int d=inf;
			for(int x=1;x<=m;++x) if(in[x]==x) {
				if(col[x]!=IN) chkmin(d,slack(x));
				else if(x>n) chkmin(d,h[x]/2);
			}
			if(d==inf) return false;
			for(int x=1;x<=n;++x){
				if(col[in[x]]==OUT) h[x]-=d;
				if(col[in[x]]==IN) h[x]+=d;
			}
			for(int x=n+1;x<=m;++x) if(in[x]==x) {
				if(col[x]==OUT) h[x]+=d*2;
				if(col[x]==IN) h[x]-=d*2;
			}
		}
		return false;
	}
	void untie(vector<int>&c,int v){
		int p=0,l=c.size();
		for(int x:c) set(x,x);
		while(c[p]!=in[v]) ++p;
		if(in[v]>n) untie(flower[in[v]],v);
		for(int i=1;i<l;i+=2) untie(c[(p+i)%l],c[(p+i+1)%l]);
		c.clear();
	}
	void untie(int x,int y){
		int u=e[x][y].u,v=e[x][y].v;
		if(in[u]!=x) swap(u,v);
		if(e[x][y].w) lk[lk[v]=u]=v;
		if(x>n) untie(flower[x],u);
		if(y>n) untie(flower[y],v);
	}
	void mwpm(){
		for(int u=1;u<=n;++u){
			for(int v=1;v<=n;++v) chkmax(h[u],e[u][v].w);
			h[u]+=h[u]&1,in[u]=u;
		}
		while(augment());
		for(int x=1;x<=m;++x) if(in[x]==x&&match[x]<x) untie(match[x],x);
		long long ret=0;
		for(int x=1;x<=n;++x) if(x<lk[x]) ret+=e[x][lk[x]].w;
		cout<<ret<<'\n';
		for(int x=1;x<=nc;++x) cout<<lk[x]<<" \n"[x==nc];
	}
} ;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	solver a;
	int n, m;
	cin >> n >> m;
	a.init(n);
	for (int i = 1; i <= m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		a.add(u, v, c);
	}
	a.mwpm();
}

