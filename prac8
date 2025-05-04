#include <iostream>
using namespace std;

// Arrays to hold the probabilities and matrices
float a[20], b[20];              // a = successful search probabilities (p[i]), b = unsuccessful (q[i])
float wt[20][20], c[20][20];     // wt = weight matrix, c = cost matrix
int r[20][20];                   // r = root matrix
int n;                           // Number of keys

// Function to construct the Optimal Binary Search Tree
void con_obst() {
    int i, j, l;

    // Step 1: Initialization for subtrees of length 0 and 1
    for (i = 0; i < n; i++) {
        c[i][i] = 0.0;
        r[i][i] = 0;
        wt[i][i] = b[i];

        // Subtree with one key
        wt[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
        c[i][i + 1] = wt[i][i + 1];
        r[i][i + 1] = i + 1;
    }

    // Initialization for the last node
    c[n][n] = 0.0;
    r[n][n] = 0;
    wt[n][n] = b[n];

    // Step 2: Build the tree for lengths 2 to n
    for (int length = 2; length <= n; length++) {
        for (i = 0; i <= n - length; i++) {
            j = i + length;
            wt[i][j] = wt[i][j - 1] + a[j] + b[j]; // Compute weight
            c[i][j] = 9999;  // Initialize with a high cost

            // Try all roots from i+1 to j and find the minimum cost
            for (l = i + 1; l <= j; l++) {
                float cost = c[i][l - 1] + c[l][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = l;  // Store the root for this subtree
                }
            }

            c[i][j] += wt[i][j]; // Add weight to the minimum cost
        }
    }

    // Output final OBST result
    cout << "\n\nOptimal BST constructed.";
    cout << "\nTotal weight w[0][" << n << "] = " << wt[0][n];
    cout << "\nTotal cost c[0][" << n << "] = " << c[0][n];
    cout << "\nRoot of the OBST r[0][" << n << "] = " << r[0][n] << "\n";
}

// Function to print the structure of the OBST recursively
void print(int l1, int r1) {
    if (l1 >= r1)
        return;

    int root = r[l1][r1];

    // Print left child
    if (r[l1][root - 1] != 0)
        cout << "\nLeft child of " << root << " is: " << r[l1][root - 1];

    // Print right child
    if (r[root][r1] != 0)
        cout << "\nRight child of " << root << " is: " << r[root][r1];

    // Recursive calls for left and right subtrees
    print(l1, root - 1);
    print(root, r1);
}

// Main function to drive the program
int main() {
    int i;

    cout << "\n**** PROGRAM FOR OBST (Optimal Binary Search Tree) ******\n";

    // Input number of keys
    cout << "\nEnter the number of keys (n): ";
    cin >> n;

    // Input successful search probabilities (p[1] to p[n])
    cout << "\nEnter the probabilities for successful search (p[1] to p[" << n << "]):\n";
    for (i = 1; i <= n; i++) {
        cout << "p[" << i << "] = ";
        cin >> a[i];
    }

    // Input unsuccessful search probabilities (q[0] to q[n])
    cout << "\nEnter the probabilities for unsuccessful search (q[0] to q[" << n << "]):\n";
    for (i = 0; i <= n; i++) {
        cout << "q[" << i << "] = ";
        cin >> b[i];
    }

    // Construct OBST and print the structure
    con_obst();
    print(0, n);

    cout << endl;
    return 0;
}

