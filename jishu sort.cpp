#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> count(n + 1, 0);  
    for (int i = 0; i < m; i++) {
        int vote;
        cin >> vote;
        count[vote]++;
    }
    
    bool first = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < count[i]; j++) {
            if (!first) {
                cout << " ";
            }
            cout << i;
            first = false;
        }
    }
    cout << endl;
    
    return 0;
}
