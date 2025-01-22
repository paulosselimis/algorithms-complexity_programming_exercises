#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int N, K;
    scanf("%d %d", &N, &K);

    vector<int> h(N+1);
    for(int i=1; i<=N; i++){
        scanf("%d", &h[i]);
    }

    vector<long long> dp(N+1, 0LL);

    for(int i=1; i<=N; i++){

        int currentMax = 0;  

        for(int r=1; r<=K && r<=i; r++){
           
            currentMax = max(currentMax, h[i - r + 1]); 
            long long candidate = dp[i-r] + (long long)currentMax * r;
            dp[i] = max(dp[i], candidate);
        }
    }

    printf("%lld\n", dp[N]);
    return 0;
}