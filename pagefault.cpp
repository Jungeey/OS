#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

void optimalPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    fill(frame, frame + capacity, -1);
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        bool pageFound = false;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == currentPage) {
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            pageFaults++;

            bool placed = false;
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    frame[j] = currentPage;
                    placed = true;
                    break;
                }
            }

            if (!placed) {
                int farthestIndex = -1, pageToReplace = -1;

                for (int j = 0; j < capacity; j++) {
                    bool foundInFuture = false;
                    for (int k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            foundInFuture = true;
                            farthestIndex = max(farthestIndex, k);
                            break;
                        }
                    }

                    if (!foundInFuture) {
                        pageToReplace = j;
                        break;
                    }
                }

                frame[pageToReplace] = currentPage;
            }
        }

        cout << "Frame: ";
        for (int j = 0; j < capacity; j++) {
            cout << (frame[j] == -1 ? " " : to_string(frame[j])) << " ";
        }
        cout << endl;
    }

    cout << "Optimal Page Faults: " << pageFaults << endl;
}


void fifoPageReplacement(int pages[], int n, int capacity) {
    queue<int> fifoQueue;
    unordered_map<int, bool> frame;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        if (frame.find(currentPage) == frame.end()) {
            pageFaults++;

            if (fifoQueue.size() < capacity) {
                fifoQueue.push(currentPage);
                frame[currentPage] = true;
            } else {
                int pageToReplace = fifoQueue.front();
                fifoQueue.pop();
                frame.erase(pageToReplace);
                fifoQueue.push(currentPage);
                frame[currentPage] = true;
            }
        }

        cout << "Frame: ";
        queue<int> tempQueue = fifoQueue;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
    }

    cout << "FIFO Page Faults: " << pageFaults << endl;
}

void lruPageReplacement(int pages[], int n, int capacity) {
    unordered_map<int, int> pageMap;
    int pageFaults = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        if (pageMap.find(currentPage) == pageMap.end()) {
            pageFaults++;

            if (pageMap.size() == capacity) {
                int lruPage = -1, lruTime = time;
                for (auto &entry : pageMap) {
                    if (entry.second < lruTime) {
                        lruTime = entry.second;
                        lruPage = entry.first;
                    }
                }
                pageMap.erase(lruPage);
            }
            pageMap[currentPage] = time;
        } else {
            pageMap[currentPage] = time;
        }

        cout << "Frame: ";
        for (auto &entry : pageMap) {
            cout << entry.first << " ";
        }
        cout << endl;

        time++;
    }

    cout << "LRU Page Faults: " << pageFaults << endl;
}

int main() {
    int choice;
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2}; 
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity;

    cout << "Enter the number of frames: ";
    cin >> capacity;

    do {
        cout << "\nMenu:\n";
        cout << "1. Optimal Page Replacement\n";
        cout << "2. FIFO Page Replacement\n";
        cout << "3. LRU Page Replacement\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                optimalPageReplacement(pages, n, capacity);
                break;
            case 2:
                fifoPageReplacement(pages, n, capacity);
                break;
            case 3:
                lruPageReplacement(pages, n, capacity);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
