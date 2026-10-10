#pragma once
#include <string>

using namespace std;

class Account {
public:
    class Money {
    private:
        int n500, n200, n100, n50, n20, n10, n5, n2, n1;
        int m50, m25, m10, m5, m2, m1;

        void distributeFromTotal(double totalAmount);

    public:
        double getTotal() const;

        bool Init(double amount);
        void Read();
        void Display() const;
        string toString() const;

        Money add(const Money& other) const;
        Money sub(const Money& other) const;
        double div(const Money& other) const;
        Money div(double scalar) const;
        Money mul(double scalar) const;

        bool isEqual(const Money& other) const;
        bool isGreater(const Money& other) const;
        bool isLess(const Money& other) const;
    };

private:
    string surname;
    unsigned int nomer;
    double percent;
    Money summa; 

public:
    void change_owner(string newOwner);
    bool zabraty_money(Money amount);
    void put_money(Money amount);
    void calculate_percent();
    double to_dolar(double exchange) const;
    double to_euro(double exchange) const;
    string toString() const;

    string getSurname() const { return surname; }
    unsigned int getNomer() const { return nomer; }
    double getPercent() const { return percent; }
    Money getSumma() const { return summa; }

    bool setSurname(string value);
    bool setNomer(unsigned int value);
    bool setPercent(double value);
    bool setSumma(Money value);

    bool Init(string surname, unsigned int nomer, double percent, Money summa);
    void Read();
    void Display() const;
};

Account makeAccount(string o, unsigned int nomer, double percent, Account::Money summa);