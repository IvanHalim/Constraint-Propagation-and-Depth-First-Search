#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

string concatenate(char a, char b) {
    return string() + a + b;
}

vector<string> cross(string A, string B) {
    vector<string> str;
    for (int i = 0; i < A.length(); i++) {
        for (int j = 0; j < B.length(); j++) {
            str.push_back(concatenate(A[i],B[i]));
        }
    }

    return str;
}

int main() {
    vector<string> x = cross("ABC", "123");
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << ' ';
    }
    cout << endl;

    return 0;
}