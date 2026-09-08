// darray.cpp — Lab 9.3 (Dynamic Arrays)
// Your Name, Course, Date

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float* monthSales = nullptr;  // dynamic array pointer
    float  total = 0.0f;
    float  average = 0.0f;
    int    numOfSales = 0;

    cout << fixed << showpoint << setprecision(2);

    cout << "How many monthly sales will be processed? ";
    cin  >> numOfSales;

    // allocate array
    monthSales = new (nothrow) float[numOfSales];

    // (Optional) check allocation success for some compilers/grades
    if (monthSales == nullptr) {
        cout << "Error allocating memory!\n";
        return 1;
    }

    cout << "Enter the sales below\n";
    for (int count = 0; count < numOfSales; ++count) {
        cout << "Sales for Month number " << (count + 1) << ": ";
        cin  >> monthSales[count];
    }

    for (int count = 0; count < numOfSales; ++count) {
        total += monthSales[count];
    }

    average = (numOfSales > 0) ? (total / numOfSales) : 0.0f;
    cout << "Average Monthly sale is $" << average << '\n';

    // free dynamic array
    delete[] monthSales;
    return 0;
}
