#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 998244353
#define ll long long
using namespace std;
const int N=4010;
int n,K,a[N],h[N],MOD[N],f[N],ans[N],c[N];
inline void Add(int &a,int b) { a+=b;if (a>=mo) a-=mo;}
void mul(int *a,int *b)
{
    for (int i=0;i<K+K-1;i++) c[i]=0;
    for (int i=0;i<K;i++)
        for (int j=0;j<K;j++) Add(c[i+j],(ll)a[i]*b[j]%mo);
    for (int i=K*2-2;i>=K;i--)
    if (c[i])
    {
        for (int j=K-1;j>=0;j--)
        {
            Add(c[i-K+j],-(ll)MOD[j]*c[i]%mo);
            if (c[i-K+j]<0) c[i-K+j]+=mo;
        }
    }
    for (int i=0;i<K;i++) a[i]=c[i];
}
void mi(int y)
{
    while (y)
    {
        if (y&1) mul(ans,f);
        mul(f,f);
        y>>=1;
    }
}
int main()
{
    scanf("%d%d",&n,&K);
    for (int i=1;i<=K;i++) scanf("%d",&a[i]),a[i]=(a[i]%mo+mo)%mo;
    for (int i=0;i<K;i++) scanf("%d",&h[i]),h[i]=(h[i]%mo+mo)%mo;
    if (n<K) { printf("%d\n",h[n]);return 0;}
    for (int i=0;i<K;i++) MOD[i]=(-a[K-i]%mo+mo)%mo;
    f[1]=1;ans[0]=1;
    mi(n);
    int Ans=0;
    for (int i=0;i<K;i++) Add(Ans,(ll)ans[i]*h[i]%mo);
    printf("%d\n",Ans);
    return 0;
}

