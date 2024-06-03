#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

pair<int, int> getTileCoordinates(const string& directions) {
    int x = 0, y = 0;
    for (size_t i = 0; i < directions.size(); ++i) {
        if (directions[i] == 'e') {
            x += 2;
        } else if (directions[i] == 'w') {
            x -= 2;
        } else if (directions[i] == 'n') {
            if (directions[++i] == 'e') {
                x += 1;
                y += 1;
            } else {
                x -= 1;
                y += 1;
            }
        } else if (directions[i] == 's') {
            if (directions[++i] == 'e') {
                x += 1;
                y -= 1;
            } else {
                x -= 1;
                y -= 1;
            }
        }
    }
    return {x, y};
}

int main() {
    ifstream inputFile("input.txt");
    unordered_set<string> blackTiles;
    string directions;

    // Reading the input and flipping tiles
    while (getline(inputFile, directions)) {
        pair<int, int> coords = getTileCoordinates(directions);
        string tileKey = to_string(coords.first) + "," + to_string(coords.second);
        if (blackTiles.find(tileKey) != blackTiles.end()) {
            blackTiles.erase(tileKey);
        } else {
            blackTiles.insert(tileKey);
        }
    }

    inputFile.close();

    cout << "Number of black tiles: " << blackTiles.size() << endl;
}
