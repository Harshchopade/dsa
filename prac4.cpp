#include <iostream>
#include <stack>
#include <cctype> // for isalpha and isdigit

using namespace std;


struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};


bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}


Node* constructTreeFromPrefix(const string& prefix) {
    stack<Node*> st;


    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        Node* node = new Node(c);

        if (isOperator(c)) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }
        st.push(node);
    }

    return st.top(); 
}


void postOrderNonRecursive(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* node = s1.top(); s1.pop();
        s2.push(node);

        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}


void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    cout<<"deleted node :"<<root->data<<endl;
    delete root;

}


int main() {
    string prefix ="+a*bc";
    /*cout<<"enter the size of expression:";
    int s;
    cin>>s;
    
    cout << "Enter each element of the prefix expression:\n";
    for (int i = 0; i < s; i++) {
        char ch;
        cout << "Element " << i + 1 << ": ";
        cin >> ch;
        prefix += ch;
    }*/
    Node* root = constructTreeFromPrefix(prefix);

    cout << "--------------------Post-order traversal (non-recursive):------------ ";
    postOrderNonRecursive(root);

    deleteTree(root);

    return 0;
}

