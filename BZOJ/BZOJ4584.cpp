#include<cstdio>
#include<algorithm>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=505;
int n,a[N],b[N],A[N<<1],inv[N],f[N],C[N];
inline void Add(int &a,int b) { a+=b;if (a>=mo) a-=mo;}
int main()
{
	scanf("%d",&n);
	int cnt=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		A[++cnt]=a[i];
		A[++cnt]=b[i]+1;
	}
	sort(A+1,A+cnt+1);
	cnt=unique(A+1,A+cnt+1)-A-1;
	for (int i=1;i<=n;i++)
	{
		a[i]=lower_bound(A+1,A+cnt+1,a[i])-A;
		b[i]=lower_bound(A+1,A+cnt+1,b[i]+1)-A;
	}
	inv[0]=inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
	f[0]=1;
	for (int j=1;j<cnt;j++)
	{
		C[0]=1;
		for (int i=1;i<=n;i++) C[i]=(ll)C[i-1]*(A[j+1]-A[j]+i-1)%mo*inv[i]%mo;
		for (int i=n;i>=1;i--)
		{
			if (a[i]<=j&&j<b[i])
			{
				int num=0;
				for (int k=1;k<=i;k++)
				{
					if (a[i-k+1]<=j&&j<b[i-k+1]) num++;
					Add(f[i],(ll)C[num]*f[i-k]%mo);
				}
			}	
		}
	}
	int ans=0;
	for (int i=1;i<=n;i++) Add(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
