#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<set>
using namespace std;
int n,D,A[200100],B[200100],Q[200100],dis[200100];
struct cmp1
{
	bool operator () (int x,int y) { return B[x]<B[y];}
};
struct cmp2
{
	bool operator () (int x,int y) { return A[x]<A[y];}
};
multiset<int,cmp1>Sa;
multiset<int,cmp2>Sb;
int main()
{
	scanf("%d%d",&n,&D);
	for (int i=1;i<=n*2;i++)
	{
		scanf("%d%d",&A[i],&B[i]);
		A[i]=-A[i];B[i]=-B[i];
	}
	int t=0,w=1;
	memset(dis,-1,sizeof(dis));
	for (int i=1;i<=n;i++)
	{
		if (B[i]==0) { Q[++w]=i;dis[i]=1;}
			else Sa.insert(i);
		if (A[n+i]==0) { Q[++w]=n+i;dis[n+i]=1;}
			else Sb.insert(n+i);
	}
	while (t<w)
	{
		int u=Q[++t];
		if (u<=n)
		{
			while (1)
			{
				multiset<int,cmp1>::iterator it=Sb.lower_bound(u);
				if (it==Sb.end()||A[*it]>A[u]+D) break;
				Q[++w]=*it;
				dis[*it]=dis[u]+1;
				Sb.erase(it);
			}
		}else
		{		
			while (1)
			{
				multiset<int,cmp2>::iterator it=Sa.lower_bound(u);
				if (it==Sa.end()||B[*it]>B[u]+D) break;
				Q[++w]=*it;
				dis[*it]=dis[u]+1;
				Sa.erase(it);
			}
		}
	}
	for (int i=1;i<=n;i++) printf("%d\n",dis[i]);
	return 0;
}
