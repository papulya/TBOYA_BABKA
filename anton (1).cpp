#include <iostream>   // Для вывода и ввода, команды
#include <fstream>    // файлы читать/писать
#include <vector>     // Для динамических масивов, чтобы можно было их изменять
#include <cstdlib>    // рандом, exit и всякое
#include <ctime>      // время, надо для рандома
#include <string>     // строки, что-то типо массив чаров, но удобнее
#include <locale.h>   // русский текст в консоли
#include <windows.h>  // кодировки винды

using namespace std;

// ну это типо для меню
void showMenu() {
    cout << endl << "=== СМЕХОТЕКА ===" << endl;
    cout << "1 < Случайный анекдот" << endl;
    cout << "2 < Выборочный анекдот" << endl;
    cout << "3 < Добавить анекдот" << endl;
    cout << "4 < Количество анекдотов" << endl;
    cout << "5 < Показать все анекдоты" << endl;
    cout << "6 < Очистить список анекдотов" << endl;
    cout << "7 < Сортировка анекдотов" << endl;
    cout << "8 < Поиск по слову" << endl;
    cout << "0 < Выход" << endl;
    cout << "Выберите: ";
}

// сортировка анекдотов (по длине)
void sortJokes(vector<string>& jokes) {
    system("cls");
    for (size_t i = 0; i < jokes.size(); i++) {
        for (size_t j = 0; j < jokes.size() - i - 1; j++) {
            if (jokes[j].size() > jokes[j + 1].size()) {
                swap(jokes[j], jokes[j + 1]); // меняем местами
            }
        }
    }
}

// поиск анекдота по слову
void searchJoke(const vector<string>& jokes, const string& word) {
    system("cls");
    bool found = false;
    for (const auto& joke : jokes) {
        if (joke.find(word) != string::npos) { // если слово есть
            cout << joke << endl;
            found = true;
        }
    }
    if (!found) cout << "Ничего не найдено" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); // короче, чтобы русский норм был
    SetConsoleOutputCP(1251); // Эта команда и та что ниже, нужна чтобы в файлах был тоже русиш текст
    SetConsoleCP(1251);

    vector<string> jokes;

    // чтение из файла
    ifstream file("jokes.txt"); // открываем
    string line;
    while (getline(file, line)) { // читаем строки
        jokes.push_back(line); // заполняем вектор
    }
    file.close();

    if (jokes.empty()) { // если файл пустой, заливаем дефолтные
        jokes.push_back("Почему программисты не могут работать с детьми? Потому что они всегда просят перезагрузить!");
        jokes.push_back("Почему коты всегда садятся на клавиатуру? Потому что они хотят быть на высоте.");
        jokes.push_back("Почему программисты никогда не играют в футбол? Потому что они не могут победить без исходного кода.");
        jokes.push_back("Как называется программистская вечеринка? - Баг-фест.");
        jokes.push_back("Почему компы часто перегреваются? Потому что на них постоянно работает Windows!");
    }

    srand(static_cast<unsigned>(time(0))); // рандом

    int choice = -1;

    while (choice != 0) {
        showMenu();
        cin >> choice;

        if (choice == 1) { // случайный анекдот
            system("cls"); // типа чистим консоль
            cout << "Анекдот:" << endl << jokes[rand() % jokes.size()] << endl; // рандом
        }
        else if (choice == 2) { // выборочный
            system("cls");
            cout << "Список анекдотов:" << endl;
            for (size_t i = 0; i < jokes.size(); i++) {
                cout << i + 1 << ". " << jokes[i] << endl;
            }
            int number;
            cout << "Введите номер (1-" << jokes.size() << "): ";
            cin >> number;
            if (number >= 1 && number <= jokes.size()) { // ну типа проверка
                cout << "Анекдот #" << number << ":" << endl << jokes[number - 1] << endl;
            }
            else {
                cout << "Ошибка: Неверный номер!" << endl;
            }
        }
        else if (choice == 3) { // добавление
            system("cls");
            cin.ignore();
            cout << "Введите анекдот: ";
            getline(cin, line);
            jokes.push_back(line); // добавляем в массив

            // запись в файл
            ofstream file("jokes.txt", ios::out); // ну короче пишем, ios::out = перезапись
            for (auto& joke : jokes) {
                file << joke << endl; // записываем каждый анекдот
            }
            file.close();
            cout << "Анекдот сохранён!" << endl;
        }
        else if (choice == 4) { // кол-во анекдотов
            system("cls");
            cout << "Всего анекдотов: " << jokes.size() << endl;
        }
        else if (choice == 5) { // показать все
            system("cls");
            cout << "Список всех анекдотов:" << endl;
            for (size_t i = 0; i < jokes.size(); i++) {
                cout << i + 1 << ". " << jokes[i] << endl;
            }
        }
        else if (choice == 6) { // очистка
            system("cls");
            jokes.clear();
            ofstream file("jokes.txt", ios::out); // очищаем файл, а ios::out нужен для того чтобы открыть и перезаписать файл
            file.close();
            cout << "Список анекдотов очищен!" << endl;
        }
        else if (choice == 7) { // сортировка
            system("cls");
            sortJokes(jokes);
            cout << "Анекдоты отсортированы!" << endl;
        }
        else if (choice == 8) { // поиск
            system("cls");
            string word;
            cout << "Введите слово для поиска: ";
            cin >> word;
            searchJoke(jokes, word);
        }
    }

    cout << "Выход..." << endl;
    return 0;
}
