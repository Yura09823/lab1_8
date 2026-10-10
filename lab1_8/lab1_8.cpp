#include <iostream>
#include "Account.h"
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Демонстрація створення об'єкта через функцію makeAccount" << endl;

    Account::Money initial_money;
    initial_money.Init(1500.75);

    Account acc1 = makeAccount("Іваненко", 123456, 5.0, initial_money);
    acc1.Display();

    cout << "\nДемонстрація методу toString()" << endl;
    cout << acc1.toString() << endl;

    cout << "\nДемонстрація поповнення рахунку" << endl;
    Account::Money deposit;
    deposit.Init(250.50);
    acc1.put_money(deposit);
    acc1.Display();

    cout << "\nДемонстрація зняття коштів" << endl;
    Account::Money withdraw;
    withdraw.Init(300.00);
    if (acc1.zabraty_money(withdraw)) {
        cout << "Гроші успішно знято." << endl;
    }
    else {
        cout << "Помилка: недостатньо коштів." << endl;
    }
    acc1.Display();

    cout << "\nДемонстрація нарахування відсотків" << endl;
    acc1.calculate_percent();
    acc1.Display();

    cout << "\nДемонстрація конвертації валют" << endl;
    cout << "Сума в доларах (курс 41.5): " << acc1.to_dolar(41.5) << endl;
    cout << "Сума в євро (курс 45.2): " << acc1.to_euro(45.2) << endl;

    cout << "\nДемонстрація зміни власника" << endl;
    acc1.change_owner("Петренко");
    acc1.Display();

    cout << "\nДемонстрація масиву об'єктів" << endl;

    Account accounts[2] = {
        makeAccount("Козак", 111111, 2.0, initial_money),
        makeAccount("Шевченко", 222222, 3.5, deposit)
    };

    for (int i = 0; i < 2; i++) {
        cout << "\nРахунок " << i + 1 << ":" << endl;
        accounts[i].Display();
    }

    cout << "\nВведення з клавіатури" << endl;

    Account userAcc;
    userAcc.Read();

    cout << "\n Виведення введеного рахунку" << endl;
    userAcc.Display();

    return 0;
}