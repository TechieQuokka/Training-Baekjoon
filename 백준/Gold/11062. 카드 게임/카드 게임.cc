#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        vector<int> card(N);
        for (int i = 0; i < N; ++i) {
            cin >> card[i];
        }
        
        // 전체 점수의 합 계산
        int total = 0;
        for (int i = 0; i < N; ++i) {
            total += card[i];
        }
        
        // DP 테이블 초기화
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        // DP 테이블 채우기
        for (int len = 1; len <= N; ++len) {
            for (int i = 0; i <= N - len; ++i) {
                int j = i + len - 1;
                if (len == 1) {
                    dp[i][j] = card[i];
                } else {
                    int choose_left = card[i] - dp[i + 1][j];
                    int choose_right = card[j] - dp[i][j - 1];
                    dp[i][j] = max(choose_left, choose_right);
                }
            }
        }
        
        // 근우의 점수 계산
        int geunwoo_score = (total + dp[0][N - 1]) / 2;
        cout << geunwoo_score << endl;
    }
    return 0;
}