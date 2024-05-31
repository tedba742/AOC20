#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

struct Instruction {
    std::string operation;
    int argument;
};

std::vector<Instruction> readInstructionsFromFile(const std::string& filename) {
    std::vector<Instruction> instructions;
    std::ifstream file(filename);
    std::string operation;
    int argument;

    while (file >> operation >> argument) {
        instructions.push_back({operation, argument});
    }

    return instructions;
}

int executeUntilLoop(const std::vector<Instruction>& instructions) {
    int accumulator = 0;
    int currentIndex = 0;
    std::set<int> executedIndices;

    while (currentIndex < instructions.size()) {
        if (executedIndices.find(currentIndex) != executedIndices.end()) {
            // Infinite loop detected
            return accumulator;
        }

        executedIndices.insert(currentIndex);

        const Instruction& instr = instructions[currentIndex];

        if (instr.operation == "acc") {
            accumulator += instr.argument;
            currentIndex++;
        } else if (instr.operation == "jmp") {
            currentIndex += instr.argument;
        } else if (instr.operation == "nop") {
            currentIndex++;
        }
    }

    return accumulator;
}

int main() {
    std::string filename = "input.txt";
    std::vector<Instruction> instructions = readInstructionsFromFile(filename);
    int accumulator = executeUntilLoop(instructions);
    std::cout << "The value of the accumulator before any instruction is executed a second time is: " << accumulator << std::endl;
    return 0;
}
