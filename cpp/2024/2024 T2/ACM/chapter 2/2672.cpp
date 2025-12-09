//初始思路是暴力枚举每一个数列，但是输入n=3000，时间复杂度过高，遂放弃
//本题不会，遂找题解
//哈希表可以使匹配两个数的和的这一过程的时间复杂度降低到O(1)
//思路上: 定义一个二位数组dp，用于存放以第i，j个数结尾的斐波那契数列的长度。
//从数列的顶部开始向下迭代，用哈希表中的find函数即可实现匹配的过程。
//最后找到第一个数和第二个数，以及数组的长度，输出即可，不需要存下整个数组。

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <hash_map>
using namespace std;
using __gnu_cxx::hash_map;
#define N 3010
int a[N];
int dp[N][N];
int n;
hash_map<int,int>mp;
hash_map<int ,int >::iterator it;
int main()
{
    int test=0;
    while(~scanf("%d",&n))
    {
        if(test!=0)
            printf("\n");
        test++;
        for(int i=1; i<=n; i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                 dp[i][j]=1;
        mp.clear();//初始化

        int m=0,x,y;
        x=a[1];
        for(int i=n;i>=1;i--)
        {
            for(int j=1;j<i;j++)
            {
                int k=a[i]+a[j];
                it=mp.find(k);
                if(it!=mp.end())
                {
                    dp[j][i]=dp[i][it->second]+1;
                    if(dp[j][i]>m)
                    {
                        m=dp[j][i];
                        x=j;
                        y=i;
                    }
                }
            }
            mp[a[i]]=i;
        }

        if(n==1)
        {
            printf("1\n%d\n",a[1]);
            continue;
        }
        if(n==2)
        {
            printf("2\n%d %d\n",a[1],a[2]);
            continue;
        }
        if(m==0)
        {
            printf("2\n%d %d\n",a[1],a[2]);
        }

        else
        {
            printf("%d\n",m+1);
            x=a[x],y=a[y];
            printf("%d",x);
            for(int i=1;i<=m;i++)
            {
                printf(" %d",y);
                int z=x+y;
                x=y;
                y=z;
            }
            printf("\n");
        }
    }
    return 0;
}
