#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <unordered_set>

bool isValid(const std::deque<long long>& preamble, long long number) {
    std::unordered_set<long long> seen;
    for (long long num : preamble) {
        if (seen.find(number - num) != seen.end()) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}

long long findFirstInvalidNumber(const std::vector<long long>& numbers, size_t preambleSize) {
    std::deque<long long> preamble(numbers.begin(), numbers.begin() + preambleSize);

    for (size_t i = preambleSize; i < numbers.size(); ++i) {
        long long currentNumber = numbers[i];
        if (!isValid(preamble, currentNumber)) {
            return currentNumber;
        }
        preamble.pop_front();
        preamble.push_back(currentNumber);
    }

    return -1; // should not trigger
}

std::vector<long long> readNumbersFromFile(const std::string& filename) {
    std::vector<long long> numbers;
    std::ifstream file(filename);
    long long number;

    while (file >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

int main() {
    std::string filename = "input.txt";
    std::vector<long long> numbers = readNumbersFromFile(filename);
    size_t preambleSize = 25;

    long long invalidNumber = findFirstInvalidNumber(numbers, preambleSize);
    std::cout << "The first invalid number is: " << invalidNumber << std::endl;


    return 0;
}
