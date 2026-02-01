#include <iostream>
#include <windows.h>
#include "game.h"

using namespace std;

void showRules() {
    system("cls");
    cout << "ПРАВИЛА:\n\n";
    cout << "1. На поле 4x4 лежат 16 карточек\n";
    cout << "2. Карточки с одинаковыми числами - это пары\n";
    cout << "3. Открываешь две карточки за ход\n";
    cout << "4. Если совпали - остаются открытыми\n";
    cout << "5. Если нет - закрываются обратно\n";
    cout << "6. Надо найти все 8 пар\n\n";
    system("pause");
}