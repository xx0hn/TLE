#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ll=long long;


//Bottom-Up


int main()
{
	ll* segment_tree=0;
	ll* arr=0;
	int n,q;
	int segment_tree_height(1);
	cin>>n>>q;
	arr=new ll[n+1];
	while((1<<segment_tree_height)<n)
	{
		++segment_tree_height;
	}
	segment_tree=new ll[(2<<segment_tree_height)];
	for(int i=1;i<=n;++i)
	{
		cin>>arr[i];
        segment_tree[(1<<segment_tree_height)+i-1]=arr[i];
	}
    for(int i=(1<<segment_tree_height)+n;i<(2<<segment_tree_height);++i)
    {
        segment_tree[i]=0;
    }
    for(int i=1;i<=n;++i)
    {
        int node=(1<<segment_tree_height)+i-1;
        ll val=segment_tree[node];
        node=node/2;
        while(node>0)
        {
            segment_tree[node]+=val;
            node=node/2;
        }
    }
	for(int i=0;i<q;++i)
	{
		int start, end;
		cin>>start>>end;
		ll ans(0);
        start--;
        end--;
        start+=(1<<segment_tree_height);
        end+=(1<<segment_tree_height);
        while(start<end)
        {
            if(start%2)ans+=segment_tree[start++];
            if(!(end%2))ans+=segment_tree[end--];
            start/=2;
            end/=2;
        }
        if(start==end)
        {
            ans+=segment_tree[start];
        }
        cout<<ans<<"\n";
	}
	return 0;
}