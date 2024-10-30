#include <iostream>
#include <windows.h>
#include <psapi.h>

using namespace std;

size_t memory_allocated = 0;
const char* divider = "\n-----------------------------------------------------------";

void* operator new(size_t size) {
    memory_allocated += size;
    cout << divider << "\nAllocated: " << size << " bytes.\tTotal memory allocated: " << memory_allocated << " bytes" << divider << "\n\n";
    return malloc(size);
}

void* operator new[](size_t size) {
    memory_allocated += size;
    cout << divider << "\nAllocated: " << size << " bytes.\tTotal memory allocated: " << memory_allocated << " bytes" << divider << "\n\n";
    return malloc(size);
}

void operator delete(void* pointer, size_t size) {
    memory_allocated -= size;
    cout << divider << "\nFreed: " << size << " bytes.\tTotal memory allocated: " << memory_allocated << " bytes" << divider << "\n\n";
    free(pointer);
}

void operator delete[](void* pointer, size_t size) {
    memory_allocated -= size;
    cout << divider << "\nFreed: " << size << " bytes.\tTotal memory allocated: " << memory_allocated << " bytes" << divider << "\n\n";
    free(pointer);
}

SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    if (result) {
        return memCounter.WorkingSetSize;
    }
    return 0;
}

int main() {


    auto currentMemory0 = getMemoryUsage();
    cout << "0\tInitial memory consumption: " << currentMemory0 << " bajtova" << endl;

    Sleep(1000);

    auto currentMemory1 = getMemoryUsage();
    cout << "1\tCurrent memory consumption: " << currentMemory1 << " bajtova" << endl;

    int* array = new int[10000];

    auto currentMemory2 = getMemoryUsage();
    cout << "2\tCurrent memory consumption: " << (currentMemory2 - currentMemory1) << " bajtova" << endl;

    operator delete[](array, memory_allocated);

    auto currentMemory3 = getMemoryUsage();
    cout << "3\tCurrent memory consumption: " << (currentMemory3 - currentMemory1) << " bajtova" << endl;

    cout << "\n\n\n";

    cout << "Additional new/delete opearator testing..." << endl;

    int* p = new int;
    delete p;

    int* arr = new int[10];
    operator delete[](arr, memory_allocated);

    return 0;
}