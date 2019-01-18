#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=500010;
int n,a[N],len[N],v[N];
bool check(int x)
{
	int top=1;
	len[1]=a[1];v[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (a[i]>a[i-1])
		{
			len[++top]=a[i];v[top]=1;
		}else
		{
			while (top&&len[top-1]>=a[i]) top--;
			while (top&&v[top]==x) top--;
			if (top==0) return 0;
			int K=min(a[i],len[top]),color=v[top];
			len[top]=K-1;
			if (len[top]==len[top-1]) top--;
			len[++top]=K;
			v[top]=color+1;
			if (len[top]!=a[i])
			{
				len[++top]=a[i];
				v[top]=1;
			}
		}
		while (top>1&&v[top]==v[top-1]) len[top-1]=a[i],top--;
	}
	return 1;
}
int erfen(int l,int r)
{
	while (l<r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) r=mid;
			else l=mid+1;
	}
	return r;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	printf("%d\n",erfen(1,n));
	return 0;
}
