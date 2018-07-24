#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
int k,n;
struct node{int val,id;}Max[3000100],Min[3000100];
int Abs(int x,int y) { return (x>y)?x-y:y-x;}
int main()
{
	scanf("%d%d",&k,&n);
	int now=1,ans=0,l_min=1,l_max=1,r_min=0,r_max=0;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		while (l_max<=r_max&&Max[r_max].val<x) r_max--;
		Max[++r_max]=(node){x,i};
		while (l_min<=r_min&&Min[r_min].val>x) r_min--;
		Min[++r_min]=(node){x,i};
		while (Max[l_max].val-Min[l_min].val>k)
		{
			if (Max[l_max].id<Min[l_min].id) 
				now=Max[l_max++].id+1;else now=Min[l_min++].id+1;
		}
		ans=std::max(ans,i-now+1);
	}
	printf("%d\n",ans);
	return 0;
}

