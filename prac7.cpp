#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 10;

class FlightGraph {
    string cities[MAX];
    int adjMatrix[MAX][MAX];
    int cityCount;

public:
    FlightGraph() {
        cityCount = 0;
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                adjMatrix[i][j] = 0; // No connection initially
    }

    int getCityIndex(string name) {
        for (int i = 0; i < cityCount; i++) {
            if (cities[i] == name)
                return i;
        }
        // City not found, add new city
        cities[cityCount] = name;
        return cityCount++;
    }

    void addFlight(string from, string to, int cost) {
        int i = getCityIndex(from);
        int j = getCityIndex(to);
        adjMatrix[i][j] = cost;
        //adjMatrix[j][i] = cost; // Assuming flights are bidirectional
    }

    void displayMatrix() {
        cout << "\nFlight Cost Adjacency Matrix:\n    ";
        for (int i = 0; i < cityCount; i++)
            cout << cities[i] << "\t";
        cout << "\n";

        for (int i = 0; i < cityCount; i++) {
            cout << cities[i] << "\t";
            for (int j = 0; j < cityCount; j++) {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }
};

int main() {
    FlightGraph graph;

    // Sample input
    graph.addFlight("Pune", "Mumbai", 120);
    graph.addFlight("Pune", "Delhi", 180);
    graph.addFlight("Mumbai", "Bangalore", 150);
    graph.addFlight("Delhi", "Bangalore", 200);
      graph.addFlight("Mumbai", "Pune", 160);

    graph.displayMatrix();

    return 0;
}

