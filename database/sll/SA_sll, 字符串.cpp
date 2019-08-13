#include<bits/stdc++.h>
#define N 200020
int wa[N],wb[N],ws[N],wv[N],sa[N],rank[N];
void cal_sa(int *r,int n,int m)
{
	int *x=wa,*y=wb,*t;
	for(int i=0;i<m;i++)ws[i]=0;
	for(int i=0;i<n;i++)ws[x[i]=r[i]]++;
	for(int i=1;i<m;i++)ws[i]+=ws[i-1];
	for(int i=n-1;i>=0;i--)sa[--ws[x[i]]]=i;
	for(int j=1,p=1;p<n;j<<=1,m=p)
	{
		p=0;
		for(int i=n-j;i<n;i++)y[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(int i=0;i<n;i++)wv[i]=x[y[i]];
		for(int i=0;i<m;i++)ws[i]=0;
		for(int i=0;i<n;i++)ws[wv[i]]++;
		for(int i=1;i<m;i++)ws[i]+=ws[i-1];
		for(int i=n-1;i>=0;i--)sa[--ws[wv[i]]]=y[i];
		t=x,x=y,y=t,p=1;x[sa[0]]=0;
		for(int i=1;i<n;i++)
			x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j])?p-1:p++;
	}
}
int height[N];
void cal_h(int *r,int *sa,int n)
{
	int k=0;
	for(int i=1;i<=n;i++)rank[sa[i]]=i;
	for(int i=0;i<n;i++)
	{
		int j=sa[rank[i]-1];if(k)k--;
		while(r[j+k]==r[i+k])k++;
		height[rank[i]]=k;
	}
}
char ch[N];
int r[N];
int main()
{
	std::cin>>ch;
	int n=strlen(ch);
	for(int i=0;i<n;i++)r[i]=ch[i];r[n]=0;
	cal_sa(r,n+1,128);
	cal_h(r,sa,n);
	for(int i=1;i<=n;i++)printf("%d ",sa[i]+1);puts("");
	for(int i=2;i<=n;i++)printf("%d ",height[i]);
}
