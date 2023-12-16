#include <iostream>
using namespace std;


/*
    Program inputs a number n.
    Output is the least number m that is >= to n.
    m = k ^ l, k,l >= 2

*/
int main() {
    int n;
    cout << "Enter a number (n>0): ";
    do {
        cin >> n;
        if(n<=0)
            cout << "Number you entered is not a natural number! Please enter again: ";

    } while (n <= 0);

    int m = n, output, k, l;
    bool found = false;
    while (!found) {
        for (int i = 2; i < m; i++) {
            for (int j = 2; j < m; j++) {
                if (m == pow(i, j)) {
                    output = m;
                    k = i;
                    l = j;
                    found = true;
                    break;
                }
            }
        }
        m++;
    }
    cout << output << " = " << k << " ^ " << l <<  endl;

    return 0;
}