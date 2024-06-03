#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<int> playCrabCups(const std::vector<int>& cups, int moves) {
    std::unordered_map<int, int> next;
    int size = cups.size();

    // Initialize the next cup map
    for (int i = 0; i < size; ++i) {
        next[cups[i]] = cups[(i + 1) % size];
    }

    int current = cups[0];

    for (int move = 0; move < moves; ++move) {
        int pick1 = next[current];
        int pick2 = next[pick1];
        int pick3 = next[pick2];
        
        next[current] = next[pick3];

        int destination = current - 1;
        if (destination == 0) destination = size;
        while (destination == pick1 || destination == pick2 || destination == pick3) {
            destination--;
            if (destination == 0) destination = size;
        }

        next[pick3] = next[destination];
        next[destination] = pick1;

        current = next[current];
    }

    // Collect the result starting from cup 1
    std::vector<int> result;
    int cup = next[1];
    for (int i = 1; i < size; ++i) {
        result.push_back(cup);
        cup = next[cup];
    }

    return result;
}

int main() {
    std::vector<int> cups = {8, 7, 1, 3, 6, 9, 4, 5, 2};
    int moves = 100;

    std::vector<int> result = playCrabCups(cups, moves);

    std::cout << "Order after 100 moves: ";
    for (int cup : result) {
        std::cout << cup;
    }
    std::cout << std::endl;
}
