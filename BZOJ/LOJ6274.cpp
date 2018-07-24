#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=65;
ll T,L1,R1,L2,R2,f[N][65540];
int len,Len1L,Len1R,Len2L,Len2R,aL[N],aR[N],bL[N],bR[N],A[N];
int calc(int x,int y,int sta,int L)
{
	int S=0;
	for (int P=0;P<16;P++)
	if (sta&(1<<P))
	{
		int i=P/4,j=P%4,I=0,J=0;
		if (i)
		{
			if (i==1||i==3)
			{
				if (x>aR[L]) continue;
				if (x==aR[L]) I++;
			}
			if (i==2||i==3)
			{
				if (x<aL[L]) continue;
				if (x==aL[L]) I+=2;
			}
		}
		if (j)
		{
			if (j==1||j==3)
			{
				if (y>bR[L]) continue;
				if (y==bR[L]) J++;
			}
			if (j==2||j==3)
			{
				if (y<bL[L]) continue;
				if (y==bL[L]) J+=2;
			}
		}
		S|=1<<(I*4+J);
	}
	return S;
}
ll solve(int Len,int sta)
{
	if (!Len) return 1;
	if (f[Len][sta]!=-1) return f[Len][sta];
	ll ans=0;
	if (!A[Len])
	{
		int S=calc(0,0,sta,Len);
		if (S) ans+=solve(Len-1,S);
	}
	if (A[Len]==1)
	{
		int S=calc(1,1,sta,Len);
		if (S) ans+=solve(Len-1,S);
	}
	if (A[Len]==1)
	{
		int S=calc(1,0,sta,Len)|calc(0,1,sta,Len);
		if (S) ans+=solve(Len-1,S);
	}
	f[Len][sta]=ans;
	return ans;
}
int main()
{
	scanf("%lld%lld%lld%lld%lld",&T,&L1,&R1,&L2,&R2);
	while (T) { A[++len]=T&1;T>>=1;}
	while (L1) { aL[++Len1L]=L1&1;L1>>=1;}
	while (R1) { aR[++Len1R]=R1&1;R1>>=1;}
	while (L2) { bL[++Len2L]=L2&1,L2>>=1;}
	while (R2) { bR[++Len2R]=R2&1;R2>>=1;}
	memset(f,-1,sizeof(f));
	printf("%lld\n",solve(max(len,max(Len1R,Len2R)),1<<15));
	return 0;
}
