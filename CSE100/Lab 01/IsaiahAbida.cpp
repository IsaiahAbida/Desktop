#include <iostream>
#include <vector> 
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i=0; i < n; i++){
        cin >> arr[i];
    }

    //Insertion sort with snapshot output
    for (int i = 1; i< n; i++){
        int temp = arr[i];
        int j = i - 1;

        //move elements greater than temp
        while (j >= 0 && arr[j] > temp) {
        arr[j + 1] = arr[j];
        j--;
        }
        arr[j + 1] = temp;

        //print the first i+1 elements
        for (int k = 0; k <= i; k++){
        cout << arr[k] << ";";
        }
        cout << endl;
    }

    for (int i = 1; i < n; i++){
        int temp = arr[i];
        int j = i - 1;


        while(j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;

        for (int k = 0; k <= i; k++){
            cout << arr[k] << ";";
        }
        cout << endl;
    }

    for (int i = 1; i < n; i++){
        int temp = arr[i] ; 
        int j = i - 1; 

        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp; 
        for (int k = 0;)
        int temp = arr[i] ; 
        int j = i -1; 

        while 9 j >= 0 &&
    }

    for (int i = 1 ; i < n ; i++){
        int temp = s
        int temp = 
    }
    return 0;

}