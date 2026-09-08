/*
  quiz_game.cpp
  Author: LaVon Thomas
  Course: CIS240 – Programming in C++
  Description:
    A console multiple-choice quiz game demonstrating variables, arrays,
    functions, loops, conditionals, input validation, and simple calculations.
    Features:
      - Main menu (Start / How to Play / Exit)
      - 10 question bank (multiple choice)
      - Randomized order each round (Fisher–Yates)
      - Scoring, percentage, and letter grade
      - Play-again loop with high score for the session
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>   // rand, srand
#include <ctime>     // time (seed)
using namespace std;

// ----- Data Types -----
struct Question {
    string prompt;
    string choices[4];
    int correctIndex; // 0..3
};

// ----- Function Prototypes -----
void showWelcome();
void showHowToPlay();
int  getMenuChoice();
void waitForEnter();

void shuffleIndices(int idx[], int n);
int  askQuestion(const Question& q);
char letterGrade(double pct);
void playRound(const Question bank[], int bankSize, int questionsToAsk, int& scoreOut, double& pctOut);

// ----- Question Bank (10 items) -----
const int BANK_SIZE = 10;
const Question BANK[BANK_SIZE] = {
    {
        "Which C++ header provides input and output with cout/cin?",
        {"<iostream>", "<iomanip>", "<vector>", "<string>"},
        0
    },
    {
        "What does the '&&' operator mean in a condition?",
        {"Bitwise AND", "Logical AND", "Address-of", "Array subscript"},
        1
    },
    {
        "Which type stores true/false values?",
        {"char", "int", "bool", "float"},
        2
    },
    {
        "Arrays in C++ are indexed starting at…",
        {"-1", "0", "1", "It depends"},
        1
    },
    {
        "What does 'const' before a variable mean?",
        {"Global scope", "Uninitialized", "Cannot be modified", "Pointer type"},
        2
    },
    {
        "Which statement repeats while a condition remains true?",
        {"if", "switch", "while", "break"},
        2
    },
    {
        "Which line correctly declares a function that returns an int and takes no parameters?",
        {"int doThing;", "int doThing() { }", "void doThing(int);", "return int doThing();"},
        1
    },
    {
        "Which library function seeds the pseudo-random number generator?",
        {"seed()", "srand()", "randseed()", "time()"},
        1
    },
    {
        "Given int a=5,b=2; the value of a % b is…",
        {"2", "1", "0", "3"},
        1
    },
    {
        "Which keyword allocates dynamic memory for a single int?",
        {"new int", "malloc(int)", "alloc<int>()", "make_int()"},
        0
    }
};

int main() {
    // Seed the RNG for random order each run
    srand(static_cast<unsigned int>(time(nullptr)));

    showWelcome();

    int highScore = 0;
    bool running = true;

    while (running) {
        int choice = getMenuChoice();

        if (choice == 1) {
            int score = 0;
            double pct = 0.0;

            // Ask 5 questions per round (change to 10 if you want the full bank)
            playRound(BANK, BANK_SIZE, 5, score, pct);

            if (score > highScore) {
                highScore = score;
                cout << "\nNew high score for this session: " << highScore << "!\n";
            }

            cout << "\nWould you like to play again? (y/n): ";
            char again;
            cin >> again;
            while (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
                cout << "Please enter y or n: ";
                cin >> again;
            }
            if (again == 'n' || again == 'N') {
                running = false;
            }
        }
        else if (choice == 2) {
            showHowToPlay();
        }
        else { // 3) Exit
            running = false;
        }
    }

    cout << "\nThanks for playing! High score this session: " << highScore << "\n";
    cout << "Goodbye!\n";
    return 0;
}

// ----- Function Definitions -----

void showWelcome() {
    cout << "=====================================\n";
    cout << "        C++ Console Quiz Game       \n";
    cout << "=====================================\n";
}

void showHowToPlay() {
    cout << "\nHow to Play:\n";
    cout << " - Choose '1' at the main menu to start a round.\n";
    cout << " - You will see multiple-choice questions.\n";
    cout << " - Type 1, 2, 3, or 4 to select your answer (input is validated).\n";
    cout << " - Your score, percentage, and letter grade are shown at the end.\n";
    cout << " - You can play multiple rounds; the highest score is tracked.\n\n";
    waitForEnter();
}

int getMenuChoice() {
    cout << "\nMain Menu\n";
    cout << "  1) Start Quiz\n";
    cout << "  2) How to Play\n";
    cout << "  3) Exit\n";
    cout << "Choose (1-3): ";

    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 3) {
            return choice;
        } else {
            cout << "Invalid input. Enter 1, 2, or 3: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void waitForEnter() {
    cout << "Press ENTER to return to the menu...";
    cin.ignore(10000, '\n'); // clear any leftover newline
    cin.get();
}

void shuffleIndices(int idx[], int n) {
    // Fisher–Yates shuffle
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = idx[i];
        idx[i] = idx[j];
        idx[j] = tmp;
    }
}

// Returns 1 if correct, 0 otherwise
int askQuestion(const Question& q) {
    cout << "\n" << q.prompt << "\n";
    for (int i = 0; i < 4; ++i) {
        cout << "  " << (i + 1) << ") " << q.choices[i] << "\n";
    }
    cout << "Your choice (1-4): ";

    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 4) break;
        cout << "Please enter 1, 2, 3, or 4: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if ((choice - 1) == q.correctIndex) {
        cout << "Correct!\n";
        return 1;
    } else {
        cout << "Incorrect. The correct answer was: "
             << (q.correctIndex + 1) << ") " << q.choices[q.correctIndex] << "\n";
        return 0;
    }
}

char letterGrade(double pct) {
    if (pct >= 90.0) return 'A';
    if (pct >= 80.0) return 'B';
    if (pct >= 70.0) return 'C';
    if (pct >= 60.0) return 'D';
    return 'F';
}

void playRound(const Question bank[], int bankSize, int questionsToAsk, int& scoreOut, double& pctOut) {
    // Clamp questionsToAsk
    if (questionsToAsk > bankSize) questionsToAsk = bankSize;

    // Build index array and shuffle so we can ask random questions
    int order[ BANK_SIZE ];
    for (int i = 0; i < bankSize; ++i) order[i] = i;
    shuffleIndices(order, bankSize);

    int score = 0;
    for (int i = 0; i < questionsToAsk; ++i) {
        int idx = order[i];
        score += askQuestion(bank[idx]);
    }

    scoreOut = score;
    pctOut = (questionsToAsk > 0) ? (100.0 * score / questionsToAsk) : 0.0;

    cout << "\nRound Results\n";
    cout << "-------------\n";
    cout << "Correct: " << score << " out of " << questionsToAsk << "\n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Percentage: " << pctOut << "%\n";
    cout << "Letter Grade: " << letterGrade(pctOut) << "\n";
}
