#include <string>
#include <fstream>
#include <vector>
#include <iostream>

void readFile(std::vector<std::string>& lines) {
    std::fstream file{"input.txt"};
    std::string line{""};
    while (getline(file, line)) {
        lines.push_back(line);
    }
}

int countTrees(const std::vector<std::string>& lines, int right, int down) {
    int treeCount = 0;
    int x = 0;
    int width = lines[0].size();

    for (int y = 0; y < lines.size(); y += down) {
        if (lines[y][x % width] == '#') {
            treeCount++;
        }
        x += right;
    }
    
    return treeCount;
}

int main() {
    std::vector<std::string> lines{};
    readFile(lines);

    int treeCount = countTrees(lines, 3, 1);
    std::cout << "Number of trees: " << treeCount << std::endl;

}
