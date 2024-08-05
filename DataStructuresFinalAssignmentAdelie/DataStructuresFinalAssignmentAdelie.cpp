#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <limits>
#include <sstream>

using namespace std;
typedef map<char, map<char, int>> Graph;

Graph ReadGraph(const string& filename) {
    ifstream file(filename);
    Graph graph;
    string line;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        char nodeA, nodeB;
        double weight;
        ss >> nodeA >> nodeB >> weight;

        graph[nodeA][nodeB] = weight;
        graph[nodeB][nodeA] = weight; 
    }

    return graph;
}

void UltimateCalculationFriendNearestNodeRouteYay(const Graph& graph, char start, int freakMode, char freakTarget) {
    map<char, double> distances;
    map<char, char> previous;
    set<char> nodes;
    int nearests[4] = { 9001, 9001, 9001, 9001 };

    for (const auto& pair : graph) {
        distances[pair.first] = numeric_limits<double>::infinity();
        previous[pair.first] = '\0';
        nodes.insert(pair.first);
    }

    distances[start] = 0;

    auto compare = [&distances](char lhs, char rhs) {
        return distances[lhs] > distances[rhs];
        };

    priority_queue<char, vector<char>, decltype(compare)> minHeapQueue(compare);
    minHeapQueue.push(start);

    while (!minHeapQueue.empty()) {
        char nodeA = minHeapQueue.top();
        minHeapQueue.pop();

        if (distances[nodeA] == numeric_limits<double>::infinity()) break;

        if (freakMode!=1) {
            switch (nodeA) {
            case 'H':
                if (freakMode == 2) {
                    cout << "It's 'H', congratulation! Welcome to H Chargingstation please PLUG In your laptop and Have a nice drive!!!!!"
                        << "\n By the way. nice to meet you and the distance you took to get here is: " << distances[nodeA] << "\n";
                    return;
                }
                else {
                    if (nearests[0] == 9001) { nearests[0] = distances[nodeA]; }
                }
                break;
            case 'K':

                if (freakMode == 2) {
                    cout << "Ya it's K Time my friend. 'K' is the name of the location of the station that YOU have arrived to."
                        << "\n By the way. nice to meet you and the distance you took to get here is: " << distances[nodeA] << "\n";
                    return;
                }
                else {
                    if (nearests[1] == 9001) { nearests[1] = distances[nodeA]; }
                }
                break;
            case 'Q':
                if (freakMode == 2) {
                    cout << "Q Q Q Q Q Q Q Q Q Q Q Q Q Q it's 'Q' welcome to Q Lightning Electric Friend House."
                        << "\n By the way. nice to meet you and the distance you took to get here is: " << distances[nodeA] << "\n";
                    return;
                }
                else {
                    if (nearests[2] == 9001) { nearests[2] = distances[nodeA]; }
                }
                break;
            case 'T':

                if (freakMode == 2) {
                    cout << "The true winner after all is 'T' . you are T best. You are T-riffic !!! Yipee!!"
                        << "\n By the way. nice to meet you and the distance you took to get here is: " << distances[nodeA] << "\n";
                    return;
                }
                else {
                    if (nearests[3] == 9001) { nearests[3] = distances[nodeA]; }
                }
                break;
            default:
                break;
            }
        }
        else {
            if (nodeA == freakTarget) {
                cout << "You have FOUND YOUR TARGET!!!! THe node " << nodeA << " IS WITHINR EACH. THE CLOSEST ROUTE FROM YOUR ORIGINAL NODE IS A DISTANCE OF: " << distances[nodeA];
                return;
            }
        }


        for (const auto& neighbor : graph.at(nodeA)) {
            char nodeB = neighbor.first;
            double weight = neighbor.second;
            double alt = distances[nodeA] + weight;
            if (alt < distances[nodeB]) {
                distances[nodeB] = alt;
                previous[nodeB] = nodeA;
                minHeapQueue.push(nodeB);
            }
        }
    }
    char nearestName = 'H';
    int nearest = nearests[0];
    cout << "\n The charging station at: " << 'H' << " has a distance of: " << nearests[0];
    cout << "\n The charging station at: " << 'J' << " has a distance of: " << nearests[1];
    cout << "\n The charging station at: " << 'Q' << " has a distance of: " << nearests[2];
    cout << "\n The charging station at: " << 'T' << " has a distance of: " << nearests[3];
    for (int i = 0; i < 2; i++) {
        if (nearest > nearests[i + 1]) {
            nearest = nearests[i + 1];
            switch(i+1) {
            case 1:
                nearestName = 'K';
                break;
            case 2:
                nearestName = 'Q';
                break;
            case 3: 
                nearestName = 'T';
                break;
            default:
                break;
            }
        }
    }
    cout << "\nThe nearest charging station is " << nearestName << " which's route has a distance of " << nearest<<"\n";

}

int main() {
    
    string filename = "nodes.txt";
    Graph graph = ReadGraph(filename);
    char decision = ' ';
    vector<char> stations = { 'H', 'K', 'Q', 'T' };
    char nodeSelect = ' ';
    char targetSelect = ' ';
    int freakMode = 0;
    cout << "Please enter the node you would like to start at: ";
    cin >> nodeSelect;
    
    
    cout << "\nWould you like to use the default option? \n1. Search for all charging stations and determine the nearest\n2. Set custom node\n3. Determine the nearest charging station and STOP!\nInput either 1 or 2 or 3: ";
    cin >> decision;
    switch(decision) {
    case '1':
        cout << "\nVery well you shall have your wish.";
        break;
    case '2':
        cout << "\nI see. Clever dog. Now then. Please allow me to ask you something else. What exactly would you like to find. Which node please enter here: ";
        cin >> targetSelect;
        freakMode = 1;
        break;
    case '3':
        cout << "\nVery well you shall have your wish.";
        freakMode = 2;
        break;
    default:
        cout << "MISINPUT!!!! YOU DIDN'T INPUT ONE OF THE EXPECTED ANSWERS!!!!!!!";
        break;
    }
    UltimateCalculationFriendNearestNodeRouteYay(graph, nodeSelect, freakMode, targetSelect);
    if (freakMode == 0) {
    }
    

    

    

    return 0;
}
