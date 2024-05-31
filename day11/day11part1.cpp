#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readSeatingAreaFromFile(const string& filename) {
    vector<string> seatingArea;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        seatingArea.push_back(line);
    }
    return seatingArea;
}

bool isOccupied(const vector<string>& area, int row, int col) {
    return row >= 0 && row < area.size() && col >= 0 && col < area[row].size() && area[row][col] == '#';
}

int countAdjacentOccupied(const vector<string>& area, int row, int col) {
    int occupied = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                if (isOccupied(area, row + i, col + j)) {
                    occupied++;
                }
            }
        }
    }
    return occupied;
}

vector<string> applySeatingRules(const vector<string>& area) {
    vector<string> newArea = area;
    for (int i = 0; i < area.size(); ++i) {
        for (int j = 0; j < area[i].size(); ++j) {
            if (area[i][j] == 'L' && countAdjacentOccupied(area, i, j) == 0) {
                newArea[i][j] = '#';
            } else if (area[i][j] == '#' && countAdjacentOccupied(area, i, j) >= 4) {
                newArea[i][j] = 'L';
            }
        }
    }
    return newArea;
}

bool areAreasEqual(const vector<string>& area1, const vector<string>& area2) {
    for (int i = 0; i < area1.size(); ++i) {
        if (area1[i] != area2[i]) {
            return false;
        }
    }
    return true;
}

int countOccupiedSeats(const vector<string>& area) {
    int occupied = 0;
    for (const string& row : area) {
        for (char seat : row) {
            if (seat == '#') {
                occupied++;
            }
        }
    }
    return occupied;
}

int main() {
    string filename = "input.txt";
    vector<string> seatingArea = readSeatingAreaFromFile(filename);

    while (true) {
        vector<string> newArea = applySeatingRules(seatingArea);
        if (areAreasEqual(seatingArea, newArea)) {
            break;
        }
        seatingArea = newArea;
    }

    int occupiedSeats = countOccupiedSeats(seatingArea);
    cout << "Number of occupied seats: " << occupiedSeats << endl;
}
