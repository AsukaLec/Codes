#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

struct node
{
    int l;
    int w;
};

int cmp(struct node x,struct node y)
{
    if(x.l==y.l)
        return x.w<y.w;
    else
        return x.l<y.l;
}


int Find(struct node t[],int n)
{
    //数组b表示木棒分组的序号
    int b[5003];
    memset(b, 0, sizeof(b));
    b[0]=1;

    int k;
    for (int i=1; i<n; i++)
    {
        //计算第i个木棒的的分组序号
        k=0;
        for (int j=0; j<i; j++)
            if (t[i].w<t[j].w && k<b[j])
                k=b[j];    //找出尽量大的k
        b[i]=k+1;
    }

    //查找最大的分组序号（数组b中的最大值）
    int Max=0;
    for (int i=0; i<n; i++)
        if (b[i]>Max) Max=b[i];
        
    return Max;
}

int main(void)
{
    int ncase;
    struct node t[5005];

    scanf("%d",&ncase);
    while(ncase--)
    {
        int n;
        scanf("%d",&n);
        for (int i=0; i<n; i++)
            scanf("%d %d",&t[i].l,&t[i].w);

        sort(t,t+n,cmp);
        printf("%d\n",Find(t,n));
    }
    return 0;
}