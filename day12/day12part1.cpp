#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

struct Instruction {
    char action;
    int value;
};

std::vector<Instruction> readInstructionsFromFile(const std::string& filename) {
    std::vector<Instruction> instructions;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        char action = line[0];
        int value = std::stoi(line.substr(1));
        instructions.push_back({action, value});
    }

    return instructions;
}

void processInstructions(const std::vector<Instruction>& instructions, int& east, int& north, int& direction) {
    for (const auto& instr : instructions) {
        switch (instr.action) {
            case 'N':
                north += instr.value;
                break;
            case 'S':
                north -= instr.value;
                break;
            case 'E':
                east += instr.value;
                break;
            case 'W':
                east -= instr.value;
                break;
            case 'L':
                direction = (direction + 360 - instr.value) % 360;
                break;
            case 'R':
                direction = (direction + instr.value) % 360;
                break;
            case 'F':
                switch (direction) {
                    case 0: // East
                        east += instr.value;
                        break;
                    case 90: // South
                        north -= instr.value;
                        break;
                    case 180: // West
                        east -= instr.value;
                        break;
                    case 270: // North
                        north += instr.value;
                        break;
                }
                break;
        }
    }
}

int main() {
    std::string filename = "input.txt";
    std::vector<Instruction> instructions = readInstructionsFromFile(filename);

    int east = 0, north = 0;
    int direction = 0;

    processInstructions(instructions, east, north, direction);

    int manhattanDistance = std::abs(east) + std::abs(north);
    std::cout << "Manhattan distance: " << manhattanDistance << std::endl;
}
