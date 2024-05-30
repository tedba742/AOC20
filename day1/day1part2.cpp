#include <string>
#include <fstream>
#include <vector>
#include <iostream>

long long getTwentyTwenty(const std::vector<int>& lines) {
    int n = lines.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (lines[i] + lines[j] + lines[k] == 2020) {
                    return static_cast<long long>(lines[i]) * lines[j] * lines[k];
                }
            }
        }
    }
    return -1;
}

int main() {
    std::fstream file{"input.txt"};
    std::string line{""};
    std::vector<int> lines{};
    while (getline(file, line)) {
        lines.push_back(std::stoi(line));
    }
    std::cout << getTwentyTwenty(lines);
}
