#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

ll t;
ll m, n;

void solve()
{
    cin >> m >> n;
    vector<pair<ll, ll>> v;
    for(ll i=0; i<n; i++){
        ll x, y;
        cin >> x >> y;
        // 연결관계의 표현 - x+m과 y+m은 결국 한 사이클 돈 후 매칭과 같으므로 동치
        if(x<=y){
            v.emplace_back(x, y);
            v.emplace_back(x+m, y+m);
        }
        else v.emplace_back(x, y+m); // x에서 연결되는 요소는 더 큰 값으로만(그리디를 위함)
    }
    sort(v.begin(), v.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq; // 최소 힙
    
    // 벡터 v, pt 이용해 순회
    ll pt = 0;
    for(; pt<(ll)v.size();){
        ll y=v[pt].first;
        pq.push(v[pt].second);

        // 동일한 x 값을 가진 (x, y) 집합 모두 힙에 추가
        for(pt++; pt<(ll)v.size(); pt++){
            if(v[pt].first != v[pt-1].first) break;
            pq.push(v[pt].second);
        }

        ll x = m*2;
        if(pt<(ll)v.size()) x = v[pt].first;

        // x가 구간 [x, y]에서 매칭 가능한지 판별
        for(ll i=0; i<x-y and !pq.empty(); i++){
            
            // 매칭이 불가능한 경우 - 종료
            if(pq.top()<y+i){
                cout << "NO\n";
                return;
            }

            pq.pop(); // 최상단 제거 - 아, 그리디적으로 매칭했구나!
        }
    }
    if(pq.empty() and m>=n) cout << "YES\n"; // 전부 매칭됨
    else cout << "NO\n"; // pq 안 비었다? 매칭 안 된 것 존재
}

void input()
{
    cin >> t;
    while(t--){
        solve();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input();

    return 0;
}