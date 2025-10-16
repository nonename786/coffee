#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// ����������ѡ�����һ��Ԫ����Ϊ��׼
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1;        // ָ��С�ڻ�׼�������ĩβ

    for (int j = low; j <= high - 1; j++) {
        // �����ǰԪ��С�ڻ���ڻ�׼
        if (arr[j] <= pivot) {
            i++;  // ��չС�ڻ�׼������
            swap(arr[i], arr[j]);  // ����ǰԪ�طŵ�������
        }
    }
    // ����׼�ŵ���ȷλ��
    swap(arr[i + 1], arr[high]);
    return i + 1;  // ���ػ�׼������
}

// ��������ݹ麯��
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // ��������ȡ��׼λ��
        int pi = partition(arr, low, high);

        // �ݹ������׼�����Ҳ��������
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}



int main() {
    vector<int> arr;
    string input;
    
    
    
    // ��ȡ��������
    getline(cin, input);
    
    // ʹ���ַ�������������
    stringstream ss(input);
    int number;
    
    while (ss >> number) {
        arr.push_back(number);
    }
    
    // ����Ƿ�����������
    if (arr.empty()) {
        cout << "δ�����κ����֣�" << endl;
        return 1;
    }
    
    int n = arr.size();
    
    
    
    
    quickSort(arr, 0, n - 1);
    cout<<arr[n];
    
    
    
    return 0;
}
