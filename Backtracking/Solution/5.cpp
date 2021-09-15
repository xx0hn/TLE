#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


bool isPrime(int num)
{
	if(num==1)return false;
	int limit=sqrt(num);
	for(int i=2;i<=limit;++i)
	{
		if(num%i==0)
		{
			return false;
		}
	}
	return true;
}

void Tracking(int digit ,int n,int num=0)
{
	if(digit==n)
	{
		cout<<num<<"\n";
	}
	else
	{
		for(int i=1;i<=9;++i)
		{
			if(isPrime(num*10+i))
			{
				Tracking(digit+1,n,num*10+i);
			}			
		}
	}
}
int main()
{

	int n;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	Tracking(0,n);
	return 0;
}
