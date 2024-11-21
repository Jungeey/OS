#include <iostream>
#include <cstring>
using namespace std;

// Function to implement the First Fit algorithm
void firstFit(int blockSizes[], int numBlocks, int processSizes[], int numProcesses) {
    int allocation[numProcesses];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numBlocks; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                allocation[i] = j;
                blockSizes[j] -= processSizes[i];
                break;
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << i + 1 << "\t\t" << processSizes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated\n";
    }
}

// Function to implement the Best Fit algorithm
void bestFit(int blockSizes[], int numBlocks, int processSizes[], int numProcesses) {
    int allocation[numProcesses];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < numProcesses; i++) {
        int bestIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (bestIdx == -1 || blockSizes[j] < blockSizes[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSizes[bestIdx] -= processSizes[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << i + 1 << "\t\t" << processSizes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated\n";
    }
}

// Function to implement the Worst Fit algorithm
void worstFit(int blockSizes[], int numBlocks, int processSizes[], int numProcesses) {
    int allocation[numProcesses];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < numProcesses; i++) {
        int worstIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (worstIdx == -1 || blockSizes[j] > blockSizes[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSizes[worstIdx] -= processSizes[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << i + 1 << "\t\t" << processSizes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated\n";
    }
}

// Main function with menu-driven interface
int main() {
    int numBlocks, numProcesses, choice;

    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;
    int blockSizes[numBlocks], originalBlockSizes[numBlocks];
    cout << "Enter the sizes of memory blocks: ";
    for (int i = 0; i < numBlocks; i++) {
        cin >> blockSizes[i];
        originalBlockSizes[i] = blockSizes[i];
    }

    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    int processSizes[numProcesses];
    cout << "Enter the sizes of processes: ";
    for (int i = 0; i < numProcesses; i++) {
        cin >> processSizes[i];
    }

    do {
        cout << "\nMemory Allocation Strategies:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Restore block sizes for each allocation strategy
        for (int i = 0; i < numBlocks; i++) {
            blockSizes[i] = originalBlockSizes[i];
        }

        switch (choice) {
            case 1:
                firstFit(blockSizes, numBlocks, processSizes, numProcesses);
                break;
            case 2:
                bestFit(blockSizes, numBlocks, processSizes, numProcesses);
                break;
            case 3:
                worstFit(blockSizes, numBlocks, processSizes, numProcesses);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
