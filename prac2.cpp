#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

class HashNode {
public:
    string key;
    string value;

    HashNode(string k, string v) : key(k), value(v) {}
};

class HashTable {
private:
    list<HashNode> table[TABLE_SIZE];

    int hashFunction(string key) {
        int hash = 0;
        for (char ch : key)
            hash = (hash + int(ch)) % TABLE_SIZE;
        return hash;
    }

public:
    // Insert key-value pair
    void insert(string key, string value) {
        int index = hashFunction(key);

        // Check for duplicate key
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value; // Update existing
                cout << "Updated existing key.\n";
                return;
            }
        }

        // Insert new node
        table[index].push_back(HashNode(key, value));
        cout << "Inserted (" << key << ", " << value << ") at index " << index << "\n";
    }

    // Find value by key
    void find(string key) {
        int index = hashFunction(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                cout << "Found: " << node.key << " => " << node.value << "\n";
                return;
            }
        }
        cout << "Key not found.\n";
    }

    // Delete a key
    void remove(string key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                cout << "Deleted key: " << key << "\n";
                return;
            }
        }
        cout << "Key not found to delete.\n";
    }

    // Display hash table
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]: ";
            for (auto& node : table[i])
                cout << "(" << node.key << "," << node.value << ") -> ";
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable dict;
    dict.insert("apple", "fruit");
    dict.insert("car", "vehicle");
    dict.insert("bat", "equipment");
    dict.insert("ball", "toy");

    dict.display();

    dict.find("car");
    dict.find("cat");

    dict.remove("bat");
    dict.remove("dog");

    dict.display();

    return 0;
}

