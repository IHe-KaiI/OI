#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mod 140345
typedef long long ll;
ll A,B,C,ans;
int cnt,head[mod+10];
struct node
{
    ll from,to,val;
    int next;
}edge[mod+10];
void init()
{
    memset(head,-1,sizeof(head));
    cnt=1;
}
void edgeadd(ll from,ll to,ll val)
{
    edge[cnt].from=from,edge[cnt].to=to,edge[cnt].val=val;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}
ll quick_my(ll x,ll y)
{
    ll ret=1;
    while(y)
    {
        if(y&1)ret=(ret*x)%C;
        x=(x*x)%C;
        y>>=1;
    }
    return ret;
}
ll gcd(ll a,ll b)
{
    while(b)
    {
        ll t=b;
        b=a%b;
        a=t;
    }
    return a;
}
void exgcd(ll a,ll b,ll &x,ll &y,ll &gcd)
{
    if(!b)
    {
        x=1,y=0,gcd=a;
        return;
    }
    exgcd(b,a%b,y,x,gcd);
    y=y-a/b*x;
}
ll get_inv(ll x,ll MOD)
{
    ll X,Y,GCD;
    exgcd(x,MOD,X,Y,GCD);
    return (X%MOD+MOD)%MOD;
}
void BSGS(ll A,ll B,ll C)
{
    //A^x=B(mod C)
    init();
    ll m=(int)ceil(sqrt(C));
    ll k=1;
    for(int i=0;i<m;i++)
    {
        int flag=0;
        for(int j=head[k%mod];j!=-1;j=edge[j].next)
        {
            if(edge[j].val==k){flag=1;break;}
        }
        if(!flag)edgeadd(k%mod,i,k);
        k=k*A%C;
    }
    ll invk=get_inv(k,C);
    ll invD=1;
    for(int i=0;i<=m;i++)
    {
        ll tmpB=B*invD%C; 
        for(int j=head[tmpB%mod];j!=-1;j=edge[j].next)
        {
            if(edge[j].val==tmpB){ans=edge[j].to+i*m;return;}
        }
        invD=invD*invk%C;
    }
}
int main()
{
    while(~scanf("%lld%lld%lld",&A,&C,&B))
    {
        if(A==0&&B==0&&C==0)break;
        int top=(int)ceil(log2(C));
        int flag=0;
        for(int i=0;i<=top;i++)
        {
            if(quick_my(A,i)==B)
            {
                printf("%d\n",i);
                flag=1;
                break;
            }
        }
        if(flag)continue;
        ll cntk=0;
        ll d=gcd(A,C);
        ll pile=1;
        while(d!=1)
        {
            cntk++;
            if(B%d!=0){puts("No Solution");flag=1;break;}
            pile*=d;
            C/=d,B/=d;
            d=gcd(A,C);
        }
        if(flag)continue;
        ll inv1=get_inv(pile,C);
        ll wait_to_be_inv=quick_my(A,cntk)*inv1%C;
        ll tmp=get_inv(wait_to_be_inv,C);
        B=B*tmp%C;
        ans=-1;
        BSGS(A,B,C);
        if(ans!=-1)printf("%lld\n",ans+cntk);
        else puts("No Solution");
    }
}
