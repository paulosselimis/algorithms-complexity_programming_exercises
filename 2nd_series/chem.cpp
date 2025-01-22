#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 2500;
static const long long INF = LLONG_MAX / 4;

static int A[MAXN+1][MAXN+1];
static long long costArr[MAXN+1][MAXN+1];
static long long dp[MAXN+1][MAXN+1];
static long long partialCol[MAXN+1][MAXN+1];

int main(){
    
    int N, K;
    scanf("%d %d", &N, &K);

    // ---- 1) Διάβασμα του πίνακα A (μόνο το πάνω τρίγωνο) και συμμετρική συμπλήρωση:
  
    // Αρχικοποίηση σε 0 
    memset(A, 0, sizeof(A));

    for(int i=1; i<=N-1; i++){
        for(int j=i+1; j<=N; j++){
            int val;
            scanf("%d", &val);
            A[i][j] = val;
            A[j][i] = val;
        }
    }

    // ---- 2) Precompute cost(i,j) με τον τύπο:
    //         cost(i,j) = cost(i,j-1) + sum_{p=i..j-1} A[p,j]
    //         Θα ονομάσουμε costArr[i][j] το κόστος για το διάστημα [i..j].
    //         Για γρηγοράδα, χρησιμοποιούμε partialCol[col][x] = A[1][col] + ... + A[x][col].
    //         Έτσι sum_{p=i..j-1} A[p][j] = partialCol[j][j-1] - partialCol[j][i-1].

    memset(partialCol, 0, sizeof(partialCol));
    for(int col=1; col<=N; col++){
        long long runSum = 0;
        for(int x=1; x<=N; x++){
            runSum += A[x][col];
            partialCol[col][x] = runSum;
        }
    }

    // costArr[i][i] = 0, κι έπειτα:
    // costArr[i][j] = costArr[i][j-1] + (partialCol[j][j-1] - partialCol[j][i-1])
    memset(costArr, 0, sizeof(costArr));

    for(int i=1; i<=N; i++){
        costArr[i][i] = 0;
        for(int j=i+1; j<=N; j++){
            long long sumP = partialCol[j][j-1] - partialCol[j][i-1];
            costArr[i][j] = costArr[i][j-1] + sumP;
        }
    }

    // ---- 3) Υλοποίηση dp[i][k]: ελάχιστο κόστος για τις πρώτες i ουσίες σε k φιάλες.
    //      dp[i][k] = min_{k-1 <= p < i} ( dp[p][k-1] + costArr[p+1][i] ).
    // Αρχικοποίηση:
    for(int i=0; i<=N; i++){
        for(int c=0; c<=K; c++){
            dp[i][c] = INF; 
        }
    }
    dp[0][0] = 0;  // 0 ουσίες, 0 φιάλες => κόστος 0

    // Μία φιάλη (c=1) => dp[i][1] = costArr[1][i]
    for(int i=1; i<=N; i++){
        dp[i][1] = costArr[1][i];
    }

    // ---- 4) Συμπλήρωση του DP για c=2..K
    

    for(int c=2; c<=K; c++){
        // Τουλάχιστον c ουσίες για c φιάλες => i>=c
        for(int i=c; i<=N; i++){
            long long bestVal = INF;
            // Δοκιμάζουμε p από (c-1) έως (i-1)
            // (πρέπει να έχουμε ήδη βάλει p ουσίες σε c-1 φιάλες)
            for(int p=c-1; p<i; p++){
                long long cand = dp[p][c-1] + costArr[p+1][i];
                if(cand < bestVal){
                    bestVal = cand;
                }
            }
            dp[i][c] = bestVal;
        }
    }

    // ---- 5) Έξοδος: dp[N][K] είναι το ελάχιστο κόστος
    printf("%lld\n", dp[N][K]);

    return 0;
}
