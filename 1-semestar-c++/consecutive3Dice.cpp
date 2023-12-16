#include <iostream>
#include <ctime>
using namespace std;

// number of tries before 3 equal consecutive throws

int main(){
    srand(time(NULL));

    int a, b, c, tries = 1, consecutive = 0;
    a = rand() % 6 + 1;
    b = rand() % 6 + 1;
    c = rand() % 6 + 1;

    while (consecutive < 2) {
        tries++;
        a = rand() % 6 + 1;
        b = rand() % 6 + 1;
        c = rand() % 6 + 1;
        if (a == b && b == c)
            consecutive++;
        if (a != b && b != c && consecutive == 1)
            consecutive--;
    }
    cout << "Number of tries before 3 equal consecutive throws: " << tries << endl;
}
