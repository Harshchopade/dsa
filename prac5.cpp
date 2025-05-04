#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool isThreaded;
};

class ThreadedBinaryTree {
private:
    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->isThreaded = false;
            return newNode;
        }
        if (data < root->data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);
        return root;
    }

    void createThreads(Node* root, Node*& prev) {
        if (!root) return;

        createThreads(root->left, prev);

        if (prev && prev->right == nullptr) {
            prev->right = root;
            prev->isThreaded = true;
        }
        prev = root;

        createThreads(root->right, prev);
    }

    void inorderTraversal(Node* root) {
        Node* current = root;

        // Go to leftmost node
        while (current && current->left)
            current = current->left;

        while (current) {
            cout << current->data << " ";

            if (current->isThreaded)
                current = current->right;
            else {
                current = current->right;
                while (current && current->left)
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

    void insert(int data) {
        root = insert(root, data);
    }

    void convertToThreadedTree() {
        Node* prev = nullptr;
        createThreads(root, prev);
    }

    void inorderTraversal() {
        cout << "In-order Traversal of Threaded Binary Tree: ";
        inorderTraversal(root);
    }
};

// Driver code
int main() {
    ThreadedBinaryTree OBJ;
    int keys[] = {7,4,5,8,2,9,1};

    for (int key : keys)
        OBJ.insert(key);

    OBJ.convertToThreadedTree();

    OBJ.inorderTraversal();

    return 0;
}

