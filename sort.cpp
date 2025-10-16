#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;


int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;        

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;  
            swap(arr[i], arr[j]); 
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;  
}
    void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void printArray(const vector<int>& arr) {
	int n=arr.size();
    for (int i=0;i<n;i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
	int n,m;
    cin>>n>>m;
    cin.get();
    vector<int> arr;
    string input;
    getline(cin, input);
    stringstream ss(input);
    int number;
    
    while (ss >> number) {
        arr.push_back(number);
    }
    
    
    
    quickSort(arr, 0, n - 1);
    printArray(arr);
    
    return 0;
}
