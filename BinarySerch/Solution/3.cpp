#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll=long long;

ll solve(vector<ll>& minSizeArray, vector<ll>& maxSizeArray, ll t)
{
    ll ret(0);
    vector<ll> store;
    for(int i=0;i<minSizeArray.size();++i)
    {
        for(int j=i+1;j<minSizeArray.size();++j)
        {
            store.push_back(minSizeArray[j]-minSizeArray[i]);
        }
    }
    sort(begin(store), end(store));
    for(int i=0;i<maxSizeArray.size();++i)
    {
        for(int j=i+1;j<maxSizeArray.size();++j)
        {
            ll target=t-(maxSizeArray[j]-maxSizeArray[i]);
            ret+=upper_bound(begin(store), end(store), target)-lower_bound(begin(store), end(store), target);
        }
    }
	return ret;
}

int main()
{
    ll t;
    int n,m;
    vector<ll> B_sum;
    vector<ll> A_sum;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t>>n;
    A_sum.resize(n+1);
    for(int i=1;i<=n;++i)
    {
        ll val;
        cin>>val;
        A_sum[i]=A_sum[i-1]+val;
    }
	cin>>m;
	B_sum.resize(m+1);
    for(int i=1;i<=m;++i)
    {
        ll val;
        cin>>val;
        B_sum[i]=B_sum[i-1]+val;
    }
    if(n>m)
    {
        cout<<solve(A_sum,B_sum,t);
    }
    else
    {
        cout<<solve(B_sum,A_sum,t);
    }
    return 0;
}