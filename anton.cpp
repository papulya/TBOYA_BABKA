#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <locale.h>
#include <windows.h>

using namespace std;

// Функция для менюшки
void показатьМеню() {
    cout << endl << "=== СМЕХОТЕКА ===" << endl;
    cout << "1 < Случайный анекдот" << endl;
    cout << "2 < Выборочный анекдот" << endl;
    cout << "3 < Добавить анекдот" << endl;
    cout << "4 < Количество анекдотов" << endl;
    cout << "5 < Показать все анекдоты" << endl;
    cout << "6 < Очистить список анекдотов" << endl;
    cout << "0 < Выход" << endl;
    cout << "Выберите: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251); 
    SetConsoleCP(1251);

    vector<string> анекдоты;
    ifstream файл("шутки.txt");

    string строка;
    while (getline(файл, строка)) {
        анекдоты.push_back(строка);
    }
    файл.close();

    if (анекдоты.empty()) {
        анекдоты.push_back("Почему программисты не могут работать с детьми? Потому что они всегда просят перезагрузить!");
        анекдоты.push_back("Почему коты всегда садятся на клавиатуру? Потому что они хотят быть на высоте.");
        анекдоты.push_back("Почему программисты никогда не играют в футбол? Потому что они не могут победить без исходного кода.");
        анекдоты.push_back("Как называется программистская вечеринка? - Баг-фест.");
        анекдоты.push_back("Почему компы часто перегреваются? Потому что на них постоянно работает Windows!");
    }

    srand(static_cast<unsigned>(time(0)));

    int выбор = -1;

    while (выбор != 0) {
        показатьМеню();
        cin >> выбор;

        if (выбор == 1) { // Случайный анекдот
            system("cls");
            if (анекдоты.empty()) {
                cout << "Ошибка! Нет анекдотов." << endl;
            }
            else {
                cout << "Анекдот:" << endl << анекдоты[rand() % анекдоты.size()] << endl;
            }
        }

        if (выбор == 2) { // Выборочный анекдот
            system("cls");
            if (анекдоты.empty()) {
                cout << "Ошибка! Список анекдотов пуст." << endl;
            }
            else {
                cout << "Список всех анекдотов:" << endl;
                for (size_t i = 0; i < анекдоты.size(); i++) {
                    cout << i + 1 << ". " << анекдоты[i] << endl;
                }

                unsigned int номер;
                cout << "Введите номер анекдота (1-" << анекдоты.size() << "): ";
                cin >> номер;
                system("cls");
                if (номер >= 1 && номер <= анекдоты.size()) {
                    cout << "Анекдот #" << номер << ":" << endl << анекдоты[номер - 1] << endl;
                }
                else {
                    cout << "Ошибка: Неверный номер!" << endl;
                }
            }
        }

        if (выбор == 3) { // Добавление нового анекдота
            system("cls");
            cin.ignore();
            cout << "Введите анекдот: ";
            getline(cin, строка);
            анекдоты.push_back(строка);

            
            ofstream файл("шутки.txt", ios::out);
            for (auto& анекдот : анекдоты) {
                файл << анекдот << endl;
            }
            файл.close();

            cout << "Анекдот сохранён!" << endl;
        }

        if (выбор == 4) { // Количество анекдотов
            system("cls");
            cout << "Всего анекдотов: " << анекдоты.size() << endl;
        }

        if (выбор == 5) { // Показать все анекдоты
            if (анекдоты.empty()) {
                system("cls");
                cout << "Нет анекдотов!" << endl;
            }
            else {
                system("cls");
                cout << "Список всех анекдотов:" << endl;
                for (size_t i = 0; i < анекдоты.size(); i++) {
                    cout << i + 1 << ". " << анекдоты[i] << endl;
                }
            }
        }

        if (выбор == 6) { // Очистить анекдоты
            system("cls");
            анекдоты.clear();
            ofstream файл("шутки.txt", ios::out);
            файл.close();
            cout << "Список анекдотов очищен!" << endl;
        }
    }

    cout << "Выход..." << endl;
    return 0;
}
