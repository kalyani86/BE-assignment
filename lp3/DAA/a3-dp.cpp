#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int recursion(int n,int capacity,vector<int>&wt,vector<int>&price,int ind)
{
    if(ind>=n)
    {
        return 0;
    }

    int pick=0;
    if(capacity>=wt[ind])
    {
        pick=price[ind]+recursion(n,capacity-wt[ind],wt,price,ind+1);
    }
    int notpick=recursion(n,capacity,wt,price,ind+1);
    return max(pick,notpick);
}

int memo(int n,int capacity,vector<int>&wt,vector<int>&price,int ind,vector<vector<int>>&dp)
{
     if(ind>=n)
    {
        return 0;
    }
    if(dp[ind][capacity]!=-1)
    {
        return dp[ind][capacity];
    }
    int pick=0;
    if(capacity>=wt[ind])
    {
        pick=price[ind]+memo(n,capacity-wt[ind],wt,price,ind+1,dp);
    }
    int notpick=memo(n,capacity,wt,price,ind+1,dp);
    dp[ind][capacity]=max(pick,notpick);
    return max(pick,notpick);
}
// Function to print the DP table
void printTable(const vector<vector<int>>& dp, int n, int W) {
    cout << "\nDP Table:\n";
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            cout << setw(5) << dp[i][w];
        }
        cout << endl;
    }
}

// Function to solve the Knapsack problem using dynamic programming and return selected items
int knapsackDP(const vector<int>& weights, const vector<int>& values, int W, vector<int>& selectedItems) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
           int pick=0;
           if(weights[i-1]<=w)
           {
              pick=values[i-1]+dp[i-1][w-weights[i-1]];
           }
           int notpick=dp[i-1][w];

           dp[i][w]=max(pick,notpick);

        }
    }

    // Print the DP table
    printTable(dp, n, W);

    // Backtrack to find the selected items
    int maxProfit = dp[n][W];
    int w = W;
    for (int i = n; i > 0 && maxProfit > 0; i--) {
        if (maxProfit != dp[i - 1][w]) {  // Item i-1 was included
            selectedItems.push_back(i);    // Save the index (1-based) of selected item
            maxProfit -= values[i - 1];
            w -= weights[i - 1];
        }
    }

    return dp[n][W];
}

int main() {
    int choice;
    do {
        cout << "\nKnapsack Problem Solver";
        cout << "\n1. Solve Knapsack Problem using DP";
        cout << "\n2. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int n, W;
            cout << "Enter the number of items: ";
            cin >> n;

            vector<int> weights(n), values(n);
            cout << "Enter the weight and value of each item:\n";
            for (int i = 0; i < n; i++) {
                cout << "Item " << i + 1 << " - Weight: ";
                cin >> weights[i];
                cout << "Item " << i + 1 << " - Value: ";
                cin >> values[i];
            }

            cout << "Enter the maximum capacity of the knapsack: ";
            cin >> W;

            vector<int> selectedItems;
            int maxProfit = knapsackDP(weights, values, W, selectedItems);
            cout << "\nThe maximum profit is: " << maxProfit << endl;

            cout << "Items included in the knapsack (1-based index): ";
            for (int item : selectedItems)
                cout << item << " ";
            cout << endl;

            cout<<"recusive solution:"<<recursion(n,W,weights,values,0)<<endl;
            vector<vector<int>>dp(n,vector<int>(W+1,-1)); //here W+1 imp
            cout<<"memo sol:"<<memo(n,W,weights,values,0,dp)<<endl;

        } else if (choice != 2) {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 2);

    cout << "Program exited.\n";
    return 0;
}