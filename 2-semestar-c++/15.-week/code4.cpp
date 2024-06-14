//============================================================ CODE 4 ============================================================
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

/*
    DEMO :: uspavljivanje glavnog thread-a
*/


// koristimo mutex (binarni semafor) za korištenje resursa 'prosjek'
mutex mtx; 

void izracunajProsjek(long long brojSlucajnihBrojeva, float &prosjek) {
    cout << "Funkcija za računanje prosjeka se odvija na threadu sa ID-jem: " << this_thread::get_id() << endl;
    cout << "Racunanje prosjeka..." << endl;
    for (long long i = 1; i <= brojSlucajnihBrojeva; i++) {
        int x = rand() % 10;
        // zaključvanja mutex-a (prije modifikacije resursa 'prosjek')
        // lock_guard je mutex wrapper za zaključavanje objekta mutex (stavljanje katanca)
        lock_guard<mutex> katanac(mtx); 
        // resurs 'prosjek' će biti otključan sa izlaskom iz trenutnog scope-a 
        prosjek = ((i - 1.0) / i) * prosjek + (1.0 / i) * x;
    }
    cout << "Prosjek izracunat." << endl;
}

int main() {
    long long brojSlucajnihBrojeva = 500000000;
    cout << "ID glavnog thread-a: " << this_thread::get_id() << endl;
    float prosjek = 0.0;
    thread t1(izracunajProsjek, brojSlucajnihBrojeva, ref(prosjek));
    vector<string> books = {"Dina", "Hyperion", "1984", "Babel-17", "Vodic kroz galaksiju za autostopere"};
    for (auto &obj : books)
        cout << obj << " ";
    cout << endl;

    cout << "Glavni thread spava 4 sekunde..." << endl;
    this_thread::sleep_for(chrono::seconds(4));
    cout << "Glavni thread se budi!" << endl;
    {
        // zaključavanje mutex-a prije modifikacije vrijednosti
        lock_guard<mutex> katanac(mtx);
        prosjek += 15000;
    }

    t1.join();
    cout << "Prosjek: " << prosjek << endl;
    return 0;
}