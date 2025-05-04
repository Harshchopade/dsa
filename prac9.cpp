#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key, meaning;
    Node* left;
    Node* right;
    int height;
    Node(string k, string m) {
        key = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* node) {
    return node ? node->height : 0;
}

int balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node* insert(Node* node, string key, string meaning) {
    if (!node) return new Node(key, meaning);

    if (key < node->key)
        node->left = insert(node->left, key, meaning);
    else if (key > node->key)
        node->right = insert(node->right, key, meaning);
    else {
        cout << "Duplicate keyword not allowed.\n";
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, string key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp)
                root = nullptr;
            else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = balanceFactor(root);

    // Balance rotations
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* update(Node* root, string key, string newMeaning) {
    Node* current = root;
    while (current) {
        if (key == current->key) {
            current->meaning = newMeaning;
            cout << "Updated successfully.\n";
            return root;
        } else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    cout << "Keyword not found.\n";
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " : " << root->meaning << endl;
        inorder(root->right);
    }
}

void reverseInorder(Node* root) {
    if (root) {
        reverseInorder(root->right);
        cout << root->key << " : " << root->meaning << endl;
        reverseInorder(root->left);
    }
}

int search(Node* root, string key, int& comparisons) {
    comparisons = 0;
    while (root) {
        comparisons++;
        if (key == root->key) {
            cout << "Found: " << root->meaning << endl;
            return comparisons;
        } else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    cout << "Keyword not found.\n";
    return comparisons;
}

int treeHeight(Node* root) {
    return height(root);
}

int main() {
    Node* root = nullptr;
    int choice, comps;
    string key, meaning;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Update\n4. Display Asc\n5. Display Desc\n6. Search\n7. Max Comparisons\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter keyword: "; cin >> key;
            cout << "Enter meaning: "; cin.ignore(); getline(cin, meaning);
            root = insert(root, key, meaning);
            break;
        case 2:
            cout << "Enter keyword to delete: "; cin >> key;
            root = deleteNode(root, key);
            break;
        case 3:
            cout << "Enter keyword to update: "; cin >> key;
            cout << "Enter new meaning: "; cin.ignore(); getline(cin, meaning);
            root = update(root, key, meaning);
            break;
        case 4:
            inorder(root);
            break;
        case 5:
            reverseInorder(root);
            break;
        case 6:
            cout << "Enter keyword to search: "; cin >> key;
            comps = 0;
            comps = search(root, key, comps);
            cout << "Comparisons made: " << comps << endl;
            break;
        case 7:
            cout << "Maximum comparisons = height of tree = " << treeHeight(root) << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}

