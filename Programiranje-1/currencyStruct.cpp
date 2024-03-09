#include <iostream>
using namespace std;

/*
	A structure is given that describes the current exchange rate of a currency in the exchange rate list 
    (how many BAM you will get for one unit of that currency).

    struct Exchange 
    {
        char currency[5];
        float value;
    };

    E.g. the current exchange rate for the currency EUR is 1.955830 BAM, so the struct for that currency contains the values 
    "EUR" and 1.95583.

    Write a function exchange() that receives a list of exchange rates (array of arbitrary length 
    whose members are of type struct Exchange), one string that indicates the currency (eg "EUR") 
    and the amount of money in that currency, and returns the amount in BAM.

    In the above example, if we were to pass an amount of 2, the function should return 3.91166.
    If the currency is not in the string, 0 should be returned.

    You must also write a main function that enables:

    entry of exchange rate list (string),
    then enter currency and amount,
    function call and print conversion results.
*/

struct Exchange
{
    char currency[5];
    float value;

    void input() {
        cout << "Please enter the currency: ";
        char temp[4];
        cin.getline(temp, size(temp));
        strcpy_s(currency, strlen(temp) + 1, temp);

        cout << "Please enter the value: ";
        cin >> value;

        cin.ignore();
        cout << endl;
    }
};

float exchange(Exchange* arr, int size, char* currency, float iznos) {
    int counter = 0;
    float exchangeRate = 0.0f;
    for (int i = 0; i < size; i++) {
        if (!strcmp(arr[i].currency, currency)) {
            exchangeRate = arr[i].value;
            counter++;
            break;
        }
    }

    return (counter == 0) ? 0 : exchangeRate * iznos;
}

int main() {

    int arrSize;
    do {
        cout << "Please enter the size of the array: ";
        cin >> arrSize;
    } while (arrSize < 1);

    cin.ignore(); cout << endl;

    Exchange* exchangeRate = new Exchange[arrSize];

    // input
    for (int i = 0; i < arrSize; i++) {
        exchangeRate[i].input();
    }

    char chosenCurrency[5];
    cout << "Please enter the currency you would like to convert to BAM: ";
    cin.getline(chosenCurrency, size(chosenCurrency));
    
    cout << endl;

    float amount = 0.0f;
    cout << "Please enter the amount you would like to convert to BAM: ";
    cin >> amount;

    float result = exchange(exchangeRate, arrSize, chosenCurrency, amount);
    if (result != 0) {
        cout << amount << " " << chosenCurrency << " = " << result << " BAM" << endl;
    }
    else {
        cout << "Currency not found!" << endl;
    }

    delete[] exchangeRate;
    exchangeRate = nullptr;

    return 0;
}