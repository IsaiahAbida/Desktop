#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// function to find max crossing subarray sum
int maxCrossingSum(const vector<int>& arr, int left, int mid, int right) {
    // Include elements on left of mid
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    // include elements on right of midpoint
    sum = 0;
    int right_sum = INT_MIN;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    // return sum of elements on left and right of mid
    return left_sum + right_sum;
}

// function to find maximum subarray sum
int maxSubArray(const vector<int>& arr, int left, int right) {
    if (left == right)  // base case: only one element
        return arr[left];

    int mid = left + (right - left) / 2;

    int left_max = maxSubArray(arr, left, mid);
    int right_max = maxSubArray(arr, mid + 1, right);
    int cross_max = maxCrossingSum(arr, left, mid, right);

    // return max({left_max, right_max, cross_max}); reason why ta couldnt compile
    return max(max(left_max, right_max), cross_max);

}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int result = maxSubArray(arr, 0, n - 1);
    cout << result;  // output only the sum, no spaces/newlines

    return 0;
}