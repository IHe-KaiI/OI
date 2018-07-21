#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int T;
ll A1,B1,C1,D1;
__int128 A,B,C,D;
ll gcd(ll x,ll y) { return (!y)?x:gcd(y,x%y);}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%lld%lld%lld%lld",&A1,&B1,&C1,&D1);
		A=A1;B=B1;C=C1;D=D1;
		bool flag=1;
		if (B>D) { puts("No");continue;}
		for (int i=1;i<=15;i++)
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
		if (flag)
		{
			for (int i=1;i<=min((ll)1e6,B1+gcd(D1-B1,B1));i++)
			{
				A1=(A1+D1-B1)%B1;
				if (A1>C1) { flag=0;break;}
			}
		}
		if (flag) puts("Yes");else puts("No");
	}
	return 0;
}
