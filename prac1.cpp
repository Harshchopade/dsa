//prac1
#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;
const int EMPTY = -1;

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Insert using Linear Probing
void insertLinear(int table[], int key) {
    int index = hashFunction(key);
    int i = 0;
    while (table[(index + i) % TABLE_SIZE] != EMPTY && i < TABLE_SIZE) {
        i++;
    }
    if (i < TABLE_SIZE)
        table[(index + i) % TABLE_SIZE] = key;
}

// Insert using Quadratic Probing
void insertQuadratic(int table[], int key) {
    int index = hashFunction(key);
    int i = 0;
    while (table[(index + i * i) % TABLE_SIZE] != EMPTY && i < TABLE_SIZE) {
        i++;
    }
    if (i < TABLE_SIZE)
        table[(index + i * i) % TABLE_SIZE] = key;
}

// Search using Linear Probing and count comparisons
int searchLinear(int table[], int key, int &comparisons) {
    int index = hashFunction(key);
    int i = 0;
    comparisons = 0;
    while (table[(index + i) % TABLE_SIZE] != EMPTY && i < TABLE_SIZE) {
        comparisons++;
        if (table[(index + i) % TABLE_SIZE] == key)
            return (index + i) % TABLE_SIZE;
        i++;
    }
    return -1;
}

// Search using Quadratic Probing and count comparisons
int searchQuadratic(int table[], int key, int &comparisons) {
    int index = hashFunction(key);
    int i = 0;
    comparisons = 0;
    while (table[(index + i * i) % TABLE_SIZE] != EMPTY && i < TABLE_SIZE) {
        comparisons++;
        if (table[(index + i * i) % TABLE_SIZE] == key)
            return (index + i * i) % TABLE_SIZE;
        i++;
    }
    return -1;
}

void printTable(int table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] == EMPTY)
            cout << i << ": " << "EMPTY" << endl;
        else
            cout << i << ": " << table[i] << endl;
    }
}

int main() {
    int linearTable[TABLE_SIZE], quadraticTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        linearTable[i] = EMPTY;
        quadraticTable[i] = EMPTY;
    }

    // Sample data (telephone numbers or keys)
    int data[] = {23, 43, 13, 27, 37};
    int n = sizeof(data) / sizeof(data[0]);

    // Insert into both tables
    for (int i = 0; i < n; i++) {
        insertLinear(linearTable, data[i]);
        insertQuadratic(quadraticTable, data[i]);
    }

    // Print tables
    cout << "Linear Probing Hash Table:\n";
    printTable(linearTable);
    cout << "\nQuadratic Probing Hash Table:\n";
    printTable(quadraticTable);

    // Search and compare
    cout << "\nSearch comparison:\n";
    for (int i = 0; i < n; i++) {
        int comparisonsLinear, comparisonsQuadratic;
        searchLinear(linearTable, data[i], comparisonsLinear);
        searchQuadratic(quadraticTable, data[i], comparisonsQuadratic);
        cout << "Key: " << data[i]
             << " | Linear Comparisons: " << comparisonsLinear
             << " | Quadratic Comparisons: " << comparisonsQuadratic << endl;
    }

    return 0;
}
