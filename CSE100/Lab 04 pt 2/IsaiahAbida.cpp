#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
using namespace std;

// Partition function with random pivot
int randomizedPartition(vector<int>& arr, int p, int r) {
    int pivotIndex = p + rand() % (r - p + 1);
    swap(arr[pivotIndex], arr[r]);            
    int pivot = arr[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

// QuickSort recursive function
void quickSort(vector<int>& arr, int p, int r) {
    if (p < r) {
        int q = randomizedPartition(arr, p, r);
        quickSort(arr, p, q - 1);
        quickSort(arr, q + 1, r);
    }
}

int main() {
    srand(time(0));

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    quickSort(arr, 0, n - 1);


    for (int i = 0; i < n; i++)
        cout << arr[i] << ";";

    return 0;
}
