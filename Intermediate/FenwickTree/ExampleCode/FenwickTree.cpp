#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

ll Sum(int i, const ll* fenwickTree)
{
    ll sum(0);
    while(i>0)
    {
        sum+=fenwickTree[i];
        i-=(i&(-i));
    }
    return sum;
}

void Update(ll val,int i, int n, ll* fenwickTree)
{
    while(i<=n)
    {
        fenwickTree[i]+=val;
        i+=(i&-i);
    }
    return;
}
int main()
{
	ll* fenwickTree=0;
	ll* arr=0;
	int n,q;
	cin>>n>>q;
	arr=new ll[n+1];
	fenwickTree=new ll[n+1];
	fenwickTree[0]=0;
    for(int i=1;i<=n;++i)
    {
        cin>>arr[i];
        fenwickTree[i]=0;
    }
    for(int i=1;i<=n;++i)
    {
        Update(arr[i],i,n,fenwickTree);
    }
    for(int i=0;i<q;++i)
    {
        int start, end;
        cin>>start>>end;
        cout<<Sum(end,fenwickTree)-Sum(start-1,fenwickTree)<<"\n";
    }
	return 0;
}