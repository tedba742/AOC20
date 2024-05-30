#include <string>
#include <fstream>
#include <vector>
#include <iostream>

int getTwentyTwenty(std::vector<int> lines){
    for(auto line : lines){
        for(int i = lines.size() -1; i > 0; i--){
            if(line + lines[i] == 2020){
                return line * lines[i];
            }
        } 
    }
}
int main(){
    std::fstream file{"input.txt"};
    std::string line{""};
    std::vector<int> lines{};
    while(getline(file, line)){
        lines.push_back(std::stoi(line));
    }
    std::cout << getTwentyTwenty(lines) << std::endl;      
}