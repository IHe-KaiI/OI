#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=70010,M=2200;
int n,m,a[N],b[N];
struct BitSet
{
	unsigned int a[M];
}Ans,X,Y,A[N];
BitSet operator & (BitSet a,BitSet b) { for (int i=0;i<M;i++) a.a[i]&=b.a[i];return a;}
BitSet operator ^ (BitSet a,BitSet b) { for (int i=0;i<M;i++) a.a[i]^=b.a[i];return a;}
BitSet operator | (BitSet a,BitSet b) { for (int i=0;i<M;i++) a.a[i]|=b.a[i];return a;}
void operator -= (BitSet &a,BitSet b)
{
	unsigned int last=0;
	for (int i=0;i<M;i++)
		if (a.a[i]>=b.a[i]+last) a.a[i]-=b.a[i]+last,last=0;
			else a.a[i]-=b.a[i]+last,last=1;
}
void operator <<= (BitSet &a,BitSet b)//a=b*2+1
{
	unsigned int last=1;
	for (int i=0;i<M;i++)
	{
		unsigned int x=b.a[i]>>31;
		a.a[i]=(b.a[i]<<1|last);
		last=x;

	}
}
void Insert(BitSet &A,int x) { A.a[x>>5]|=1u<<(x&31);}
int count(BitSet A)
{
	int ans=0;
	for (int i=0;i<M;i++) ans+=__builtin_popcount(A.a[i]);
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		Insert(A[a[i]],i);
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		Y<<=Ans;
		Ans=Ans|A[b[i]];
		X=Ans;
		X-=Y;
		Ans=Ans&(Ans^X);
	}
	printf("%d\n",count(Ans));
	return 0;
}
