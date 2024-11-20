#include <iostream>
using namespace std;

int main() {
    int num_processes = 5, num_resources = 4;
    
    int available[] = {1, 5, 2, 0};  // Available resources
    int max[5][4] = {                // Maximum resources needed for each process
        {0, 2, 1, 0},
        {1, 6, 5, 2},
        {2, 3, 6, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };
    
    int allocation[5][4] = {         
        {0, 1, 1, 0},
        {1, 2, 3, 1},
        {1, 3, 6, 5},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };
    
    int need[5][4];               
    
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    cout << "Need Matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    
    int work[4];              
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i]; 
    }
    
    int finish[5] = {0};     
    int safe_sequence[5];      
    int num_safe = 0;        
    
    while (num_safe < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe_sequence[num_safe++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        
        if (!found) {
            cout << "Unsafe state!\n";
            return 1;
        }
    }
    
    cout << "Safe sequence: ";
    for (int i = 0; i < num_processes; i++) {
        cout << "P" << safe_sequence[i] << " ";
    }
    cout << endl;

    return 0;
}
