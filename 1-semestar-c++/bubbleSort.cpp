#include <iostream>
//#include <ctime>
using namespace std;

const int arrLength = 10;

void input(int[]);
void output(int[]);
void sort(int[]);


int main(){
	//srand(time(NULL));
	int arrayToSort[10] = {};

	input(arrayToSort);
	output(arrayToSort);
	sort(arrayToSort);
	output(arrayToSort);

	return 0;
}

void input(int arr[]) {
	for (size_t i = 0; i < arrLength; i++)
	{
		arr[i] = rand() % 1000 + 1;
	}
}

void output(int arr[]) {
	for (size_t i = 0; i < arrLength; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void sort(int arr[]) {
	bool change = true;
	int upperBound = arrLength - 1, iterations=0;
	while (change)
	{
		change = false;
		for (size_t i = 0; i < upperBound; i++)
		{
			if (arr[i] > arr[i + 1]) {
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				change = true;
				iterations++;
			}
		}
		upperBound--;
	}
	cout << "Number of iterations to sort the array: " << iterations << endl;
}