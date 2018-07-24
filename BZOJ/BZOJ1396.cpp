#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=200010;
char s[N];
int n,cnt,last,maxlen[N],Right[N],endpos[N],fa[N],a[N][26],P[N],Q[N],Min[N*2][2];
void extend(int c,int pos)
{
	int p=last,np;last=np=++cnt;
	maxlen[np]=maxlen[p]+1;
	Right[np]=1;
	endpos[np]=pos;
	while (!a[p][c]&&p) a[p][c]=np,p=fa[p];
	if (!p) fa[np]=1;
	else
	{
		int q=a[p][c];
		if (maxlen[q]==maxlen[p]+1) fa[np]=q;
		else
		{
			int nq=++cnt;
			Right[nq]=0;
			endpos[nq]=endpos[q];
			maxlen[nq]=maxlen[p]+1;
			memcpy(a[nq],a[q],sizeof(a[q]));
			fa[nq]=fa[q];
			fa[q]=fa[np]=nq;
			while (a[p][c]==q) a[p][c]=nq,p=fa[p];
		}
	}
}
void Sort()
{
	for (int i=1;i<=cnt;i++) P[maxlen[i]]++;
	for (int i=1;i<=cnt;i++) P[i]+=P[i-1];
	for (int i=cnt;i>=1;i--) Q[P[maxlen[i]]--]=i;
}
void change(int l,int r,int id,int op,int x,int y,int d)
{
	if (l>y||r<x) return;
	if (x<=l&&r<=y) { Min[id][op]=min(Min[id][op],d);return;}
	int mid=(l+r)>>1;
	change(l,mid,id<<1,op,x,y,d);
	change(mid+1,r,id<<1|1,op,x,y,d);
}
int query(int l,int r,int id,int x)
{
	if (l==r) return min(Min[id][0],Min[id][1]-x+1);
	int mid=(l+r)>>1,ans=min(Min[id][0],Min[id][1]-x+1);
	if (x<=mid) return min(ans,query(l,mid,id<<1,x));
		else return min(ans,query(mid+1,r,id<<1|1,x));
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	last=cnt=1;
	for (int i=1;i<=n;i++) extend(s[i]-'a',i);
	Sort();
	for (int i=cnt;i>=1;i--) Right[fa[Q[i]]]+=Right[Q[i]];
	memset(Min,0x3f,sizeof(Min));
	for (int i=1;i<=cnt;i++)
	if (Right[i]==1)
	{
		change(1,n,1,0,endpos[i]-maxlen[fa[i]]+1,endpos[i],maxlen[fa[i]]+1);	
		change(1,n,1,1,endpos[i]-maxlen[i]+1,endpos[i]-maxlen[fa[i]],endpos[i]);
	}
	for (int i=1;i<=n;i++) printf("%d\n",query(1,n,1,i));
	return 0;
}
