#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	int x,sum=0,Sum=0;
	for (int i=1;i<=n;i++) { scanf("%d",&x);sum+=x;}
	for (int i=1;i<=n;i++) { scanf("%d",&x);Sum+=x;}
	if (Sum>sum) puts("No");else puts("Yes");
	return 0;
}
