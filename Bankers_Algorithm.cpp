#include <fstream>
#include <iostream>
#include <vector>

const int NUM_PROCESSES = 5; // Number of processes
const int NUM_RESOURCES = 3; // Number of resources

void calculateNeed(int need[][NUM_RESOURCES], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES]) {
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeed(need, max, allocation);

    bool finish[NUM_PROCESSES] = {false};
    std::vector<int> safeSequence;
    int work[NUM_RESOURCES];
    
    // Initialize work with available resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int completed = 0;
    while (completed < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
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
    for (int i = 0; i < safeSequence.size(); i++) {
        std::cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;

    return true;
}

int main() {
    int available[NUM_RESOURCES];
    int max[NUM_PROCESSES][NUM_RESOURCES];
    int allocation[NUM_PROCESSES][NUM_RESOURCES];

    std::ifstream Input_File("Input_File.txt");
    if (!Input_File) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    // Read allocation matrix
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            Input_File >> allocation[i][j];
        }
    }

    // Read max matrix
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            Input_File >> max[i][j];
        }
    }

    // Read available resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        Input_File >> available[i];
    }

    Input_File.close();

    // Check system safety
    isSafe(available, max, allocation);

    return 0;
}