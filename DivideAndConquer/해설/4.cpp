#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

ll mod;

ll power(ll p,ll exp)
{
	ll ret(1);
	while(exp)
	{
		if(exp%2)ret=ret*p%mod;
		p=p*p%mod;
		exp>>=1;
	}
	return ret;
}

ll solve(ll r,ll n)
{
	if(n==0LL)return 1;
	if(n==1LL)return (r+1)%mod;
	if(n&1LL)return solve(r,n>>1)*(1+power(r,(n>>1)+1LL))%mod;
	else return (solve(r,(n>>1)-1LL)*(1+power(r,n>>1))%mod+(power(r,n)%mod))%mod;
}
int main()
{
	ll a,r,n;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>r>>n>>mod;
	if(mod==0LL)
	{
		cout<<0;
	}
	else
	{
		cout<<a*solve(r,n-1LL)%mod;
	}
	return 0;
}