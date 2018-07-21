#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,num,Tree[400100];
double X[100100],Y[100100];
bool check(int i,int j,int x)
{
	return X[i]+(x-1)*Y[i]>X[j]+(x-1)*Y[j];
}
void change(int l,int r,int id,int x)
{
	if (l==r)
	{
		if (check(x,Tree[id],l)) Tree[id]=x;
		return;
	}
	int mid=(l+r)>>1;
	if (Y[x]>Y[Tree[id]])
	{
		if (check(x,Tree[id],mid)) change(l,mid,id<<1,Tree[id]),Tree[id]=x;
			else change(mid+1,r,id<<1|1,x);
	}else
	{
		if (check(x,Tree[id],mid)) change(mid+1,r,id<<1|1,Tree[id]),Tree[id]=x;
			else change(l,mid,id<<1,x);
	}
}
double query(int l,int r,int id,int x)
{
	if (l>x||r<x) return 0;
	if (l==r&&l==x) return X[Tree[id]]+(l-1)*Y[Tree[id]];
	int mid=(l+r)>>1;
	double ans=X[Tree[id]]+(x-1)*Y[Tree[id]];
	return max(ans,max(query(l,mid,id<<1,x),query(mid+1,r,id<<1|1,x)));
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char s[20];
		scanf("%s",s);
		if (s[0]=='Q')
		{
			int x;
			scanf("%d",&x);
			printf("%d\n",(int)query(1,50000,1,x)/100);
		}else
		{
			num++;
			scanf("%lf%lf",&X[num],&Y[num]);
			change(1,50000,1,num);
		}
	}
	return 0;
}
