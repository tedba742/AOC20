#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

int main() {
    const std::string filename = "input.txt";
    const auto boardingPasses = readBoardingPasses(filename);
    int highestSeatID = 0;

    for (const auto& boardingPass : boardingPasses) {
        int seatID = getSeatID(boardingPass);
        if (seatID > highestSeatID) {
            highestSeatID = seatID;
        }
    }

    std::cout << "Highest seat ID: " << highestSeatID << std::endl;

}
