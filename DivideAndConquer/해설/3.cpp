#include <iostream>
#include <vector>
using namespace std;
using matrix=vector<vector<int>>;

//행렬곱
matrix mul(matrix& m1, matrix& m2)
{
    matrix result;
    result.resize(m1.size(), vector<int>(m1.size(),0));
    for(int i=0;i<m1.size();++i)
    {
        for(int j=0;j<m1.size();++j)
        {
            for(int k=0;k<m1.size();++k)
            {
                result[i][j]+=m1[i][k]*m2[k][j];
                result[i][k]%=1000;
            }
        }
    }
    return result;
}

matrix solve(matrix& m, long long b)
{
    //고속 제곱
    if(b==1LL)return m;
    matrix ret=solve(m,b>>1);
    ret=mul(ret, ret);
    if(b&1LL)
    {
        ret=mul(ret, m);
    }
    return ret;
}
int main()
{
    int n;
    long long b;
    matrix m;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>b;
    m.resize(n,vector<int>(n));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin>>m[i][j];
        }
    }
    m=solve(m,b);
    for(auto& v:m)
    {
        for(auto val:v)
        {
            cout<<val%1000<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
