#include <iostream>
#include <vector>
using namespace std;

void countingSort(vector<vector<int>>& arr, int column) {
    int n = arr.size();
    int k = 4;
    vector<vector<int>> output(n, vector<int>(10));
    vector<int> count(k, 0);

    // count occurrences of each digit in this columnumn
    for (int i = 0; i < n; i++)
        count[arr[i][column]]++;

    for (int i = 1; i < k; i++)
        count[i] += count[i - 1];

    // build output array (stable sort, process backwards)
    for (int i = n - 1; i >= 0; i--) {
        int digit = arr[i][column];
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void radixSort(vector<vector<int>>& arr) {
    // sort by each digit from least significant to most
    for (int column = 9; column >= 0; column--) {
        countingSort(arr, column);
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> arr(n, vector<int>(10));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> arr[i][j];
        }
    }

    radixSort(arr);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cout << arr[i][j] << ";";
        }
        cout << endl;
    }

    return 0;
}