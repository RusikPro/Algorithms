#include <iostream>
#include <queue>
#include <vector>

#include "../../common/timer.h"

using namespace std;

// BFS solution: Enumerate all possible paths using a queue.
int countPathsBFS(int m, int n) {
    int count = 0;
    // Each element in the queue is a pair (row, column)
    queue<pair<int, int>> q;
    q.push({0, 0});

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        // If we reached the destination (bottom right cell), increment count.
        if (i == m - 1 && j == n - 1) {
            count++;
            // Continue to process other paths.
            continue;
        }

        // If moving down is within the grid, push that cell.
        if (i + 1 < m) {
            q.push({i + 1, j});
        }
        // If moving right is within the grid, push that cell.
        if (j + 1 < n) {
            q.push({i, j + 1});
        }
    }
    return count;
}

void printGrid(const vector<vector<int>>& grid) {
    cout << "\nDP Grid:\n";
    for (const auto& row : grid) {
        for (const auto& value : row) {
            // Adjust width for prettier formatting.
            cout.width(5);
            cout << value << " ";
        }
        cout << "\n";
    }
}

// Dynamic Programming solution: Count paths using a table.
int countPathsDP(int m, int n) {
    // Create a 2D dp array with m rows and n columns.
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;  // Start cell

    // Fill the dp table
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // If we can go down, add the number of ways to reach the current cell.
            if (i + 1 < m) {
                dp[i + 1][j] += dp[i][j];
            }
            // If we can go right, add the number of ways to reach the current cell.
            if (j + 1 < n) {
                dp[i][j + 1] += dp[i][j];
            }
        }
    }

    // Print the DP grid in a pretty way.
    printGrid(dp);

    return dp[m - 1][n - 1];
}

int main() {
    int m, n;
    cout << "Enter grid dimensions (m rows and n columns): ";
    cin >> m >> n;

    int bfsCount = 0;
    {
        Timer<std::milli> timer1("BFS");
        // bfsCount = countPathsBFS(m, n);
    }

    int dpCount = 0;
    {
        Timer<std::milli> timer1("DP");
        dpCount = countPathsDP(m, n);
    }

    cout << "Number of unique paths using BFS: " << bfsCount << "\n";
    cout << "Number of unique paths using DP:  " << dpCount << "\n";

    return 0;
}
