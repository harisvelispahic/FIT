//============================================================ CODE 2 ============================================================
#include<iostream>
#include<vector>
#include<thread>
using namespace std;


void izracunajProsjek(long long brojSlucajnihBrojeva, float & prosjek){

    cout << "Funkcija za računanje prosjeka se odvija na threadu sa ID-jem: " << this_thread::get_id() << endl;
    cout << "Racunanje prosjeka..." << endl;
    // u nastavku je prikazana inkrementalna metoda računanja prosjeka (aritmetičke sredine)
    for (long long i = 1; i <= brojSlucajnihBrojeva; i++)
    {
        int x = rand() % 10;
        //cout << x << endl;
        prosjek = ((i-1.0)/i) * prosjek + (1.0/i) * x;
    }
    cout << "Prosjek izracunat." << endl;
}

int main(){
    long long brojSlucajnihBrojeva = 500000000;
    cout << "ID glavnog thread-a:" << this_thread::get_id() << endl;
    // računanje prosjeka za generisane slučajne vrijednosti
    

    float prosjek = 0.0;
    // kreiranje sporednog thread-a pod nazivom 't1' za poziv funkcije izracunajProsjek 
    // proslijeđuju se dvije varijable 'brojSlucajnihBrojeva' (po vrijednosti) i 'prosjek' (po referenci)
    thread t1(izracunajProsjek, brojSlucajnihBrojeva, ref(prosjek));

    // čekanje na sporedni thread 't1' da izvrši računanje prosjeka
    t1.join();   // spajanje sporednog thread-a i glavnog thread-a
    // PRIMJEDBA :: Bez obzira što imamo dodatni thread, glavni thread i njegovo izvršenje je blokirano od strane sporednog thread-a
    cout << "Prosjek je: " << prosjek << endl;
    // kreiranje vektora knjiga
    vector<string> books = {"Dina", "Hyperion", "1984", "Babel-17",  "Vodic kroz galaksiju za autostopere"};


    // ispisivanje vektora knjiga na glavnom thread-u
    for(auto & obj : books)
        cout << obj << " ";
    cout << endl;
    return 0;
}