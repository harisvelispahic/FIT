#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;


int main()
{
    cout << ">>> CONVERSION FROM ONE BASE TO ANOTHER (UP TO 10 DIGITS/CHARS AND UP TO BASE 16 (HEX)) <<<";
    cout << endl;
    cout << endl;

    cout << "Type in the number you want to convert: ";
    string input;
    cin >> input;

    vector<int> arr;
    arr.resize(input.length());
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == 'A') arr.at(i) = 10;
        else if (input[i] == 'B') arr.at(i) = 11;
        else if (input[i] == 'C') arr.at(i) = 12;
        else if (input[i] == 'D') arr.at(i) = 13;
        else if (input[i] == 'E') arr.at(i) = 14;
        else if (input[i] == 'F') arr.at(i) = 15;
        else arr.at(i) = input[i] - '0';            //int to char conversion
    }
    
    /*
    for (int i = 0; i < input.length(); i++) {             //digits output
        cout << arr.at(i) << endl;
    }
    */
    
    
    int base1, base2;
    cout << "Type in the base of the number you want to convert: ";
    cin >> base1;

    cout << "Type in the base you want to convert to: ";
    cin >> base2;
    
    for (int i = 0; i < input.length(); i++) {
        if (arr.at(i) >= base1) {
            cout << "Disallowed base!";
            return 0;
        }
    }

   int decimal = 0, counter = input.length() - 1;
    for (int i = 0; i < input.length(); i++) {
        decimal += arr.at(i) * pow(base1, counter);
        //cout << decimal << endl;                  //addition process step by step
        counter--;
    }
    //cout << decimal << endl;                      //value of number in decimal system
   
    counter = 0;
    string text;
    while (decimal != 0) {
        int temp = 0;
        temp += decimal % base2; 
        if (temp == 10) text += 'A';
        else if (temp == 10) text += 'A';
        else if (temp == 11) text += 'B';
        else if (temp == 12) text += 'C';
        else if (temp == 13) text += 'D';
        else if (temp == 14) text += 'E';
        else if (temp == 15) text += 'F';
        else text += to_string(temp);
        //cout << temp << endl;                     //addition process step by step
        decimal /= base2;
        counter++;
    }
    string output;
    for (int i = text.length() - 1; i >= 0; i--) {
        output += text[i];
    }

    cout << "The number in base " << base2 << " equals: " << output << endl;
    
    arr.clear();
}