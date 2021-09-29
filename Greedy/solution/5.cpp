#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
using ll=long long;
int main()
{
	vector<ll> negative;
	vector<ll> positive;
	ll ans(0);
	int n;
	int one_cnt(0), zero_cnt(0);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	cin>>n;
	for(int i=0;i<n;++i)
	{
		ll temp;
		cin>>temp;
		if(temp==1LL)
		{
			++one_cnt;
		}
		else if(temp==0LL)
		{
			++zero_cnt;
		}
		else if(temp<0LL)
		{
			negative.push_back(temp);
		}
		else
		{
			positive.push_back(temp);
		}
	}
	sort(begin(negative),end(negative));
	sort(rbegin(positive),rend(positive));
	for(int i=0;i+1<positive.size();i+=2)
	{
		ll e1=positive[i];
		ll e2=positive[i+1];
		ans+=(e1*e2);
	}
	if(positive.size()%2==1)
	{
		ans+=positive.back();
	}
	ans+=one_cnt;
	for(int i=0;i+1<negative.size();i+=2)
	{
		ll e1=negative[i];
		ll e2=negative[i+1];
		ans+=(e1*e2);
	}
	if(negative.size()%2==1&&!zero_cnt)
	{
		ans+=negative.back();
	}
	cout<<ans;
    return 0;
}