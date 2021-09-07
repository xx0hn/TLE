#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> prime;
	vector<bool> isPrime(2000001,true);
	int limits=sqrt(2000000);
	for(int i=2;i<=2000000;++i)
	{
		if(!isPrime[i])continue;
		prime.push_back(i);
		for(int j=i*2;j<=2000000;j+=i)
		{
			isPrime[j]=false;
		}
	}
	int t;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		int k;
		cin>>k;
		if(isPrime[k])cout<<0<<"\n";
		else
		{
			auto back=upper_bound(begin(prime), end(prime), k);
			auto front=back-1;
			cout<<*back-*front<<"\n";
		}
	}
}