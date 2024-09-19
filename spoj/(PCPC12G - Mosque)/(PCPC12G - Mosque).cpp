#include <bits/stdc++.h>
using namespace std;

#define MAX_M 20010  // Maximum possible value for 'total'
#define MAX_N 105    // Maximum number of items
#define INF (1 << 28) // A large value representing infinity

int dp[MAX_N][MAX_M][3]; // DP table to store the minimum cost results
int fl[MAX_N][MAX_M][3]; // Flag table to track whether a state has been computed
int a[MAX_N], b[MAX_N];  // Arrays to store item values
int case_number = 1;     // Variable to keep track of the test case number
int item_count, capacity, total; // Variables to store input values

// Function to calculate the minimum cost using dynamic programming
int calculate(int index, int remaining, int force_select) {
    if (remaining <= 0) return 0; // If no remaining capacity, return 0 (base case)
    if (index > item_count) return INF; // If out of bounds, return a large value (infinity)

// to not write the parameters a lot
#define params [index][remaining][force_select]

    auto &ret = dp params;
    // Check if this state has already been computed
    if (fl params == case_number) return ret;

    // Mark this state as computed for this case
    fl params = case_number;

    // If forced to select the current item
    if (force_select)
        return ret = calculate(index + 1, remaining - a[index], 0) + b[index];

    // Otherwise, choose the minimum of either selecting or skipping the current item
    ret = min(
            calculate(index + 1, remaining - a[index], 0) + b[index], // Select the current item
            calculate(index + 1, remaining, 1)                                // Skip the current item
             );
    return ret;
}

signed main()
{
    while (scanf("%d %d %d", &item_count, &capacity, &total) == 3) 
    {
    
        for (int i = 1; i <= item_count; i++) 
        {
            int item_weight;
            scanf("%d", &item_weight);
            b[i] = item_weight;  // Store the original item weight
            a[i] = max(0, capacity - (2 * item_weight)); // Calculate the adjusted value and ensure non-negative
        }
    
    
        // Output the result of the calculation
        printf("%d\n", calculate(1, total, 0));
        case_number++; // Increment the case number
    }
    
}