#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Объявление функций
// Функция инициализации игры
int initializeGame(vector<int>& cards, int size);
// Функция отображения массива
void displayArray(const vector<int>& cards, const vector<int>& revealed);
// Основная логика игры
int playGame(vector<int>& cards, vector<int>& revealed);

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    // Приветствие игрока
    cout << "Welcome to the Memory Game!" << endl;

    // Ввод размера массива
    int size;
    cout << "Enter the size of an array (6-20): ";
    cin >> size;

    // Проверка корректности размера массива
    if (size < 6 || size > 20) {
        cout << "Invalid size. Please choose a size between 6 and 20." << endl;
        return 1; // Завершение программы с ошибкой
    }

    // Создание векторов для карт и открытых карт
    vector<int> cards, revealed(size * 2);

    // Инициализация игровых карт
    if (!initializeGame(cards, size)) {
        cout << "Game initialization failed. Exiting." << endl;
        return 1;
    }

    // Запуск основной части игры
    int moves = playGame(cards, revealed);

    // Поздравление с завершением игры
    cout << "Congratulations! You matched all pairs in " << moves << " moves." << endl;

    return 0; // Успешное завершение программы
}

// Инициализация игры: возвращает 0 при неудаче, 1 при успехе
int initializeGame(vector<int>& cards, int size) {
    // Проверка корректности размера массива
    if (size < 6 || size > 20)
        return 0; // Неудачная инициализация

    // Генерация пар чисел и добавление их в вектор карт
    for (int i = 1; i <= size / 2; ++i) {
        cards.insert(cards.end(), {i, i});
    }

    // Перемешивание карт
    random_shuffle(cards.begin(), cards.end());

    return 1; // Успешная инициализация
}

// Вывод массива в консоль
void displayArray(const vector<int>& cards, const vector<int>& revealed) {
    // Перебор карт и отображение их состояния
    for (size_t i = 0; i < cards.size(); ++i) {
        cout << (revealed[i] ? to_string(cards[i]) : "? ") << " ";
    }
    cout << endl;
}

// Основная логика игры: возвращает количество ходов
int playGame(vector<int>& cards, vector<int>& revealed) {
    int moves = 0; // Счетчик ходов

    // Игра продолжается, пока все карты не будут открыты
    while (count(revealed.begin(), revealed.end(), 1) < static_cast<int>(cards.size())) {
        system("cls"); // Очистка экрана (замените на "clear" для Linux/Mac)

        cout << "Here is the array: ";
        displayArray(cards, revealed); // Вывод текущего состояния массива карт

        int index1, index2;

        // Ввод индекса первой карты
        cout << "Enter the index to show: ";
        cin >> index1;

        // Проверка валидности ввода
        if (index1 < 0 || index1 >= static_cast<int>(cards.size()) || revealed[index1] == 1) {
            cout << "Invalid input. Try again." << endl;
            continue; // Переход к следующей итерации цикла
        }

        revealed[index1] = 1; // Открытие первой карты
        system("cls"); // Очистка экрана

        cout << "Here is the array: ";
        displayArray(cards, revealed);

        // Ввод индекса второй карты
        cout << "Enter the second index to show: ";
        cin >> index2;

        // Проверка валидности ввода
        if (index2 < 0 || index2 >= static_cast<int>(cards.size()) || revealed[index2] == 1) {
            cout << "Invalid input. Try again." << endl;
            revealed[index1] = 0; // Закрытие первой карты
            continue; // Переход к следующей итерации цикла
        }

        revealed[index2] = 1; // Открытие второй карты
        system("cls"); // Очистка экрана

        cout << "Here is the array: ";
        displayArray(cards, revealed);

        // Проверка совпадения открытых карт
        if (cards[index1] == cards[index2])
            cout << "Great! The cards are matched. Continue..." << endl;
        else {
            cout << "The cards do not match. Try again!" << endl;
            revealed[index1] = revealed[index2] = 0; // Закрытие обеих карт
        }

        moves++; // Увеличение счетчика ходов

        // Ожидание нажатия Enter для продолжения
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return moves; // Возвращение количества сделанных ходов
}
