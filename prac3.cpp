#include <iostream>
#include <queue>
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

// Search for a value
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

// Delete a node
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;

    // If the key to be deleted is smaller than the root's data
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    // If the key to be deleted is greater than the root's data
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    // If the key is the same as the root's data
    else {
        // Node with only one child or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = findMinNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

Node* findMinNode(Node* root) {
    Node* current = root;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// In-order traversal
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Pre-order traversal
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Post-order traversal
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// BFS (Level-Order Traversal)
void bfs(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        cout << node->data << " ";
        q.pop();

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
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

    cout << "Pre-order traversal of original BST: ";
    preorder(root);
    cout << endl;

    cout << "Post-order traversal of original BST: ";
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

    // Step 5: Search for a value
    int key = 40;
    if (search(root, key))
        cout << "Found\n";
    else
        cout << "Not Found\n";

    // Step 6: Delete a node
    cout << "\nDeleting node with value 40...\n";
    root = deleteNode(root, 40);
    cout << "In-order after deletion: ";
    inorder(root);
    cout << endl;

    // Step 7: Perform BFS (Breadth-First Search)
    cout << "\nBFS (Level-Order Traversal): ";
    bfs(root);
    cout << endl;

    // Step 8: Mirror the tree
    mirrorTree(root);
    cout << "\nIn-order traversal after mirroring: ";
    inorder(root);
    cout << endl;

    return 0;
}

