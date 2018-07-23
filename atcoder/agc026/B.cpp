#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T;
ll A,B,C,D;
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
		bool flag=1;
		if (B>D) { puts("No");continue;}
		for (int i=1;i<=30000;i++)
		{
			if (A<B) { flag=0;break;}
			if (A>=B)
			{
				ll K;
				if (A>C)
				{
					if ((A-C)%B==0) K=(A-C)/B;
						else K=(A-C)/B+1;
					A-=K*B;
					if (A<0) { flag=0;break;}
				}else A-=B;
			}
			if (A<=C) A+=D;
		}
		if (flag) puts("Yes");else puts("No");
	}
	return 0;
}
