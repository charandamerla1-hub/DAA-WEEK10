#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Calculates the maximum profit for the 0/1 Knapsack problem and prints the selected items
int knapsackDP(int n, const vector<int>& weights, const vector<int>& profits, int capacity) {
    // DP table initialized to 0
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build table dp[][] in bottom-up manner
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], profits[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int maxProfit = dp[n][capacity];
    cout << "The Maximum profit: " << maxProfit << "\n";

    // Backtracking to find the specific items included in the optimal solution
    vector<int> solution(n, 0);
    int remainingProfit = maxProfit;
    int currentWeight = capacity;

    for (int i = n; i > 0 && remainingProfit > 0; i--) {
        // If the profit came from the top row, the item wasn't included
        if (dp[i - 1][currentWeight] == remainingProfit) {
            solution[i - 1] = 0;
        } else {
            // Item was included
            solution[i - 1] = 1;
            remainingProfit -= profits[i - 1];
            currentWeight -= weights[i - 1];
        }
    }

    // Print the solution array
    cout << "Solution : \n";
    for (int i = 0; i < n; i++) {
        cout << solution[i] << " ";
    }
    cout << "\n";

    return maxProfit;
}

int main() {
    int n = 4;
    int capacity = 8;
    vector<int> weights = {2, 3, 4, 5};
    vector<int> profits = {1, 2, 5, 6};

    knapsackDP(n, weights, profits, capacity);

    return 0;
}
