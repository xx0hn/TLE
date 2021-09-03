#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ll=long long;


//Bottom-Up

ll UpdateSegmentTree(ll* segment_tree, const ll* arr, int left, int right,int node=1);
ll Query(ll* segment_tree,int left, int right, int start, int end, int node=1);

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
    memset(segment_tree,0,sizeof(ll)*(2<<segment_tree_height));
	for(int i=1;i<=n;++i)
	{
		cin>>arr[i];
        segment_tree[(1<<segment_tree_height)+i-1]=arr[i];
	}
	for(int i=0;i<q;++i)
	{
		int start, end;
		cin>>start>>end;
		cout<<Query(segment_tree, 1,n,start,end)<<"\n";
	}
	return 0;
}

ll UpdateSegmentTree(ll* segment_tree, const ll* arr, int left, int right,int node)
{
	if(left==right)
	{
		return segment_tree[node]=arr[left];
	}
	int mid=(left+right)/2;
	return segment_tree[node]=UpdateSegmentTree(segment_tree,arr,left,mid,node*2)+UpdateSegmentTree(segment_tree,arr,mid+1,right,node*2+1);
}
ll Query(ll* segment_tree,int left, int right, int start, int end, int node)
{
	if(left>end||right<start)
	{
		return 0;
	}
	if(start<=left&&right<=end)
	{
		return segment_tree[node];
	}
	int mid=(left+right)/2;
	return Query(segment_tree,left,mid,start,end,node*2)+Query(segment_tree,mid+1,right,start,end,node*2+1);
}