#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Item {
public:
    int weight;
    int value;

    Item(int w, int v) : weight(w), value(v) {}
};

class Node {
public:
    int level;
    int profit;
    int weight;
    double bound;

    Node(int lvl = -1, int w = 0, int p = 0) : level(lvl), weight(w), profit(p), bound(0) {}
};

class Knapsack {
public:
    int W;  // Maximum weight of the knapsack
    vector<Item> items;

    Knapsack(int maxWeight) : W(maxWeight) {}

    // Function to add an item
    void addItem(int weight, int value) {
        items.push_back(Item(weight, value));
    }

    // Function to calculate the upper bound on maximum profit for a given node
    double calculateBound(Node u) {
        if (u.weight >= W) return 0;  // If overweight, bound is zero (not feasible)

        double profitBound = u.profit;
        int j = u.level + 1;
        int totWeight = u.weight;

        while ((j < items.size()) && (totWeight + items[j].weight <= W)) {
            totWeight += items[j].weight;
            profitBound += items[j].value;
            j++;
        }

        if (j < items.size())
            profitBound += (W - totWeight) * ((double)items[j].value / items[j].weight);

        return profitBound;
    }

    // Comparator for sorting items by value-to-weight ratio
    static bool compareItems(Item a, Item b) {
        double r1 = (double)a.value / a.weight;
        double r2 = (double)b.value / b.weight;
        return r1 > r2;
    }

    // Function to solve the knapsack problem using branch and bound
    int solve() {
        sort(items.begin(), items.end(), compareItems);  // Sort items by value-to-weight ratio

        auto cmp = [](Node a, Node b) { return a.bound < b.bound; };
        priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

        Node u, v;
        u.bound = calculateBound(u);
        pq.push(u);

        int maxProfit = 0;

        while (!pq.empty()) {
            u = pq.top();
            pq.pop();

            if (u.bound > maxProfit && u.level != (int)items.size() - 1) {
                v.level = u.level + 1;

                // Take the item
                v.weight = u.weight + items[v.level].weight;
                v.profit = u.profit + items[v.level].value;

                if (v.weight <= W && v.profit > maxProfit)
                    maxProfit = v.profit;

                v.bound = calculateBound(v);
                if (v.bound > maxProfit)
                    pq.push(v);

                // Don't take the item
                v.weight = u.weight;
                v.profit = u.profit;
                v.bound = calculateBound(v);

                if (v.bound > maxProfit)
                    pq.push(v);
            }
        }

        return maxProfit;
    }
};

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> W;

    Knapsack knapsack(W);

    cout << "Enter weight and value for each item:\n";
    for (int i = 0; i < n; i++) {
        int w, v;
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> w;
        cout << "Value: ";
        cin >> v;
        knapsack.addItem(w, v);
    }

    cout << "\nMaximum profit: " << knapsack.solve() << endl;
    return 0;
}
