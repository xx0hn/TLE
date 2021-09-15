#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
using ll=long long;

ll GetCookCompleteTime(vector<int>& cookTime, ll k);
ll Solve(vector<int>& cookTime, int c, ll k, int cookIndx);
int main()
{
	int n,c;
	int sum(0);
	vector<int> cookTime;
	ll ans,k;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>c;
	cookTime.resize(n);
	for(int& t:cookTime)
	{
		cin>>t;
	}
	ans=Solve(cookTime,c,k,0);
	cout<<ans;
	return 0;
}

ll Solve(vector<int>& cookTime, int c, ll k, int cookIndex)
{
	if(c==0)
	{
		return GetCookCompleteTime(cookTime, k);
	}
	else
	{
		ll ret=numeric_limits<ll>::max();
		for(int i=cookIndex;i<cookTime.size();++i)
		{
			if(cookTime[i]==1)continue;
			cookTime[i]-=1;
			ret=min(ret, Solve(cookTime,c-1,k,i));
			cookTime[i]+=1;
		}
		ret=min(ret, GetCookCompleteTime(cookTime,k));
		return ret;
	}
}

ll GetCookCompleteTime(vector<int>& cookTime, ll k)
{
	ll left=0;
	ll right=1000000000000LL;
	while(left+1<right)
	{
		ll mid=(left+right)>>1;
		ll cnt(0);
		for(int i=0;i<cookTime.size();++i)
		{
			cnt+=(mid/cookTime[i]);
		}
		if(cnt>=k)
		{
			right=mid;
		}
		else
		{
			left=mid;
		}
	}
	return right;
}