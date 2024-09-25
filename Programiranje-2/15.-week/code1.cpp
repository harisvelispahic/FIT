//============================================================ CODE 1 ============================================================
#include<iostream>
#include<vector>
#include<thread>
using namespace std;


float izracunajProsjek(long long brojSlucajnihBrojeva){
    cout << "Racunanje prosjeka..." << endl;
    float prosjek = 0.0;

    // podešavanje random generator seed-a
    srand(time(0));

    // u nastavku je prikazana inkrementalna metoda računanja prosjeka (aritmetičke sredine)
    for (long long i = 1; i <= brojSlucajnihBrojeva; i++)
    {
        int x = rand() % 10;
        //cout << x << endl;
        prosjek = ((i-1.0)/i) * prosjek + (1.0/i) * x;
    }
    cout << "Prosjek izracunat." << endl;
    return prosjek; 
}

int main(){
    long long brojSlucajnihBrojeva = 500000000;
    cout << "ID glavnog thread-a:" << this_thread::get_id() << endl;
    // računanje prosjeka za generisane slučajne vrijednosti
    // PRIMJEDBA: velika vrijednost varijable 'brojSlucajnihBrojeva' uzrokuje zastoj glavnog thread-a i čekanje na izvršenje operacije računanja prosjeka
    float prosjek = izracunajProsjek(brojSlucajnihBrojeva);
    cout << "Prosjek je: " << prosjek << endl;
    // kreiranje vektora knjiga
    vector<string> books = {"Dina", "Hyperion", "1984", "Babel-17",  "Vodic kroz galaksiju za autostopere"};


    // ispisivanje vektora knjiga na glavnom thread-u
    for(auto & obj : books)
        cout << obj << "\n";
    cout << endl;
    return 0;
}