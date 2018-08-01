#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,K,a[100100],A[100100];
int gcd(int x,int y) { return (!y)?x:gcd(y,x%y);}
int main()
{
	scanf("%d%d",&n,&K);
	int k=K;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) K=gcd(K,a[i]);
	int cnt=0;
	for (int i=0;i<k;i++)
		if (i%K==0) A[++cnt]=i;
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++) printf("%d ",A[i]);
	return 0;
}
