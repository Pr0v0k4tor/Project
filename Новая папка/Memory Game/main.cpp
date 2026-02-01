#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include "game.h"

using namespace std;
// Изменение цвета в консоли 
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
// Установка цвета в консоли 
void setColor(int k) {
    SetConsoleTextAttribute(h, k);
}

int main() {
    srand((unsigned)time(0)); //генератор случайных цифр
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
            showRules();
            continue;
        }

        if (menu == 1) {
            // ДИНАМИЧЕСКИЕ МАССИВЫ ДЛЯ МАТРИЦЫ 4x4 
            int total = 16;

            // Динамическое выделение памяти для массива карточек
            int* cards = new int[total];
            // Динамическое выделение памяти для массива состояний
            bool* opened = new bool[total];

            // Инициализация: все карточки закрыты
            for (int i = 0; i < total; i++) {
                opened[i] = false;
            }

            // Заполнение пар чисел: 1,1
            for (int i = 0; i < total / 2; i++) {
                cards[i * 2] = i + 1;      // Первая карточка пары
                cards[i * 2 + 1] = i + 1;  // Вторая карточка пары
            }

            // Перемешивание карточек 
            for (int i = 0; i < 100; i++) {
                int a = rand() % total;
                int b = rand() % total;
                int temp = cards[a];
                cards[a] = cards[b];
                cards[b] = temp;
            }

            int errors = 0;  // Счетчик ошибок
            int tries = 0;   // Счетчик попыток
            time_t start_time = time(NULL); // Запуск время 

            while (true) {
                // Проверка, все ли карточки открыты
                bool allOpened = true;
                for (int i = 0; i < total; i++) {
                    if (!opened[i]) {
                        allOpened = false;
                        break;
                    }
                }
                if (allOpened) break; // Если все открыты - победа

                system("cls");
                cout << "ИГРАЕМ! Ошибок: " << errors << "\n\n";

                //ПРЕОБРАЗОВАНИЕ В МАТРИЦУ 4x4 
                for (int i = 0; i < total; i++) {
                    if (opened[i]) {
                        setColor(2);
                        cout << "[" << setw(2) << right << cards[i] << "]";
                    }
                    else {
                        setColor(7);
                        cout << "[" << setw(2) << right << i + 1 << "]";
                    }
                    setColor(7);

                    cout << "  "; // Отступ между карточками

                    // Каждые 4 элемента - новая строка матрицы
                    if ((i + 1) % 4 == 0) {
                        cout << endl << endl;
                    }
                }

                // Ввод первой карточки
                int first;
                cout << "\nКакую карту открыть? (1-16): ";
                cin >> first;

                if (first < 1 || first > 16) {
                    cout << "Неверный номер!";
                    Sleep(1000);
                    continue;
                }

                if (opened[first - 1]) {
                    cout << "Уже открыта!";
                    Sleep(1000);
                    continue;
                }

                // Показ с выделенной первой карточкой
                system("cls");
                cout << "Открыли карту " << first << ":\n\n";

                for (int i = 0; i < total; i++) {
                    if (i == first - 1) {
                        setColor(14); // Желтый - выбранная карточка
                        cout << "[" << setw(2) << right << cards[i] << "]";
                    }
                    else if (opened[i]) {
                        setColor(2);
                        cout << "[" << setw(2) << right << cards[i] << "]";
                    }
                    else {
                        setColor(7);
                        cout << "[" << setw(2) << right << i + 1 << "]";
                    }
                    setColor(7);

                    cout << "  ";

                    if ((i + 1) % 4 == 0) {
                        cout << endl << endl;
                    }
                }

                // Ввод второй карточки
                int second;
                cout << "\nКакую карту открыть второй? (1-16): ";
                cin >> second;

                if (second < 1 || second > 16) {
                    cout << "Неверный номер!";
                    Sleep(1000);
                    continue;
                }

                if (second == first) {
                    cout << "Это та же карта!";
                    Sleep(1000);
                    continue;
                }

                if (opened[second - 1]) {
                    cout << "Уже открыта!";
                    Sleep(1000);
                    continue;
                }

                tries++; // Увеличиваем счетчик ходов

                // Проверка совпадения
                system("cls");
                cout << "Результат:\n\n";

                if (cards[first - 1] == cards[second - 1]) {
                    cout << "УРА! Карты совпали!\n\n";
                    opened[first - 1] = true;  // Отмечаем как открытые
                    opened[second - 1] = true;
                    Beep(800, 300);
                }
                else {
                    cout << "УПС! Карты разные...\n\n";
                    errors++; // Увеличиваем счетчик ошибок
                    Beep(300, 500);
                }

                // Показ результата с подсветкой
                for (int i = 0; i < total; i++) {
                    if (i == first - 1 || i == second - 1) {
                        if (cards[first - 1] == cards[second - 1]) {
                            setColor(10);
                        }
                        else {
                            setColor(12);
                        }
                        cout << "[" << setw(2) << right << cards[i] << "]";
                    }
                    else if (opened[i]) {
                        setColor(2);
                        cout << "[" << setw(2) << right << cards[i] << "]";
                    }
                    else {
                        setColor(7);
                        cout << "[" << setw(2) << right << i + 1 << "]";
                    }
                    setColor(7);

                    cout << "  ";

                    if ((i + 1) % 4 == 0) {
                        cout << endl << endl;
                    }
                }

                Sleep(2000); // Пауза 2 секунды
            }

            time_t end_time = time(NULL);
            int game_time = (int)(end_time - start_time);

            // Вывод результатов
            system("cls");
            cout << "\n";
            cout << "   ВЫ ВЫИГРАЛИ!\n";
            cout << "\n\n";

            cout << "Ваш результат:\n";
            cout << "Ходов: " << tries << endl;
            cout << "Ошибок: " << errors << endl;
            cout << "Время: " << game_time << " сек.\n\n";

            // Оценка игры
            if (errors == 0) {
                cout << "ОТЛИЧНО! Идеальная игра!\n";
            }
            else if (errors <= 3) {
                cout << "ХОРОШО! Почти без ошибок.\n";
            }
            else if (errors <= 6) {
                cout << "НЕПЛОХО! Можно лучше.\n";
            }
            else {
                cout << "ПОТРЕНИРУЙТЕСЬ ЕЩЕ!\n";
            }
            cout << endl;

            // Освобождение динамической памяти
            delete[] cards;
            delete[] opened;

            system("pause");
        }

    } while (menu != 3);

    cout << "\nПока! Заходи еще!\n";
    system("pause");

    return 0;
}