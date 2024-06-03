#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>

struct Coord {
    int x, y, z;
    bool operator<(const Coord& other) const {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }
};

using ActiveSet = std::set<Coord>;

ActiveSet parseInput(const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    ActiveSet active;

    int y = 0;
    while (std::getline(infile, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '#') {
                active.insert({x, y, 0});
            }
        }
        ++y;
    }

    return active;
}

std::vector<Coord> getNeighbors(const Coord& coord) {
    std::vector<Coord> neighbors;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                if (dx != 0 || dy != 0 || dz != 0) {
                    neighbors.push_back({coord.x + dx, coord.y + dy, coord.z + dz});
                }
            }
        }
    }
    return neighbors;
}

int countActiveNeighbors(const Coord& coord, const ActiveSet& active) {
    int count = 0;
    for (const auto& neighbor : getNeighbors(coord)) {
        if (active.find(neighbor) != active.end()) {
            ++count;
        }
    }
    return count;
}

ActiveSet simulateCycle(const ActiveSet& active) {
    ActiveSet newActive;
    std::set<Coord> candidates;

    for (const auto& coord : active) {
        for (const auto& neighbor : getNeighbors(coord)) {
            candidates.insert(neighbor);
        }
    }

    for (const auto& coord : candidates) {
        int activeNeighbors = countActiveNeighbors(coord, active);
        if (active.find(coord) != active.end()) {
            if (activeNeighbors == 2 || activeNeighbors == 3) {
                newActive.insert(coord);
            }
        } else {
            if (activeNeighbors == 3) {
                newActive.insert(coord);
            }
        }
    }

    return newActive;
}

int main() {
    std::string filename = "input.txt";
    ActiveSet active = parseInput(filename);

    for (int cycle = 0; cycle < 6; ++cycle) {
        active = simulateCycle(active);
    }

    std::cout << "Number of active cubes after 6 cycles: " << active.size() << std::endl;
}
