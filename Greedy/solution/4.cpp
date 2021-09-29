#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

bool cmp(const pair<int, int>& p1, const pair<int, int>& p2)
{
	if(p1.first==p2.first)
	{
		return p1.second>p2.second;
	}
	return p1.first<p2.first;
}
int main()
{
	vector<pair<int, int>> meats;
	int n,m;
	int total_weight(0);
	int cost=-1;
	int previous_cost=-1;
	int ans=numeric_limits<int>::max();
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
	for(int i=0;i<n;++i)
	{
		int weight, c;
		cin>>weight>>c;
		meats.push_back({c,weight});
	}
	sort(begin(meats), end(meats), cmp);
	for(int i=0;i<n;++i)
	{
		total_weight+=meats[i].second;
		if(previous_cost!=meats[i].first)
		{
			cost=previous_cost=meats[i].first;
		}
		else
		{
			cost+=meats[i].first;
		}
		if(total_weight>=m)
		{
			ans=min(cost,ans);
		}
	}
	if(total_weight<m)
	{
		cout<<-1;
	}
	else
	{
		cout<<ans;
	}
    return 0;
}