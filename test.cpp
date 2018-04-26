//
//  11248.cpp
//  L11
//
//  Created by admin on 2018/4/25.
//  Copyright © 2018 admin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define LL long long
#define INF 3000000000

using namespace std;

struct Edge {
    LL from, to, cap, flow;
};

LL n, e, c;
LL cur[105], visit[105], d[105];
vector<Edge> edges;
vector<LL> nodes[105];

bool init() {
    edges.clear();
    for(int i = 0 ; i < 105 ; i++) nodes[i].clear();
    
    cin >> n >> e >> c;
    if(n == 0) return false;
    else {
        for(LL i = 0 ; i < e ; i++) {
            LL a, b, c; cin >> a >> b >> c;
            edges.push_back((Edge){a, b, c, 0});
            edges.push_back((Edge){b, a, 0, 0});
            nodes[a].push_back(edges.size()-2);
            nodes[b].push_back(edges.size()-1);
        }
        return true;
    }
}

bool BFS() {
    memset(visit, 0, sizeof(visit));
    visit[1] = 1; d[1] = 0;
    queue<LL> q;
    q.push(1);
    while(!q.empty()) {
        LL x = q.front(); q.pop();
        for(LL i = 0 ; i < nodes[x].size() ; i++) {
            Edge& e = edges[nodes[x][i]];
            if(!visit[e.to] && e.cap > e.flow) {
                visit[e.to] = 1;
                d[e.to] = d[x] + 1;
                q.push(e.to);
            }
        }
    }
    return visit[n];
}

LL DFS(LL x, LL a) {
    if(x == n || a == 0) return a;
    LL flow = 0, f;
    for(LL& i = cur[x] ; i < nodes[x].size() ; i++) {
        Edge& e = edges[nodes[x][i]];
        if(d[x]+1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
            e.flow += f;
            edges[nodes[x][i]^1].flow -= f;
            flow += f;
            a -= f;
            if(a == 0) break;
        }
    }
    return flow;
}

int main() {
    int kase = 1;
    while(init()) {
        LL maxFlow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            maxFlow += DFS(1, INF);
        }
        
        
        
        if(maxFlow >= c) cout << "Case " << kase++ << ": possible" << endl;
        else {
            vector<LL> ans;
            for(int i = 0 ; i < edges.size() ; i++) {
                if(edges[i].flow > 0 && edges[i].cap > 0) {
                    LL preCap = edges[i].cap, preFlow = edges[i].flow;
                    edges[i].cap = c;
                    LL nowFlow = maxFlow;
                    while(BFS() && nowFlow < c) {
                        memset(cur, 0, sizeof(cur));
                        nowFlow += DFS(1, INF);
                    }
                    if(nowFlow >= c) ans.push_back(i);
                    edges[i].cap = preCap; edges[i].flow = preFlow; edges[i^1].flow = -preFlow;
                }
            }
            
            
            if(ans.empty()) cout << "Case " << kase++ << ": not possible" << endl;
            else {
                sort(ans.begin(), ans.end());
                cout << "Case " << kase++ << ": possible option:";
                for(int i = 0 ; i < ans.size() ; i++) {
                    if(i == 0) cout << "(" << edges[ans[i]].from << "," << edges[ans[i]].to << ")";
                    else cout << ",(" << edges[ans[i]].from << "," << edges[ans[i]].to << ")";
                }
                cout << endl;
            }
        }
    }
}


