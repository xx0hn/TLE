#include <iostream>
#include <vector>
#include <limits>
using namespace std;
using ll=long long;

ll max_val=numeric_limits<ll>::min();
ll min_val=numeric_limits<ll>::max();

void Solve(ll preventNum, int numberIndex, const vector<int>& numbers, vector<int>& operationCount)
{
	if(numberIndex==numbers.size())
	{
		max_val=max(preventNum,max_val);
		min_val=min(preventNum,min_val);
	}
	else
	{
		if(operationCount[0]>0)
		{
			operationCount[0]--;
			Solve(preventNum+numbers[numberIndex], numberIndex+1, numbers, operationCount);
			operationCount[0]++;
		}
		if(operationCount[1]>0)
		{
			operationCount[1]--;
			Solve(preventNum-numbers[numberIndex], numberIndex+1, numbers, operationCount);
			operationCount[1]++;
		}
		if(operationCount[2]>0)
		{
			operationCount[2]--;
			Solve(preventNum*numbers[numberIndex], numberIndex+1, numbers, operationCount);
			operationCount[2]++;
		}
		if(operationCount[3]>0)
		{
			operationCount[3]--;
			Solve(preventNum/numbers[numberIndex], numberIndex+1, numbers, operationCount);
			operationCount[3]++;
		}
	}
	return;
} 

int main()
{
	int n;
	vector<int> numbers;
	vector<int> operCnt(4);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	numbers.resize(n);
	for(int i=0;i<n;++i)
	{
		cin>>numbers[i];
	}
	for(int i=0;i<4;++i)
	{
		cin>>operCnt[i];
	}
	Solve(numbers[0],1,numbers,operCnt);
	cout<<max_val<<"\n"<<min_val<<"\n";
	return 0;
}
