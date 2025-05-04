#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Insert a new node into BST
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

// Find longest path (height)
int longestPath(Node* root) {
    if (!root) return 0;
    int leftDepth = longestPath(root->left);
    int rightDepth = longestPath(root->right);
    return max(leftDepth, rightDepth) + 1;
}

// Find minimum value in BST
int findMin(Node* root) {
    if (!root) return -1;
    while (root->left) {
        root = root->left;
    }
    return root->data;
}

// Mirror the BST
void mirrorTree(Node* root) {
    if (!root) return;
    swap(root->left, root->right);
    mirrorTree(root->left);
    mirrorTree(root->right);
}

bool search(Node* root, int key) {
    if (root == nullptr)
        return false;
    
    if (key == root->data)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// In-order traversal
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main() {
    Node* root = nullptr;
    int initialValues[] = {50, 30, 70, 20, 40, 60, 80}; // You can change this
    int n = sizeof(initialValues) / sizeof(initialValues[0]);

    // Step 1: Construct the BST
    for (int i = 0; i < n; ++i)
        root = insert(root, initialValues[i]);

    cout << "In-order traversal of original BST: ";
    inorder(root);
    cout << endl;
    cout << "preorderr traversal of original BST: ";
    preorder(root);
    cout << endl;
// 
    cout << "postordertraversal of original BST: ";
    postorder(root);
    cout << endl;
    // Step 2: Insert a new node
    cout << "\nInserting 25 into the BST...\n";
    root = insert(root, 25);

    cout << "In-order after insertion: ";
    inorder(root);
    cout << endl;

    // Step 3: Longest path
    cout << "\nLongest path (height): " << longestPath(root) << endl;

    // Step 4: Minimum value
    cout << "Minimum value in the BST: " << findMin(root) << endl;


	    // Step 6: Search for a value
int key = 40;
if (search(root, key))
    cout << "Found\n";
else
    cout << "Not Found\n";

    // Step 5: Mirror the tree
    mirrorTree(root);
    cout << "\nIn-order traversal after mirroring: ";
    inorder(root);
    cout << endl;



    return 0;
}

