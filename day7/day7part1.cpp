#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <queue>
#include <regex>

using namespace std;

unordered_map<string, vector<string>> buildGraph(const vector<string>& rules) {
    unordered_map<string, vector<string>> graph;
    regex bagPattern("(\\w+ \\w+) bags contain");
    regex containPattern("(\\d+) (\\w+ \\w+) bags?");
    smatch matches;

    for (const auto& rule : rules) {
        stringstream ss(rule);
        string container;
        if (regex_search(rule, matches, bagPattern)) {
            container = matches[1];
        }
        
        string rest = rule.substr(rule.find("contain") + 8);
        stringstream containStream(rest);
        string content;
        
        while (getline(containStream, content, ',')) {
            if (regex_search(content, matches, containPattern)) {
                string containedBag = matches[2];
                graph[containedBag].push_back(container);
            }
        }
    }
    return graph;
}

int countBagsThatCanContainGold(const unordered_map<string, vector<string>>& graph, const string& target) {
    unordered_set<string> visited;
    queue<string> toVisit;
    toVisit.push(target);
    
    while (!toVisit.empty()) {
        string current = toVisit.front();
        toVisit.pop();
        
        if (graph.find(current) != graph.end()) {
            for (const string& neighbor : graph.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    toVisit.push(neighbor);
                }
            }
        }
    }
    return visited.size();
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file rules.txt";
        return 1;
    }

    vector<string> rules;
    string line;
    while (getline(inputFile, line)) {
        rules.push_back(line);
    }
    inputFile.close();

    unordered_map<string, vector<string>> graph = buildGraph(rules);

    string target = "shiny gold";

    int result = countBagsThatCanContainGold(graph, target);

    cout << "Number of bag colors that can eventually contain at least one shiny gold bag: " << result << endl;

}
