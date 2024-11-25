#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if a given minimum distance `D` is feasible
bool isFeasible(int D, int N, const vector<pair<int, int>>& intervals) {
    int count = 1; // Place the first store
    int lastPosition = intervals[0].first; // Place it at the start of the first interval

    for (const auto& interval : intervals) {
        int start = max(interval.first, lastPosition + D);
        while (start <= interval.second) {
            count++;
            lastPosition = start;
            start += D; // Move to the next possible position
            if (count == N) return true; // Successfully placed all stores
        }
    }
    return false;
}

int maximizeMinDistance(int N, int M, vector<pair<int, int>>& intervals) {
    // Sort intervals based on starting positions
    sort(intervals.begin(), intervals.end());

    // Define binary search bounds
    int low = 1;
    int high = (intervals.back().second - intervals.front().first) / (N - 1);
    int result = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isFeasible(mid, N, intervals)) {
            result = mid; // Store the feasible distance
            low = mid + 1; // Try for a larger minimum distance
        } else {
            high = mid - 1; // Reduce the search space
        }
    }
    return result;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);


    vector<pair<int, int>> intervals(M);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &intervals[i].first, &intervals[i].second);
    }

    printf("%d\n", maximizeMinDistance(N, M, intervals));

    return 0;
}
