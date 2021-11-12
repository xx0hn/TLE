#include <iostream>
#include <vector>
using namespace std;

char BASE[][6]={
	"  *  ",
	" * * ",
	"*****"
};
vector<string> MAP;

void Solve(int h, int x, int y)
{
	if(h==3)
	{
		for(int i=0;i<3;++i)
		{
			for(int j=0;j<5;++j)
			{
				MAP[y+i][x+j]=BASE[i][j];
			}
		}
	}
	else
	{
		Solve(h/2,x,y);
		Solve(h/2,x+h/2,y+h/2);
		Solve(h/2,x-h/2,y+h/2);
	}
}
int main()
{
	int n;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	string row(2*n+1,' ');
	MAP.resize(n,row);
	Solve(n,n-3,0);
	for(int i=0;i<n;++i)
	{
		cout<<MAP[i];
		cout<<"\n";
	}
	return 0;
}