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
    std::vector<std::pair<int, int>> slopes = {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    };

    long long result = 1;
    for (const auto& slope : slopes) {
        int treeCount = countTrees(lines, slope.first, slope.second);
        result *= treeCount;
    }

    std::cout << "Product of trees encountered on all slopes: " << result << std::endl;

}
