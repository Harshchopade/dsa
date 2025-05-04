#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int TABLE_SIZE = 10;

struct Client {
    int phone;
    string name;
};

/// --- Chaining --- ///
class HashTableChaining {
    vector<list<Client>> table;

public:
    HashTableChaining() {
        table.resize(TABLE_SIZE);
    }

    void insert(int phone, string name) {
        int index = phone % TABLE_SIZE;
        table[index].push_back({phone, name});
    }

    int search(int phone) {
        int index = phone % TABLE_SIZE;
        int comparisons = 0;
        for (auto& client : table[index]) {
            comparisons++;
            if (client.phone == phone)
                break;
        }
        return comparisons;
    }
};

/// --- Linear Probing --- ///
class HashTableLinear {
    vector<Client> table;
    vector<bool> occupied;

public:
    HashTableLinear() {
        table.resize(TABLE_SIZE, {-1, ""});
        occupied.resize(TABLE_SIZE, false);
    }

    void insert(int phone, string name) {
        int index = phone % TABLE_SIZE;
        while (occupied[index]) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index] = {phone, name};
        occupied[index] = true;
    }

    int search(int phone) {
        int index = phone % TABLE_SIZE;
        int comparisons = 0;

        while (occupied[index]) {
            comparisons++;
            if (table[index].phone == phone)
                break;
            index = (index + 1) % TABLE_SIZE;
        }
        return comparisons;
    }
};

/// --- Main --- ///
int main() {
    vector<Client> clients = {
        {105, "Alice"}, {215, "Bob"}, {325, "Charlie"}, {435, "David"},
        {545, "Eva"}, {655, "Frank"}, {765, "Grace"}
    };

    HashTableChaining chainTable;
    HashTableLinear linearTable;

    // Insert
    for (auto& c : clients) {
        chainTable.insert(c.phone, c.name);
        linearTable.insert(c.phone, c.name);
    }

    // Search and compare
    cout << "Search Comparisons:\n";
    for (auto& c : clients) {
        int compChain = chainTable.search(c.phone);
        int compLinear = linearTable.search(c.phone);

        cout << c.name << " (" << c.phone << ") - Chaining: "
             << compChain << ", Linear: " << compLinear << "\n";
    }

    return 0;
}

