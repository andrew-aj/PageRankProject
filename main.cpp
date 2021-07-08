#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class AdjacencyList {
private:
    std::map<std::string, int> stringConversion;
    int highest = 0;

    std::map<int, std::unordered_set<int>> adjacenyStorage;

    int powerIterations;

    int checkIfExists(const std::string &test);

public:
    AdjacencyList() : powerIterations(0) {}

    AdjacencyList(int p) : powerIterations(p) {}

    void insert(const std::string &from, const std::string &to);

    void PageRank();
};

int AdjacencyList::checkIfExists(const std::string &test) {
    auto it = stringConversion.find(test);
    if (it != stringConversion.end())
        return it->second;
    else {
        stringConversion[test] = highest++;
        return highest - 1;
    }
}

void AdjacencyList::insert(const std::string &from, const std::string &to) {
    int fLoc = checkIfExists(from);
    int tLoc = checkIfExists(to);

    adjacenyStorage[fLoc].insert(tLoc);
}

void AdjacencyList::PageRank() {
    std::map<int, double> iterations;
    //Auto generate first power iteration
    for (auto it = stringConversion.begin(); it != stringConversion.end(); it++) {
        iterations[it->second] = 1. / stringConversion.size();
    }

    for (int i = 1; i < powerIterations; i++) {
        std::map<int, double> copy = iterations;
        iterations.clear();
        for (auto &it : adjacenyStorage) {
            for (auto &second : it.second) {
                iterations[second] += (1. / it.second.size()) * (copy[it.first]);
            }
        }
    }

    for (auto &it : stringConversion) {
        std::cout << std::fixed << std::setprecision(2) << it.first << " " << iterations[it.second] << std::endl;
    }
}

int main() {
    int lines, power_iterations;
    std::string from, to;
    std::cin >> lines;
    std::cin >> power_iterations;

    AdjacencyList list(power_iterations);

    for (int i = 0; i < lines; i++) {
        std::cin >> from;
        std::cin >> to;
        list.insert(from, to);
    }

    list.PageRank();

    return 0;
}