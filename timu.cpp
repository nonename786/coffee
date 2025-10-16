#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// 分区函数，选择最后一个元素作为基准
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // 选择最后一个元素作为基准
    int i = low - 1;        // 指向小于基准的区域的末尾

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++;  // 扩展小于基准的区域
            swap(arr[i], arr[j]);  // 将当前元素放到区域内
        }
    }
    // 将基准放到正确位置
    swap(arr[i + 1], arr[high]);
    return i + 1;  // 返回基准的索引
}

// 快速排序递归函数
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // 分区并获取基准位置
        int pi = partition(arr, low, high);

        // 递归排序基准左侧和右侧的子数组
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}



int main() {
    vector<int> arr;
    string input;
    
    
    
    // 读取整行输入
    getline(cin, input);
    
    // 使用字符串流解析输入
    stringstream ss(input);
    int number;
    
    while (ss >> number) {
        arr.push_back(number);
    }
    
    // 检查是否输入了数字
    if (arr.empty()) {
        cout << "未输入任何数字！" << endl;
        return 1;
    }
    
    int n = arr.size();
    
    
    
    
    quickSort(arr, 0, n - 1);
    cout<<arr[n];
    
    
    
    return 0;
}
