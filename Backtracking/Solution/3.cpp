#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll=long long;

vector<ll> numberArray;

void Tracking(ll preventNumber, int max_number)
{
    for(int i=max_number-1;i>=0;--i)
    {
        Tracking(preventNumber*10+i,i);
    }
    numberArray.push_back(preventNumber);
}

int main()
{
	int n;
	int sum(0);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	if(n>=1023)
	{
		cout<<-1;
		return 0;
	}
	for(int i=0;i<10;++i)
	{
		Tracking(i,i);
	}
	sort(begin(numberArray), end(numberArray));
	cout<<numberArray[n];
	return 0;
}
