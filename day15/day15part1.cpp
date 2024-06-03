#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::vector<int> starting_numbers = {5, 1, 9, 18, 13, 8, 0};

    std::unordered_map<int, int> last_spoken;
    int turn = 1;
    int last_number = 0;

    for (size_t i = 0; i < starting_numbers.size(); ++i) {
        last_number = starting_numbers[i];
        if (i < starting_numbers.size() - 1) {
            last_spoken[last_number] = turn;
        }
        ++turn;
    }

    while (turn <= 2020) {
        int next_number;
        if (last_spoken.find(last_number) != last_spoken.end()) {
            next_number = turn - 1 - last_spoken[last_number];
        } else {
            next_number = 0;
        }

        last_spoken[last_number] = turn - 1;
        last_number = next_number;
        ++turn;
    }

    std::cout << "The 2020th number spoken is: " << last_number << std::endl;
}
