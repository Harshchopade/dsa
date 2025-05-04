#include <iostream>
using namespace std;

// Each node stores a number and links to left and right nodes.
// We also track if the left and right pointers are actual child links or just shortcuts (threads).
struct Node {
    int data;
    Node *left, *right;
    bool isLeftThreaded;
    bool isRightThreaded;
};

class ThreadedBinaryTree {
private:
    // This function adds a new number into the tree like a normal Binary Search Tree
    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->isLeftThreaded = false;
            newNode->isRightThreaded = false;
            return newNode;
        }
        if (data < root->data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);
        return root;
    }

    // This function sets up the threads to make in-order traversal easier
    void createThreads(Node* root, Node*& prev) {
        if (!root) return;

        // First, deal with the left side of the tree
        createThreads(root->left, prev);

        // If the previous node has no right child, make its right a shortcut to current node
        if (prev) {
            if (prev->right == nullptr) {
                prev->right = root;
                prev->isRightThreaded = true;
            }

            // If the current node has no left child, link it back to previous node
            if (root->left == nullptr) {
                root->left = prev;
                root->isLeftThreaded = true;
            }
        }

        // Now this node becomes the previous one for the next call
        prev = root;

        // Finally, deal with the right side of the tree
        createThreads(root->right, prev);
    }

    // This prints all the numbers in order using the threads (no recursion or stack)
    void inorderTraversal(Node* root) {
        Node* current = root;

        // Start from the smallest value (go as left as possible)
        while (current && !current->isLeftThreaded && current->left)
            current = current->left;

        while (current) {
            cout << current->data << " ";

            // If right is just a shortcut, go directly
            if (current->isRightThreaded)
                current = current->right;
            else {
                // Otherwise, go to the leftmost node of the right subtree
                current = current->right;
                while (current && !current->isLeftThreaded && current->left)
                    current = current->left;
            }
        }
        cout << endl;
    }

public:
    Node* root;

    ThreadedBinaryTree() {
        root = nullptr;
    }

    // Public function to add a number into the tree
    void insert(int data) {
        root = insert(root, data);
    }

    // Public function to convert the regular tree into a threaded one
    void convertToThreadedTree() {
        Node* prev = nullptr;
        createThreads(root, prev);
    }

    // Public function to print the tree in sorted order using threads
    void inorderTraversal() {
        cout << "In-order Traversal of Fully Threaded Binary Tree: ";
        inorderTraversal(root);
    }
};

// Starting point of the program
int main() {
    ThreadedBinaryTree OBJ;
    int keys[] = {7, 4, 5, 8, 2, 9, 1};

    for (int key : keys)
        OBJ.insert(key);

    OBJ.convertToThreadedTree();
    OBJ.inorderTraversal();

    return 0;
}

