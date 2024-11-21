#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

#define MAX 100

void fcfs(int arr[], int size, int head) {
    int seek_count = 0;
    int distance;
    cout << "\nSeek Sequence: " << head;
    for (int i = 0; i < size; i++) {
        distance = abs(arr[i] - head);
        seek_count += distance;
        head = arr[i];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Operations: " << seek_count << endl;
}

void sstf(int arr[], int size, int head) {
    int seek_count = 0, distance;
    int visited[MAX] = {0};

    cout << "\nSeek Sequence: " << head;
    for (int i = 0; i < size; i++) {
        int min_distance = INT_MAX, index = -1;
        for (int j = 0; j < size; j++) {
            if (!visited[j] && abs(arr[j] - head) < min_distance) {
                min_distance = abs(arr[j] - head);
                index = j;
            }
        }
        visited[index] = 1;
        seek_count += min_distance;
        head = arr[index];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Operations: " << seek_count << endl;
}

void scan(int arr[], int size, int head, int disk_size) {
    int seek_count = 0, distance;
    int left[MAX], right[MAX], l = 0, r = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[l++] = arr[i];
        else
            right[r++] = arr[i];
    }
    sort(left, left + l);
    sort(right, right + r);

    cout << "\nSeek Sequence: " << head;
    for (int i = 0; i < r; i++) {
        distance = abs(right[i] - head);
        seek_count += distance;
        head = right[i];
        cout << " -> " << head;
    }
    if (head < disk_size - 1) {
        seek_count += abs(disk_size - 1 - head);
        head = disk_size - 1;
        cout << " -> " << head;
    }
    for (int i = l - 1; i >= 0; i--) {
        distance = abs(left[i] - head);
        seek_count += distance;
        head = left[i];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Operations: " << seek_count << endl;
}

void cscan(int arr[], int size, int head, int disk_size) {
    int seek_count = 0, distance;
    int left[MAX], right[MAX], l = 0, r = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[l++] = arr[i];
        else
            right[r++] = arr[i];
    }
    sort(left, left + l);
    sort(right, right + r);

    cout << "\nSeek Sequence: " << head;
    for (int i = 0; i < r; i++) {
        distance = abs(right[i] - head);
        seek_count += distance;
        head = right[i];
        cout << " -> " << head;
    }
    if (head < disk_size - 1) {
        seek_count += abs(disk_size - 1 - head);
        head = disk_size - 1;
        cout << " -> " << head;
    }
    seek_count += abs(head - 0);
    head = 0;
    cout << " -> " << head;
    for (int i = 0; i < l; i++) {
        distance = abs(left[i] - head);
        seek_count += distance;
        head = left[i];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Operations: " << seek_count << endl;
}

void look(int arr[], int size, int head) {
    int seek_count = 0, distance;
    int left[MAX], right[MAX], l = 0, r = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[l++] = arr[i];
        else
            right[r++] = arr[i];
    }
    sort(left, left + l);
    sort(right, right + r);

    cout << "\nSeek Sequence: " << head;
    for (int i = 0; i < r; i++) {
        distance = abs(right[i] - head);
        seek_count += distance;
        head = right[i];
        cout << " -> " << head;
    }
    for (int i = l - 1; i >= 0; i--) {
        distance = abs(left[i] - head);
        seek_count += distance;
        head = left[i];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Operations: " << seek_count << endl;
}

void clook(int arr[], int size, int head) {
    int seek_count = 0, distance;
    int left[MAX], right[MAX], l = 0, r = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[l++] = arr[i];
        else
            right[r++] = arr[i];
    }
    sort(left, left + l);
    sort(right, right + r);

    cout << "\nSeek Sequence: " << head;
    for (int i = 0; i < r; i++) {
        distance = abs(right[i] - head);
        seek_count += distance;
        head = right[i];
        cout << " -> " << head;
    }
    seek_count += abs(head - left[0]);
    head = left[0];
    cout << " -> " << head;
    for (int i = 1; i < l; i++) {
        distance = abs(left[i] - head);
        seek_count += distance;
        head = left[i];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Operations: " << seek_count << endl;
}

int main() {
    int choice, head, size, disk_size;
    int arr[MAX];

    cout << "Enter the number of requests: ";
    cin >> size;
    cout << "Enter the request sequence: ";
    for (int i = 0; i < size; i++)
        cin >> arr[i];
    cout << "Enter the initial head position: ";
    cin >> head;
    cout << "Enter the disk size: ";
    cin >> disk_size;

    do {
        cout << "\nDisk Scheduling Algorithms:\n";
        cout << "1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fcfs(arr, size, head);
                break;
            case 2:
                sstf(arr, size, head);
                break;
            case 3:
                scan(arr, size, head, disk_size);
                break;
            case 4:
                cscan(arr, size, head, disk_size);
                break;
            case 5:
                look(arr, size, head);
                break;
            case 6:
                clook(arr, size, head);
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
