#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> readAdaptersFromFile(const std::string& filename) {
    std::vector<int> adapters;
    std::ifstream file(filename);
    int adapter;

    while (file >> adapter) {
        adapters.push_back(adapter);
    }

    return adapters;
}

int findJoltageDifferencesProduct(std::vector<int>& adapters) {
    adapters.push_back(0);
    
    std::sort(adapters.begin(), adapters.end());
    
    // The built-in adapters is always 3 higher than the highest adapter
    adapters.push_back(adapters.back() + 3);
    
    int diff1 = 0;
    int diff3 = 0;

    for (size_t i = 1; i < adapters.size(); ++i) {
        int difference = adapters[i] - adapters[i - 1];
        if (difference == 1) {
            diff1++;
        } else if (difference == 3) {
            diff3++;
        }
    }

    return diff1 * diff3;
}

int main() {
    std::string filename = "input.txt";
    std::vector<int> adapters = readAdaptersFromFile(filename);
    int result = findJoltageDifferencesProduct(adapters);

    std::cout << "The number of 1-jolt differences multiplied by the number of 3-jolt differences is: " << result << std::endl;
}
