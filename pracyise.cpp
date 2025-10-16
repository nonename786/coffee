#include <iostream>
#include<cstring>
#include<string>
#include<fstream>
using namespace std;

int main() {
    ifstream f;
    f.open("new.txt");
    char value;
    string s="0";
    f >>value;
    while(f.good()){
    	s +=value;
    	f>>value;
	}
	cout<<s;
    f.close();
    return 0;
}



