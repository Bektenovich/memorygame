#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Объявление функций
int initializeGame(vector<int>& cards, int size);
void displayArray(const vector<int>& cards, const vector<int>& revealed);
int playGame(vector<int>& cards, vector<int>& revealed);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Welcome to the Memory Game!" << endl;

    int size;
    cout << "Enter the size of an array (6-20): ";
    cin >> size;

    if (size < 6 || size > 20) {
        cout << "Invalid size. Please choose a size between 6 and 20." << endl;
        return 1;
    }

    vector<int> cards, revealed(size * 2);

    if (!initializeGame(cards, size)) {
        cout << "Game initialization failed. Exiting." << endl;
        return 1;
    }

    int moves = playGame(cards, revealed);

    cout << "Congratulations! You matched all pairs in " << moves << " moves." << endl;

    return 0;
}

// Инициализация игры: возвращает 0 при неудаче, 1 при успехе
int initializeGame(vector<int>& cards, int size) {
    if (size < 6 || size > 20) return 0;

    for (int i = 1; i <= size / 2; ++i) {
        cards.insert(cards.end(), {i, i});
    }

    random_shuffle(cards.begin(), cards.end());

    return 1;
}

// Вывод массива в консоль
void displayArray(const vector<int>& cards, const vector<int>& revealed) {
    for (size_t i = 0; i < cards.size(); ++i) {
        if (revealed[i]) {
            cout << cards[i] << " ";
        } else {
            cout << "? ";
        }
    }
    cout << endl;
}

// Основная логика игры: возвращает количество ходов
int playGame(vector<int>& cards, vector<int>& revealed) {
    int moves = 0;

    while (count(revealed.begin(), revealed.end(), 1) < static_cast<int>(cards.size())) {
        system("cls");

        cout << "Here is the array: ";
        displayArray(cards, revealed);

        int index1, index2;

        cout << "Enter the index to show: ";
        cin >> index1;

        if (index1 < 0 || index1 >= static_cast<int>(cards.size()) || revealed[index1]) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        revealed[index1] = 1;
        system("cls");

        cout << "Here is the array: ";
        displayArray(cards, revealed);

        cout << "Enter the second index to show: ";
        cin >> index2;

        if (index2 < 0 || index2 >= static_cast<int>(cards.size()) || revealed[index2]) {
            cout << "Invalid input. Try again." << endl;
            revealed[index1] = 0;
            continue;
        }

        revealed[index2] = 1;
        system("cls");

        cout << "Here is the array: ";
        displayArray(cards, revealed);

        if (cards[index1] == cards[index2])
            cout << "Great! The cards are matched. Continue..." << endl;
        else {
            cout << "The cards do not match. Try again!" << endl;
            revealed[index1] = revealed[index2] = 0;
        }

        moves++;

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return moves;
}
