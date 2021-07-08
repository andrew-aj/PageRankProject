#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class AdjacenyList{
private:
    std::unordered_map<std::string, int> stringConversion;
    int highest = 0;

    std::map<int, std::unordered_set<int>> adjacenyStorage;

    int powerIterations;

    int checkIfExists(const std::string& test);
public:
    AdjacenyList() : powerIterations (0) {}
    AdjacenyList(int p) : powerIterations(p) {}

    void insert(const std::string& from, const std::string& to);
};

int AdjacenyList::checkIfExists(const std::string& test){
    auto it = stringConversion.find(test);
    if(it != stringConversion.end())
        return it->second;
    else{
        stringConversion[test] = highest++;
        return highest-1;
    }
}

void AdjacenyList::insert(const std::string &from, const std::string &to) {
    int fLoc = checkIfExists(from);
    int tLoc = checkIfExists(to);

    adjacenyStorage[fLoc].insert(tLoc);
}

int main() {
    int lines, power_iterations;
    std::string from, to;
    std::cin >> lines;
    std::cin >> power_iterations;

    AdjacenyList list(power_iterations);

    for(int i = 0; i < lines; i++){
        std::cin >> from;
        std::cin >> to;
        list.insert(from, to);
    }

    return 0;
}