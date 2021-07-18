#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>

class AdjacencyList {
private:
    //Using a map instead of unordered_map to maintain alphabetical order.
    std::map<std::string, int> stringConversion;

    //Storing this value
    int highest = 0;

    //This is based off the adjacency storage given in Aman lecture slides 8d-8i slide 28.
    std::map<int, std::vector<int>> adjacenyStorage;

    int powerIterations;

    int checkIfExists(const std::string &test);

public:
    AdjacencyList() : powerIterations(0) {}

    AdjacencyList(int p) : powerIterations(p) {}

    void insert(const std::string &from, const std::string &to);

    void PageRank();
};

//Checks if the string is inside the conversion container.
int AdjacencyList::checkIfExists(const std::string &test) {
    //Determines if the string is in the conversion container.
    auto it = stringConversion.find(test);

    //If it is, return the value.
    if (it != stringConversion.end())
        return it->second;
    //If not, add it to the list and return the value.
    else {
        stringConversion[test] = highest++;

        return highest - 1;
    }
}

//Inserts a connection into the adjacency list.
void AdjacencyList::insert(const std::string &from, const std::string &to) {
    //Getting the int conversion for each string.
    int fLoc = checkIfExists(from);
    int tLoc = checkIfExists(to);

    //Pushes the connection onto the adjacency list.
    adjacenyStorage[fLoc].push_back(tLoc);
}

//Calculates the page rank because on the number of iterations given on object construction.
void AdjacencyList::PageRank() {
    std::map<int, double> rank;

    //Using a separate size variable here so I don't call this function n times unlike before.
    auto size = stringConversion.size();

    //Auto generate first power iteration
    for (auto & it : stringConversion) {
        rank[it.second] = 1. / size;
    }

    //Generate the values for p>1
    for (int i = 1; i < powerIterations; i++) {
        std::map<int, double> copy = rank;
        rank.clear();
        for (auto &it : adjacenyStorage) {
            //Originally I got this copy value for each iteration in the for loop below.
            //Getting it once here saves a lot of operations.
            double& cp = copy[it.first];

            //Also originally called this size function for each iteration below.
            size = it.second.size();

            for (auto &second : it.second) {
                //Splitting up the matrix multiplication to do it by columns instead of by rows.
                rank[second] += (1. / size) * cp;
            }
        }
    }

    //Printing the values. Using string conversion as a map ensures alphabetical order.
    for (auto &it : stringConversion) {
        std::cout << std::fixed << std::setprecision(2) << it.first << " " << rank[it.second] << std::endl;
    }
}

//Using the basic template from Aman in the document for the project.
int main() {
    int lines, power_iterations;
    std::string from, to;
    std::cin >> lines;
    std::cin >> power_iterations;

    //Using a constructor so I don't have to set the value later on.
    AdjacencyList list(power_iterations);

    for (int i = 0; i < lines; i++) {
        std::cin >> from;
        std::cin >> to;
        list.insert(from, to);
    }

    list.PageRank();

    return 0;
}