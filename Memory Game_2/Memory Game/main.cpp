#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

int main() {
    srand((unsigned)time(0));
    setlocale(LC_ALL, "rus");

    int menu;
    do {
        system("cls");
        cout << "ИГРА 'ПАМЯТЬ' \n\n";
        cout << "1 - Начать игру\n";
        cout << "2 - Правила\n";
        cout << "3 - Выход\n\n";
        cout << "Выбери: ";
        cin >> menu;

        if (menu == 2) {
            showRules(); // Вызов функции из game_functions.cpp
            continue;
        }

        if (menu == 1) {
            playGame(); // ВСЯ игра в одной функции!
        }

    } while (menu != 3);

    cout << "\nПока! Заходи еще!\n";
    system("pause");

    return 0;
}