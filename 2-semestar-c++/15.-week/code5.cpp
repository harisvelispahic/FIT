//============================================================ CODE 5 ============================================================
#include <iostream>
#include <vector>
#include <thread>
#include <future>
using namespace std;

/*
    DEMO :: korištenje funkcije std::async 
*/

float izracunajProsjek(long long brojSlucajnihBrojeva) {
    cout << "Funkcija za računanje prosjeka se odvija na threadu sa ID-jem: " << this_thread::get_id() << endl;
    cout << "Racunanje prosjeka..." << endl;
    float prosjek = 0;
    for (long long i = 1; i <= brojSlucajnihBrojeva; i++) {
        int x = rand() % 10;
        // resurs 'prosjek' će biti otključan sa izlaskom iz trenutnog scop-a 
        prosjek = ((i - 1.0) / i) * prosjek + (1.0 / i) * x;
    }
    cout << "Prosjek izracunat." << endl;
    return prosjek;
}

int main() {
    long long brojSlucajnihBrojeva = 500000000;
    // async je funkcija iz std-a koja pokreće zadatu funkciju ili funkcionalni objekt asinhrono, tj. u zasebnom threadu
    // async funkcija vraća objekt tipa future, objekt koji će u budućnosti držati rezultat izvršene funkcije.
    future<float> prosjek = async(izracunajProsjek, brojSlucajnihBrojeva);
    cout << "ID glavnog thread-a: " << this_thread::get_id() << endl;
    vector<string> books = {"Dina", "Hyperion", "1984", "Babel-17", "Vodic kroz galaksiju za autostopere"};
    for (auto &obj : books)
        cout << obj << " ";
    cout << endl;
    cout << "Prosjek: " << prosjek.get() << endl;
    return 0;
}