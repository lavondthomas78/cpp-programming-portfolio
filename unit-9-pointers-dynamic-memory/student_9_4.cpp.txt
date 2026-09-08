// student_9_4.cpp — Lab 9.4 (Option 1: dynamic scores, average, bubble sort)
// Your Name, Course, Date

#include <iostream>
#include <iomanip>
using namespace std;

void bubbleSortAsc(float* a, int n) {
    if (!a || n <= 1) return;
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] > a[i + 1]) {
                float tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                swapped = true;
            }
        }
        --n; // last item placed
    } while (swapped);
}

int main() {
    cout << fixed << showpoint << setprecision(2);

    int size = 0;
    cout << "How many scores? ";
    cin  >> size;
    if (size <= 0) {
        cerr << "Size must be positive.\n";
        return 1;
    }

    float* scores = new (nothrow) float[size];
    if (!scores) {
        cerr << "Allocation failed.\n";
        return 1;
    }

    cout << "Enter " << size << " scores:\n";
    for (int i = 0; i < size; ++i) {
        cin >> scores[i];
    }

    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += scores[i];
    double avg = sum / size;

    bubbleSortAsc(scores, size);

    cout << "\nAverage = " << avg << '\n';
    cout << "Sorted (ascending): ";
    for (int i = 0; i < size; ++i) {
        cout << scores[i] << (i + 1 < size ? ' ' : '\n');
    }

    delete[] scores;
    return 0;
}
