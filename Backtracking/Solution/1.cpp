#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void DFS(vector<int>& arr, vector<int>& output, int m)
{
	if(output.size()==m)
	{
		for(int i=0;i<output.size();++i)
		{
			cout<<output[i]<<" ";
		}
		cout<<"\n";
		return;
	}
	else
	{
		int last_used(-1)
		for(int i=0;i<arr.size();++i)
		{
			if(last_used==arr[i])continue;
			
			output.push_back(arr[i]);
			last_used=arr[i];
			DFS(arr,output,m);
			output.pop_back();
		}
		return;
	}
}

int main()
{
	int n,m;
	vector<int> output;
	vector<int> arr;	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;++i)
	{
		int val;
		cin>>val;
		arr.push_back(val);
	}
    sort(arr.begin(), arr.end());
	DFS(arr,output,m);
	return 0;
}
