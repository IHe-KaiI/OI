#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
char s[100010],S[200010];
int n,RL[200010],L[200010],R[200010];
void manacher()
{
	int maxright=0,pos;
	for (int i=1;i<=n;i++)
	{
		if (i<=maxright) RL[i]=min(RL[pos+pos-i],maxright-i);
		while (S[i-RL[i]-1]==S[i+RL[i]+1]) RL[i]++;
		L[i+RL[i]]=max(L[i+RL[i]],RL[i]);
		R[i-RL[i]]=max(R[i-RL[i]],RL[i]);
		if (i+RL[i]>=maxright) maxright=i+RL[i],pos=i;
	}
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for (int i=1;i<=n;i++) S[i<<1]=s[i],S[i<<1|1]='!';
	S[1]='!';S[0]='#';S[n+n+2]='$';
	n=n+n+2;
	manacher();
	for (int i=3;i<=n;i+=2) R[i]=max(R[i],R[i-2]-2);
	for (int i=n;i>=1;i-=2) L[i]=max(L[i],L[i+2]-2);
	int ans=0;
	for (int i=1;i<=n;i+=2)
		if (R[i]&&L[i]) ans=max(ans,R[i]+L[i]);
	printf("%d\n",ans);
	return 0;
}
