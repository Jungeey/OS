#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

struct Process {
    int pid;             // Process ID
    int arrivalTime;     // Arrival Time
    int burstTime;       // Burst Time
    int waitingTime;     // Waiting Time
    int turnaroundTime;  // Turnaround Time
    int remainingTime;   // Remaining Time (for SRTN and RR)
};

// Comparator for sorting by arrival time
bool compareArrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

// FCFS Algorithm
void fcfs(Process processes[], int n) {
    sort(processes, processes + n, compareArrivalTime);
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// SJF Algorithm
void sjf(Process processes[], int n) {
    sort(processes, processes + n, compareArrivalTime);
    bool completed[n] = {false};
    int currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int shortestJob = -1;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime &&
                (shortestJob == -1 || processes[i].burstTime < processes[shortestJob].burstTime)) {
                shortestJob = i;
            }
        }

        if (shortestJob == -1) {
            currentTime++;
            continue;
        }

        processes[shortestJob].waitingTime = currentTime - processes[shortestJob].arrivalTime;
        currentTime += processes[shortestJob].burstTime;
        processes[shortestJob].turnaroundTime =
            processes[shortestJob].waitingTime + processes[shortestJob].burstTime;
        completed[shortestJob] = true;
        completedCount++;
    }
}

// SRTN Algorithm
void srtn(Process processes[], int n) {
    sort(processes, processes + n, compareArrivalTime);

    int currentTime = 0, completedCount = 0;
    while (completedCount < n) {
        int shortestRemaining = -1;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 &&
                (shortestRemaining == -1 ||
                 processes[i].remainingTime < processes[shortestRemaining].remainingTime)) {
                shortestRemaining = i;
            }
        }

        if (shortestRemaining == -1) {
            currentTime++;
            continue;
        }

        currentTime++;
        processes[shortestRemaining].remainingTime--;

        if (processes[shortestRemaining].remainingTime == 0) {
            processes[shortestRemaining].turnaroundTime =
                currentTime - processes[shortestRemaining].arrivalTime;
            processes[shortestRemaining].waitingTime =
                processes[shortestRemaining].turnaroundTime - processes[shortestRemaining].burstTime;
            completedCount++;
        }
    }
}

// Round Robin Algorithm
void roundRobin(Process processes[], int n, int quantum) {
    queue<int> readyQueue;
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    readyQueue.push(0);
    int completedCount = 0;
    bool visited[n] = {false};
    visited[0] = true;

    while (!readyQueue.empty()) {
        int index = readyQueue.front();
        readyQueue.pop();

        if (processes[index].remainingTime > quantum) {
            currentTime += quantum;
            processes[index].remainingTime -= quantum;
        } else {
            currentTime += processes[index].remainingTime;
            processes[index].remainingTime = 0;
            processes[index].turnaroundTime = currentTime - processes[index].arrivalTime;
            processes[index].waitingTime =
                processes[index].turnaroundTime - processes[index].burstTime;
            completedCount++;
        }

        // Add new processes to the queue
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(i);
                visited[i] = true;
            }
        }

        if (processes[index].remainingTime > 0) {
            readyQueue.push(index);
        }
    }
}

// Display results
void displayResults(const Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].pid << "\t" << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
             << processes[i].turnaroundTime << "\n";

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

int main() {
    int n, choice, quantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process P" << processes[i].pid << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process P" << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    do {
        cout << "\nScheduling Algorithms:\n";
        cout << "1. FCFS\n2. SJF\n3. SRTN\n4. Round Robin\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fcfs(processes, n);
                displayResults(processes, n);
                break;
            case 2:
                sjf(processes, n);
                displayResults(processes, n);
                break;
            case 3:
                srtn(processes, n);
                displayResults(processes, n);
                break;
            case 4:
                cout << "Enter time quantum: ";
                cin >> quantum;
                roundRobin(processes, n, quantum);
                displayResults(processes, n);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
