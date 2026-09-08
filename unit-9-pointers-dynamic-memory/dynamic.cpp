// dynamic.cpp — Lab 9.2 (Dynamic Memory)
// Your Name, Course, Date

#include <iostream>
using namespace std;

const int MAXNAME = 10;

int main() {
    int  pos;
    char* name  = nullptr;
    int*  one   = nullptr;
    int*  two   = nullptr;
    int*  three = nullptr;
    int   result = 0;

    // allocate dynamic variables / array
    one   = new int;
    two   = new int;
    three = new int;
    name  = new char[MAXNAME]; // dynamic char array

    cout << "Enter your last name with exactly 10 characters.\n";
    cout << "If your name has < 10 characters, repeat last letter.\n"
            "Blanks at the end do not count.\n";

    // input WITHOUT bracketed subscript
    for (pos = 0; pos < MAXNAME; ++pos) {
        cin >> *(name + pos);
    }

    cout << "Hi ";
    // output WITHOUT bracketed subscript
    for (pos = 0; pos < MAXNAME; ++pos) {
        cout << *(name + pos);
    }
    cout << '\n';

    cout << "Enter three integer numbers separated by blanks\n";
    // store into dynamic ints (pointer variables only)
    cin >> *one >> *two >> *three;

    // echo print
    cout << "The three numbers are \n";
    cout << *one << ' ' << *two << ' ' << *three << '\n';

    // calculate sum using dereferenced pointers
    result = *one + *two + *three;
    cout << "The sum of the three values is " << result << '\n';

    // deallocate all dynamic memory
    delete one;
    delete two;
    delete three;
    delete[] name;

    return 0;
}
