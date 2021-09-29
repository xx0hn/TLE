#include <iostream>
#include <stack>
using namespace std;

int main()
{
    string ppap;
    stack<int> p_stack;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>ppap;
    for(int i=0;i<ppap.size();)
    {
        if(ppap[i]=='A')
        {
            //PPAP 문잔지 검사
            if(i+1<ppap.size()&&ppap[i+1]=='P'&&p_stack.size()>=2)
            {
                p_stack.pop();
                i=i+2;
            }
            else
            {
                cout<<"NP";
                return 0;
            }
        }
        else
        {
            p_stack.push(1);
            i=i+1;
        }
    }
    //최종적으로 PPAP 문자열인지 검사
    if(p_stack.size()==1)
    {
        cout<<"PPAP";
    }
    else
    {
        cout<<"NP";
    }
    return 0;
}