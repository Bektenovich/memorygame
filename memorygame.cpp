#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, n;
    int matched = 0;
    int moves = 0;
    cout << "Welcome to the Memory Game" << endl;
    cout << "Enter the size of an array (6-20): ";
    cin >> a;

    int arr[a];
    string numbers[a];
    n = (a / 2);

    for (int i = 0; i < a; i += 2) {
        arr[i] = i;
        arr[i + 1] = i;
    }
    for (int i = 0; i < a; i++) {
        numbers[i] = "?";
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(arr, arr + a, g);

    while (matched == 0) {
        int index1, index2;
        int check = 0;
        cout << "Here is the array: ";
        for (int i = 0; i < a; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
        cout << "Enter the index to show: ";
        cin >> index1;
        cout << "The card at the index " << index1 << " is: " << arr[index1] << endl;
        cout << "Enter the second index to show: ";
        cin >> index2;
        cout << "The card at the index " << index2 << " is: " << arr[index2] << endl;
        moves++;
        for (int i = 0; i < a; i++) {
            if (i == index1 or i == index2) {
                cout << arr[i] << " ";
            }
            else {
                cout << numbers[i] << " ";
            }
        }
        if (arr[index1] == arr[index2]) {
            cout << "\nGreat the cards are matched. Continue..." << endl;
            numbers[index1] = to_string(arr[index1]);
            numbers[index2] = to_string(arr[index2]);
        }
        else {
            cout << "\nThe cards do not match! Try again!" << endl;
        }
        for (int i = 0; i < a; i++) {
            if (numbers[i] != "?") {
                check++;
            }
        }
        if (check == a) {
            cout << "You won!"<<endl;
            cout<<"Total moves: " << moves << endl;
            matched = 1;
        }
        else {
            cout << "Press Enter to continue...";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            system("cls");
        }
    }
}