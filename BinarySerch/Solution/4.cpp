#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
using ll=long long;

int count_group(vector<int>& arr, int limit_score)
{
	int ret(1);
	int min_val=arr[0];
	int max_val=arr[0];
	for(int i=1;i<arr.size();++i)
	{
		min_val=min(min_val, arr[i]);
		max_val=max(max_val, arr[i]);
		if(max_val-min_val>limit_score)
		{
			++ret;
			min_val=max_val=arr[i];
		}
	}
	return ret;
}
int main()
{
	int n,m;
	int left=0,right;
	int min_val=numeric_limits<int>::max();
	int max_val=numeric_limits<int>::min();
	vector<int> arr;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	arr.resize(n);
	for(int& ele:arr)
	{
		cin>>ele;
		min_val=min(min_val,ele);
		max_val=max(max_val,ele);
	}
	right=(max_val-min_val);
	while(left<=right)
	{
		int mid=(left+right)>>1;
		if(count_group(arr,mid)>m)
		{
			left=mid+1;
		}
		else
		{
			right=mid-1;
		}
	}
	cout<<left<<"\n";
   	return 0;
}