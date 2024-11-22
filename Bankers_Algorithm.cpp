#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class BankerAlgorithm {
private:
    int numProcesses, numResources;
    std::vector<std::vector<int>> maxDemand, allocation, need;
    std::vector<int> availableResources;

    void calculateNeed() {
        need.resize(numProcesses, std::vector<int>(numResources, 0));
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                need[i][j] = maxDemand[i][j] - allocation[i][j];
            }
        }
    }

public:
    BankerAlgorithm(int processes, int resources)
        : numProcesses(processes), numResources(resources) {}

    void initialize(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile) {
            throw std::runtime_error("Error opening file.");
        }

        allocation.resize(numProcesses, std::vector<int>(numResources, 0));
        maxDemand.resize(numProcesses, std::vector<int>(numResources, 0));
        availableResources.resize(numResources, 0);

        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                inputFile >> allocation[i][j];
            }
        }
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                inputFile >> maxDemand[i][j];
            }
        }
        for (int i = 0; i < numResources; i++) {
            inputFile >> availableResources[i];
        }
        inputFile.close();

        calculateNeed();
    }

    bool isSafe() {
        std::vector<bool> finish(numProcesses, false);
        std::vector<int> work = availableResources;
        std::vector<int> safeSequence;

        int completed = 0;
        while (completed < numProcesses) {
            bool found = false;
            for (int i = 0; i < numProcesses; i++) {
                if (!finish[i]) {
                    bool canAllocate = true;
                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }

                    if (canAllocate) {
                        for (int j = 0; j < numResources; j++) {
                            work[j] += allocation[i][j];
                        }
                        safeSequence.push_back(i);
                        finish[i] = true;
                        completed++;
                        found = true;
                    }
                }
            }

            if (!found) {
                std::cout << "System is not in a safe state.\n";
                return false;
            }
        }

        std::cout << "System is in a safe state.\nSafe sequence is: ";
        for (size_t i = 0; i < safeSequence.size(); i++) {
            std::cout << "P" << safeSequence[i];
            if (i < safeSequence.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
        return true;
    }
};

int main() {
    const int NUM_PROCESSES = 5;
    const int NUM_RESOURCES = 3;

    BankerAlgorithm banker(NUM_PROCESSES, NUM_RESOURCES);

    try {
        banker.initialize("Input_File.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    if (!banker.isSafe()) {
        std::cerr << "System is not in a safe state.\n";
        return 1;
    }

    return 0;
}