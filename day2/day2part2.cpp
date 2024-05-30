#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct PasswordPolicy {
    int pos1;
    int pos2;
    char character;
    std::string password;
};

PasswordPolicy parseLine(const std::string& line) {
    PasswordPolicy policy;
    std::string mutableLine = line;
    std::replace(mutableLine.begin(), mutableLine.end(), '-', ' ');
    std::replace(mutableLine.begin(), mutableLine.end(), ':', ' ');

    std::istringstream iss(mutableLine);
    iss >> policy.pos1 >> policy.pos2 >> policy.character >> policy.password;

    return policy;
}

bool isValidPassword(const PasswordPolicy& policy) {
    bool pos1Match = policy.password[policy.pos1 - 1] == policy.character;
    bool pos2Match = policy.password[policy.pos2 - 1] == policy.character;
    return pos1Match != pos2Match;
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
