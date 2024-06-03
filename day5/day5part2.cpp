#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

std::vector<std::string> readBoardingPasses(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> boardingPasses;

    while (getline(file, line)) {
        boardingPasses.push_back(line);
    }

    return boardingPasses;
}

int getSeatID(const std::string& boardingPass) {
    int row = 0;
    int col = 0;

    for (int i = 0; i < 7; ++i) {
        if (boardingPass[i] == 'B') {
            row = row * 2 + 1;
        } else {
            row = row * 2;
        }
    }

    for (int i = 7; i < 10; ++i) {
        if (boardingPass[i] == 'R') {
            col = col * 2 + 1;
        } else {
            col = col * 2;
        }
    }

    return row * 8 + col;
}

int findMissingSeatID(const std::vector<int>& seatIDs) {
    std::unordered_set<int> seatSet(seatIDs.begin(), seatIDs.end());

    for (int seatID : seatIDs) {
        if (seatSet.find(seatID + 1) == seatSet.end() && seatSet.find(seatID + 2) != seatSet.end()) {
            return seatID + 1;
        }
    }

    return -1;
}

int main() {
    const std::string filename = "input.txt";
    const auto boardingPasses = readBoardingPasses(filename);
    std::vector<int> seatIDs;

    for (const auto& boardingPass : boardingPasses) {
        seatIDs.push_back(getSeatID(boardingPass));
    }

    std::sort(seatIDs.begin(), seatIDs.end());

    int missingSeatID = findMissingSeatID(seatIDs);

    std::cout << "Missing seat ID: " << missingSeatID << std::endl;
}
