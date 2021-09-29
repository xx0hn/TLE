#include <iostream>
#include <queue>
using namespace std;
using ll=long long;
int main()
{
	ll ans(0);
	priority_queue<ll> pq;
	int n,k;
	ll start,end;
	ll previous, now;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>previous;
	start=end=previous;
	for(int i=1;i<n;++i)
	{
		cin>>now;
		pq.push(now-previous-1);
		end=previous=now;
	}
	ans=end-start+1;
	while(--k)
	{
		ans-=pq.top();
		pq.pop();
	}
	cout<<ans;
	return 0;
}
