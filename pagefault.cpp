#include <iostream>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

void optimalPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1; // Initialize frame with -1
    }
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        bool pageFound = false;

        // Check if page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == currentPage) {
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            pageFaults++; // Increment page faults

            bool placed = false;
            // Place the page in an empty frame if available
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    frame[j] = currentPage;
                    placed = true;
                    break;
                }
            }

            if (!placed) { // If no space, replace the farthest page
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

                frame[pageToReplace] = currentPage; // Replace the farthest page
            }
        }

        // Display the current frame
        cout << "Frame: ";
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1)
                cout << " ";
            else
                cout << frame[j] << " ";
        }
        cout << endl;
    }

    cout << "Optimal Page Faults: " << pageFaults << endl;
}

void fifoPageReplacement(int pages[], int n, int capacity) {
    queue<int> fifoQueue;
    map<int, bool> frame;  // Using map instead of unordered_map for compatibility
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        if (frame.find(currentPage) == frame.end()) { // Page not found in frame
            pageFaults++; // Increment page faults

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

        // Display the current frame
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
    map<int, int> pageMap;  // Using map instead of unordered_map for compatibility
    int pageFaults = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        if (pageMap.find(currentPage) == pageMap.end()) { // Page not found in frame
            pageFaults++; // Increment page faults

            if (pageMap.size() == capacity) { // If frame is full, remove LRU
                int lruPage = -1, lruTime = time;
                for (map<int, int>::iterator it = pageMap.begin(); it != pageMap.end(); ++it) {
                    if (it->second < lruTime) {
                        lruTime = it->second;
                        lruPage = it->first;
                    }
                }
                pageMap.erase(lruPage); // Remove the LRU page
            }
            pageMap[currentPage] = time; // Insert new page
        } else {
            pageMap[currentPage] = time; // Update page position
        }

        // Display the current frame
        cout << "Frame: ";
        for (map<int, int>::iterator it = pageMap.begin(); it != pageMap.end(); ++it) {
            cout << it->first << " ";
        }
        cout << endl;

        time++; // Increment time for LRU
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
