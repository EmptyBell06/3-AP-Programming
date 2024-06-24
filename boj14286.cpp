#include <bits/stdc++.h>

using namespace std;

int n, m;
int source, sink;

// 간선에 대한 구조체 선언
struct edge{
    int from, to, capacity, flow;
    edge* reverse_edge; // 역방향 간선에 대한 정보를 받음(얘도 간선이기에 구조체에 대한 포인터로 선언)
    edge(int u, int v, int c) : from(u), to(v), capacity(c), flow(0)
    {}
    // residual capacity
    int residual(){
        return capacity-flow;
    }
    // 유량에 대한 정보 저장
    void add_flow(int amount){
        flow += amount;
        reverse_edge -> flow-=amount;
    }
};

vector<edge*> adj[501]; // 그래프 선언

// 간선 추가
void add_edge(int u, int v, int c, bool dir = true)
{
    edge* e1 = new edge(u, v, c); // 순방향 간선
    edge* e2 = new edge(v, u, dir?0:c); // 역방향 간선
    e1 -> reverse_edge = e2;
    e2 -> reverse_edge = e1;
    // e1과 e2에는 u, v, c에 대한 값이 모두 저장된 상태

    // 무향 그래프 생성
    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

// 최대 유량 계산
int networkFlow(int source, int sink)
{
    int max_flow = 0;
    while(true){
        // 부모 및 조상 노드 탐색을 위한 벡터 선언
        vector<edge*> parent(501, nullptr);

        // bfs 느낌으로 탐색하며 residual graph 형성
        queue<int> q;
        q.push(source);
        while(!q.empty() and parent[sink] == nullptr){
            int now = q.front();
            q.pop();
            for(int i=0; i<adj[now].size(); i++){
                int nxt = adj[now][i] -> to;
                if(adj[now][i] -> residual() > 0 and parent[nxt] == nullptr){
                    parent[nxt] = adj[now][i];
                    q.push(nxt);
                }
            }
        }
        // sink에서 갈 수 있는데가 없네? break
        if(parent[sink] == nullptr) break;

        // 최대 유량은 최소 중 최대를 찾는 과정이다
        int amount = 987654321;
        for(int p=sink; p!=source; p = parent[p] -> from){
            amount = min(amount, parent[p] -> residual()); // 유량 업데이트
        }
        for(int p=sink; p!=source; p = parent[p] -> from){
            parent[p] -> add_flow(amount); // 위 업데이트를 기반으로 부모의 유량 업데이트
        }
        max_flow += amount;
    }
    return max_flow;
}

void input()
{
    cin >> n >> m;

    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c, false);
    }
    cin >> source >> sink;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input();
    cout << networkFlow(source, sink) << "\n";

    return 0;
}