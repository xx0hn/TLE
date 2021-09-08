#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
using ll=long long;

int main()
{
	int n;
	vector<ll> default_level;
	ll k;
	ll start=numeric_limits<ll>::max(), end(0);
	ll ans(0);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	default_level.resize(n);
	for(ll& ele:default_level)
	{
		cin>>ele;
        start=min(start,ele);
	}
	end=start+k;
	while(start<=end)
	{
		ll mid=(start+end)/2;
		ll require(0);
		for(const ll& ele:default_level)
		{
			require+=max(mid-ele,0LL);
		}
		if(require>k)
		{
			end=mid-1;
		}
		else
		{
			start=mid+1;
		}
	}
	cout<<end;
   	return 0;
}