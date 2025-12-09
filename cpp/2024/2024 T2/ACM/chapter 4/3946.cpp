#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include<map>
#include <queue>
using namespace std;

const int MAXN=100005;
#define INF 0xffffffffffffffff
#define SSS 1000000
#define ll unsigned long long

struct qnode
{
    int v;
    ll c;
    qnode(int _v=0,ll _c=0):v(_v),c(_c){}
    bool operator< (const qnode &r)const
    {
        return c>r.c;
    }
};
struct Edge
{
    int v;
    ll cost;
    Edge(int _v=0,ll _cost=0):v(_v),cost(_cost){}
};
vector< Edge> E[MAXN];
bool vis[MAXN];
ll dist[MAXN];
void Dijkstra(int n,int start)//点的编号从1开始
{
    memset(vis,false, sizeof(vis));
    for(int i=1;i<=n;i++)dist[i]=INF;
    priority_queue<qnode> que;
    while(!que.empty())que.pop();
    dist[start]= 0;
    que.push(qnode(start,0));
    qnode tmp;
    while(!que.empty())
    {
        tmp=que.top();
        que.pop();
        int u=tmp.v;
        if(vis[u]) continue;
        vis[u]= true;
        for(int i = 0;i < E[u].size();i++)
        {
            int v=E[tmp.v][i].v;
            ll cost = E[u][i].cost;
            ll dist_u = dist[u] / SSS * SSS;
            if(!vis[v] && dist[v] > dist_u+cost)
            {
                dist[v] = dist_u + cost;
                que.push(qnode(v, dist[v]));
            }
        }
    }
}
void addedge(int u,int v,ll w)
{
    E[u].push_back(Edge(v ,w));
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        for (int i = 0; i < MAXN; i++) E[i].clear();
        int n,m;
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; i++)
        {
            int u,v,b;
            ll w;
            cin >> u >> v >> w >> b;

            w = w * SSS + b; //处理权值

            addedge(u + 1, v + 1, w);  //注意从1开始
            addedge(v + 1, u + 1, w);
        }
        Dijkstra(n,1);
        ll ans1 = 0,ans2 = 0;
        for (int i = 2; i <= n; i++)
        {
            ans1 += dist[i] / SSS;
            ans2 += dist[i] % SSS;
        }
        cout << ans1 << " " << ans2 << endl;

    }
    return 0;
}

