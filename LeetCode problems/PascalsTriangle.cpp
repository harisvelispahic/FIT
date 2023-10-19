#include <iostream>
#include <vector>
using namespace std;

int main(){
    
    int numRows;
    cout << "Enter the number of rows of the Pascal's triangle: ";
    cin >> numRows;
    vector<vector<int>> arr{                                //2D vector initialization
        {1},
        {1,1}                                               //the first two rows are initialized
    };
    arr.resize(numRows+1);                                  //resizing of the outer vector to number of rows
    for(int i=0; i<numRows; i++) arr[i].resize(i+1);        //resizing of inner vectors to number of members per each row of the triangle


    cout << arr.at(0).at(0) << endl;                        //manually writing '1' into the console
    for (int i = 2; i <= numRows; i++) {                    //outer loop goes from 1 to number of rows
        vector<int> subArr;                                 //a subarray is initialized in which temporary values will be stored
        
        subArr.resize(i+1);                                 //subarray is resized to number of members in the row
        for (int j = 0; j < i; j++) {                       //inner loop goes from 1 to i
            
            subArr.at(0) = 1;                                                                       //first element is always '1'
            if(j!=0 && j!=i-1) subArr.at(j) = arr.at(i - 1).at(j - 1) + arr.at(i - 1).at(j);        //an element is the sum of the two elements which sit above it
            cout << subArr.at(j) << " ";
            subArr.at(i - 1) = 1;                                                                   //last element is always '1'
        }
        cout << endl;
        arr.at(i) = subArr;                                 //temporary subarray is appended to the outer vector
    }

    arr.clear();
    
    return 0;
}
