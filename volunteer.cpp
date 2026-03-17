#include <iostream>
#include <string>
using namespace std;

class Volunteer
{
private:
    string fullName;      // ФИО
    int age;              // возраст
    string direction;     // направление деятельности
    int workedHours;      // количество отработанных часов

public:
    // Конструктор по умолчанию
    Volunteer()
    {
        fullName = "Не указано";
        age = 0;
        direction = "Не указано";
        workedHours = 0;
    }

    // Конструктор с параметрами
    Volunteer(string f, int a, string d, int h)
    {
        setFullName(f);
        setAge(a);
        setDirection(d);
        setWorkedHours(h);
    }

    // Деструктор
    ~Volunteer()
    {
        cout << "Объект Volunteer (" << fullName << ") уничтожен" << endl;
    }

    // Геттеры
    string getFullName() const
    {
        return fullName;
    }

    int getAge() const
    {
        return age;
    }

    string getDirection() const
    {
        return direction;
    }

    int getWorkedHours() const
    {
        return workedHours;
    }

    // Сеттеры с валидацией
    void setFullName(string f)
    {
        if (f != "")
            fullName = f;
        else
        {
            cout << "Ошибка: ФИО не может быть пустым" << endl;
            fullName = "Не указано";
        }
    }

    void setAge(int a)
    {
        if (a >= 14 && a <= 100)
            age = a;
        else
        {
            cout << "Ошибка: некорректный возраст" << endl;
            age = 18;
        }
    }

    void setDirection(string d)
    {
        if (d != "")
            direction = d;
        else
        {
            cout << "Ошибка: направление деятельности не может быть пустым" << endl;
            direction = "Не указано";
        }
    }

    void setWorkedHours(int h)
    {
        if (h >= 0)
            workedHours = h;
        else
        {
            cout << "Ошибка: количество часов не может быть отрицательным" << endl;
            workedHours = 0;
        }
    }

    // Метод поведения 1: добавление часов
    void addWorkedHours(int h)
    {
        if (h > 0)
        {
            workedHours += h;
            cout << "Добавлено часов: " << h << endl;
        }
        else
            cout << "Ошибка: можно добавлять только положительное количество часов" << endl;
    }

    // Метод поведения 2: проверка возможности участия
    bool canParticipate(int minAge, int requiredHours) const
    {
        return (age >= minAge && workedHours >= requiredHours);
    }

    // Метод поведения 3: уменьшение часов при участии в мероприятии
    void spendHours(int h)
    {
        if (h <= 0)
            cout << "Ошибка: количество часов должно быть положительным" << endl;
        else if (h > workedHours)
            cout << "Ошибка: недостаточно отработанных часов" << endl;
        else
        {
            workedHours -= h;
            cout << "Списано часов: " << h << endl;
        }
    }

    // Вывод полной информации
    void printInfo() const
    {
        cout << "ФИО: " << fullName << endl;
        cout << "Возраст: " << age << endl;
        cout << "Направление деятельности: " << direction << endl;
        cout << "Количество отработанных часов: " << workedHours << endl;
        cout << "----------------------------------------" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Rus");

    // 1 объект: конструктор по умолчанию
    Volunteer v1;

    cout << "Объект v1 после создания:" << endl;
    v1.printInfo();

    // Вызов сеттеров
    v1.setFullName("Иванов Иван");
    v1.setAge(19);
    v1.setDirection("Экологические акции");
    v1.setWorkedHours(12);

    cout << "Объект v1 после изменения данных:" << endl;
    v1.printInfo();

    // Вызов геттеров
    cout << "Проверка геттеров для v1:" << endl;
    cout << "ФИО: " << v1.getFullName() << endl;
    cout << "Возраст: " << v1.getAge() << endl;
    cout << "Направление: " << v1.getDirection() << endl;
    cout << "Часы: " << v1.getWorkedHours() << endl;
    cout << endl;

    // Вызов методов поведения
    v1.addWorkedHours(5);
    v1.spendHours(3);

    if (v1.canParticipate(18, 10))
        cout << "v1 может участвовать в мероприятии" << endl;
    else
        cout << "v1 не может участвовать в мероприятии" << endl;

    cout << endl;

    // 2 объект: конструктор с параметрами
    Volunteer v2("Петров Петр", 16, "Социальная помощь", 8);

    cout << "Объект v2 после создания:" << endl;
    v2.printInfo();

    // Демонстрация валидации
    v2.setFullName("");
    v2.setAge(-5);
    v2.setDirection("");
    v2.setWorkedHours(-10);

    // Некорректные вызовы методов
    v2.addWorkedHours(-2);
    v2.spendHours(100);

    if (v2.canParticipate(18, 10))
        cout << "v2 может участвовать в мероприятии" << endl;
    else
        cout << "v2 не может участвовать в мероприятии" << endl;

    cout << "Итоговое состояние v2:" << endl;
    v2.printInfo();

    return 0;
}
