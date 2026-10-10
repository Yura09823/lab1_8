#include "Account.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;


void Account::Money::distributeFromTotal(double totalAmount) {
    long totalKopecks = round(totalAmount * 100);

    n500 = totalKopecks / 50000; totalKopecks %= 50000;
    n200 = totalKopecks / 20000; totalKopecks %= 20000;
    n100 = totalKopecks / 10000; totalKopecks %= 10000;
    n50 = totalKopecks / 5000;  totalKopecks %= 5000;
    n20 = totalKopecks / 2000;  totalKopecks %= 2000;
    n10 = totalKopecks / 1000;  totalKopecks %= 1000;
    n5 = totalKopecks / 500;   totalKopecks %= 500;
    n2 = totalKopecks / 200;   totalKopecks %= 200;
    n1 = totalKopecks / 100;   totalKopecks %= 100;

    m50 = totalKopecks / 50;    totalKopecks %= 50;
    m25 = totalKopecks / 25;    totalKopecks %= 25;
    m10 = totalKopecks / 10;    totalKopecks %= 10;
    m5 = totalKopecks / 5;     totalKopecks %= 5;
    m2 = totalKopecks / 2;     totalKopecks %= 2;
    m1 = totalKopecks / 1;     totalKopecks %= 1;
}

double Account::Money::getTotal() const {
    double total = (n500 * 500) + (n200 * 200) + (n100 * 100) + (n50 * 50) +
        (n20 * 20) + (n10 * 10) + (n5 * 5) + (n2 * 2) + (n1 * 1) +
        (m50 * 0.50) + (m25 * 0.25) + (m10 * 0.10) +
        (m5 * 0.05) + (m2 * 0.02) + (m1 * 0.01);
    return total;
}

bool Account::Money::Init(double amount) {
    if (amount < 0) return false;
    distributeFromTotal(amount);
    return true;
}

void Account::Money::Read() {
    double amount;
    do {
        cout << "¬вед≥ть суму: ";
        cin >> amount;
    } while (!Init(amount));
}

void Account::Money::Display() const {
    cout << toString() << endl;
}

string Account::Money::toString() const {
    stringstream sout;
    double total = getTotal();
    long grn = floor(total);
    long kop = round((total - grn) * 100);
    sout << grn << "," << setfill('0') << setw(2) << kop << " грн";
    return sout.str();
}

Account::Money Account::Money::add(const Account::Money& other) const {
    Account::Money result;
    result.Init(this->getTotal() + other.getTotal());
    return result;
}

Account::Money Account::Money::sub(const Account::Money& other) const {
    Account::Money result;
    double diff = this->getTotal() - other.getTotal();
    result.Init(diff >= 0 ? diff : 0);
    return result;
}

double Account::Money::div(const Account::Money& other) const {
    if (other.getTotal() == 0) return 0;
    return this->getTotal() / other.getTotal();
}

Account::Money Account::Money::div(double scalar) const {
    Account::Money result;
    if (scalar > 0) result.Init(this->getTotal() / scalar);
    else result.Init(0);
    return result;
}

Account::Money Account::Money::mul(double scalar) const {
    Account::Money result;
    if (scalar > 0) result.Init(this->getTotal() * scalar);
    else result.Init(0);
    return result;
}

bool Account::Money::isEqual(const Account::Money& other) const { return abs(this->getTotal() - other.getTotal()) < 0.001; }
bool Account::Money::isGreater(const Account::Money& other) const { return this->getTotal() > other.getTotal(); }
bool Account::Money::isLess(const Account::Money& other) const { return this->getTotal() < other.getTotal(); }


bool Account::setSurname(string value) {
    if (!value.empty()) {
        surname = value;
        return true;
    }
    surname = "нев≥домо";
    return false;
}

bool Account::setNomer(unsigned int value) {
    if (value > 0) {
        nomer = value;
        return true;
    }
    else {
        nomer = 0;
        return false;
    }
}

bool Account::setPercent(double value) {
    if (value >= 0.0) {
        percent = value;
        return true;
    }
    else {
        percent = 0.0;
        return false;
    }
}

bool Account::setSumma(Account::Money value) {
    summa = value;
    return true;
}

bool Account::Init(string surname, unsigned int nomer, double percent, Account::Money summa) {
    return setSurname(surname) && setNomer(nomer) && setPercent(percent) && setSumma(summa);
}

void Account::Read() {
    string surname_val;
    int nomer_val;
    double percent_val;
    double amount;

    cout << "surname = "; cin >> surname_val;

    Account::Money initial_sum;
    do {
        cout << "nomer   = "; cin >> nomer_val;
        cout << "percent = "; cin >> percent_val;
        cout << "summa   = "; cin >> amount;
        initial_sum.Init(amount);
    } while (!Init(surname_val, nomer_val, percent_val, initial_sum));
}

void Account::Display() const {
    cout << "surname = " << surname << endl;
    cout << "nomer   = " << nomer << endl;
    cout << "percent = " << percent << "%" << endl;
    cout << "summa   = " << summa.toString() << endl;
}

void Account::change_owner(string newOwner) {
    if (setSurname(newOwner)) {
        cout << "successfully. owner: " << newOwner << endl;
    }
    else {
        cout << "error" << endl;
    }
}

bool Account::zabraty_money(Account::Money amount) {
    if (!summa.isLess(amount) && amount.getTotal() > 0) {
        summa = summa.sub(amount);
        return true;
    }
    return false;
}

void Account::put_money(Account::Money amount) {
    summa = summa.add(amount);
}

void Account::calculate_percent() {
    Account::Money interest = summa.mul(percent / 100.0);
    summa = summa.add(interest);
}

double Account::to_dolar(double exchange) const {
    return summa.getTotal() / exchange;
}

double Account::to_euro(double exchange) const {
    return summa.getTotal() / exchange;
}

string Account::toString() const {
    double total = summa.getTotal();
    int UAH = (int)floor(total);
    int kopecks = (int)round((total - UAH) * 100);

    if (UAH == 0) return "нуль грн. " + to_string(kopecks) + " коп.";

    string ones[] = { "", "одна", "дв≥", "три", "чотири", "п'€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть" };
    string teens[] = { "дес€ть", "одинадц€ть", "дванадц€ть", "тринадц€ть", "чотирнадц€ть", "п'€тнадц€ть", "ш≥стнадц€ть", "с≥мнадц€ть", "в≥с≥мнадц€ть", "дев'€тнадц€ть" };
    string tens[] = { "", "", "двадц€ть", "тридц€ть", "сорок", "п'€тдес€т", "ш≥стдес€т", "с≥мдес€т", "в≥с≥мдес€т", "дев'€носто" };
    string hundreds[] = { "", "сто", "дв≥ст≥", "триста", "чотириста", "п'€тсот", "ш≥стсот", "с≥мсот", "в≥с≥мсот", "дев'€тсот" };

    string result = "";
    int thousands = (UAH / 1000) % 1000;
    int units = UAH % 1000;

    if (thousands > 0) {
        result += hundreds[thousands / 100] + (thousands / 100 > 0 ? " " : "");
        int th_tens = thousands % 100;
        if (th_tens >= 10 && th_tens <= 19) {
            result += teens[th_tens - 10] + " тис€ч ";
        }
        else {
            result += tens[th_tens / 10] + (th_tens / 10 > 0 ? " " : "");
            result += ones[th_tens % 10] + (th_tens % 10 > 0 ? " " : "");
            if (th_tens % 10 == 1) result += "тис€ча ";
            else if (th_tens % 10 >= 2 && th_tens % 10 <= 4) result += "тис€ч≥ ";
            else result += "тис€ч ";
        }
    }

    if (units > 0) {
        result += hundreds[units / 100] + (units / 100 > 0 ? " " : "");
        int un_tens = units % 100;
        if (un_tens >= 10 && un_tens <= 19) {
            result += teens[un_tens - 10] + " ";
        }
        else {
            result += tens[un_tens / 10] + (un_tens / 10 > 0 ? " " : "");
            result += ones[un_tens % 10] + (un_tens % 10 > 0 ? " " : "");
        }
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    stringstream ss;
    ss << result << " грн. " << (kopecks < 10 ? "0" : "") << kopecks << " коп.";
    return ss.str();
}

Account makeAccount(string o, unsigned int nomer, double percent, Account::Money summa) {
    Account acc;
    if (!acc.Init(o, nomer, percent, summa)) {
        cout << "error" << endl;
        exit(1);
    }
    return acc;
}