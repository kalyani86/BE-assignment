#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int> &weight, vector<int> &value, int index, int capacity, vector<vector<int>> &dp) {
    if (index == 0) {
        if (weight[0] <= capacity)
            return value[0];
        else
            return 0;
    }

    if (dp[index][capacity] != -1)
        return dp[index][capacity];

    int include = 0, exclude = 0;
    if (weight[index] <= capacity) {
        include = value[index] + solve(weight, value, index - 1, capacity - weight[index], dp);
    }
    exclude = solve(weight, value, index - 1, capacity, dp);

    return dp[index][capacity] = max(include, exclude);
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n), value(n);

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));

    int result = solve(weight, value, n - 1, capacity, dp);

    cout << "\nMaximum value that can be obtained: " << result << endl;

    return 0;
}
