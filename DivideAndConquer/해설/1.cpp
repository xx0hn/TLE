#include <iostream>
#include <vector>
using namespace std;

void moo(int n, int len, int k)
{
    //len -> S(k-1) 의 길이
    //new len -> S(k) 의 길이
	int new_len=(len*2)+(k+3);
    
    //기저 사례
    //S(0)에서 찾을 수 있을 때
	if(n<=3)
	{
		if(n==1)
		{
			cout<<"m";
		}
		else
		{
			cout<<"o";
		}
	}
	else if (new_len<n)
	{
        //S(k)보다 작은 위치에서 찾음 
		moo(n,new_len,k+1);
	}
	else
	{
        //S(k-1) 뒤에 붙은 moo..에 있는 문자를 꺼냄
		if(n>len&&n<=len+k+3)
		{
			if(n-len==1)
			{
				cout<<"m";
			}
			else
			{
				cout<<"o";
			}
		}
		else
		{
            //뒤에 있는 S(k-1)부분에서 탐색
			moo(n-(len+k+3), 3,1);
		}
	}
}

int main()
{
	int n;
	cin>>n;
	moo(n,3,1);
	return 0;
}