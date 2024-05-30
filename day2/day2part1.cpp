#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct PasswordPolicy {
    int min;
    int max;
    char character;
    std::string password;
};

PasswordPolicy parseLine(const std::string& line) {
    PasswordPolicy policy;
    std::string mutableLine = line;
    std::replace(mutableLine.begin(), mutableLine.end(), '-', ' ');
    std::replace(mutableLine.begin(), mutableLine.end(), ':', ' ');

    std::istringstream iss(mutableLine);
    iss >> policy.min >> policy.max >> policy.character >> policy.password;

    return policy;
}

bool isValidPassword(const PasswordPolicy& policy) {
    int count = std::count(policy.password.begin(), policy.password.end(), policy.character);
    return count >= policy.min && count <= policy.max;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<PasswordPolicy> policies;

    while (std::getline(inputFile, line)) {
        policies.push_back(parseLine(line));
    }

    int validPasswordCount = 0;
    for (const auto& policy : policies) {
        if (isValidPassword(policy)) {
            validPasswordCount++;
        }
    }

    std::cout << "Number of valid passwords: " << validPasswordCount << std::endl;
}
