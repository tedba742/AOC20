#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

std::vector<std::unordered_map<std::string, std::string>> readPassports(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, passportData;
    std::vector<std::unordered_map<std::string, std::string>> passports;
    std::unordered_map<std::string, std::string> passport;

    while (getline(file, line)) {
        if (line.empty()) {
            passports.push_back(passport);
            passport.clear();
        } else {
            std::istringstream iss(line);
            std::string keyValue;
            while (iss >> keyValue) {
                auto delimiterPos = keyValue.find(':');
                auto key = keyValue.substr(0, delimiterPos);
                auto value = keyValue.substr(delimiterPos + 1);
                passport[key] = value;
            }
        }
    }

    if (!passport.empty()) {
        passports.push_back(passport);
    }

    return passports;
}

bool isValidPassport(const std::unordered_map<std::string, std::string>& passport) {
    static const std::unordered_set<std::string> requiredFields = {
        "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
    };

    for (const auto& field : requiredFields) {
        if (passport.find(field) == passport.end()) {
            return false;
        }
    }

    return true;
}

int main() {
    const std::string filename = "input.txt";
    const auto passports = readPassports(filename);
    int validPassportCount = 0;

    for (const auto& passport : passports) {
        if (isValidPassport(passport)) {
            validPassportCount++;
        }
    }

    std::cout << "Number of valid passports: " << validPassportCount << std::endl;

}
