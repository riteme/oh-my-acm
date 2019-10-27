/**
 * title: largest_empty_convex
 * category: 计算几何 
 * description: largest_empty_convex.md
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;

int getint()
{
    int i=0,f=1;char c;
    for(c=getchar();(c!='-')&&(c<'0'||c>'9');c=getchar());
    if(c=='-')f=-1,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())i=(i<<3)+(i<<1)+c-'0';
    return i*f;
}

#define ACM_BEGIN
const int N=105;
struct point
{
    double x,y;
    point(){}
    point(double _x,double _y):x(_x),y(_y){}
    inline friend point operator - (const point &a,const point &b)
    {return point(a.x-b.x,a.y-b.y);}
    inline friend double operator * (const point &a,const point &b)
    {return a.x*b.y-a.y*b.x;}
    inline double dis(){return x*x+y*y;}
}a[N],p[N],O;
int T,n,m;
double dp[N][N],ans;

inline bool cmp(const point &a,const point &b)
{
    double res=(a-O)*(b-O);
    if(res)return res>0;
    return (a-O).dis()<(b-O).dis();
}

void solve()
{
    memset(dp,0,sizeof(dp));
    sort(p+1,p+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        int j=i-1;
        while(j&&!((p[i]-O)*(p[j]-O)))j--;
        bool bz=(j==i-1);
        while(j)
        {
            int k=j-1;
            while(k&&(p[i]-p[k])*(p[j]-p[k])>0)k--;
            double area=fabs((p[i]-O)*(p[j]-O))/2;
            if(k)area+=dp[j][k];
            if(bz)dp[i][j]=area;
            ans=max(ans,area),j=k;
        }
        if(bz)for(int j=1;j<i;j++)dp[i][j]=max(dp[i][j],dp[i][j-1]);
    }
}

int main()
{
    //freopen("lx.in","r",stdin);
    T=getint();
    while(T--)
    {
        n=getint();ans=0;
        for(int i=1;i<=n;i++)a[i].x=getint(),a[i].y=getint();
        for(int i=1;i<=n;i++)
        {
            O=a[i],m=0;
            for(int j=1;j<=n;j++)
                if(a[j].y>a[i].y||a[j].y==a[i].y&&a[j].x>a[i].x)p[++m]=a[j];
            solve();
        }
        printf("%0.1lf\n",ans);
    }
    return 0;
}
#define ACM_END
