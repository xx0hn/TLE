#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n, k,next_n=1, index;
	vector<int> arr;
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	arr.resize(n+1);
	index = n;
    //next_n = 현재 배치할 사람 번호
	while (k!=0)
	{
		if (k >=index)
		{
			arr[index] = next_n++;
			--index;
			k = k - index;
		}
		else
		{
			arr[k + 1] = next_n++;
			k = 0;
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		cout << (arr[i] == 0 ? next_n++ : arr[i])<<" ";
	}
	return 0;
}