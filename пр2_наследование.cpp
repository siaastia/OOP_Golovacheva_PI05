#include <iostream>
#include <string>
using namespace std;

// Базовый класс
class Volunteer
{
protected:
    string fullName;      // ФИО
    int age;              // возраст
    string direction;     // направление
    int workedHours;      // отработанных часов

public:
    // Конструктор с параметрами
    Volunteer(string fullNameValue, int ageValue, string directionValue, int workedHoursValue)
    {
        setFullName(fullNameValue);
        setAge(ageValue);
        setDirection(directionValue);
        setWorkedHours(workedHoursValue);
    }

    // Виртуальный деструктор
    virtual ~Volunteer()
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

    // Сеттеры
    void setFullName(string newFullName)
    {
        if (newFullName != "")
            fullName = newFullName;
        else
        {
            cout << "Ошибка: ФИО не может быть пустым" << endl;
            fullName = "Не указано";
        }
    }

    void setAge(int newAge)
    {
        if (newAge >= 14 && newAge <= 100)
            age = newAge;
        else
        {
            cout << "Ошибка: некорректный возраст" << endl;
            age = 18;
        }
    }

    void setDirection(string newDirection)
    {
        if (newDirection != "")
            direction = newDirection;
        else
        {
            cout << "Ошибка: направление не может быть пустым" << endl;
            direction = "Не указано";
        }
    }

    void setWorkedHours(int newWorkedHours)
    {
        if (newWorkedHours >= 0)
            workedHours = newWorkedHours;
        else
        {
            cout << "Ошибка: количество часов не может быть отрицательным" << endl;
            workedHours = 0;
        }
    }

    // Обычный метод, общий для всех потомков
    void addWorkedHours(int hoursToAdd)
    {
        if (hoursToAdd > 0)
        {
            workedHours += hoursToAdd;
            cout << "Добавлено часов: " << hoursToAdd << endl;
        }
        else
            cout << "Ошибка: можно добавлять только положительное количество часов" << endl;
    }

    // Чисто виртуальные методы
    virtual double calcContribution() const = 0;
    virtual bool canParticipate(int requiredAge) const = 0;

    // Виртуальный метод printInfo
    virtual void printInfo() const
    {
        cout << "ФИО: " << fullName << endl;
        cout << "Возраст: " << age << endl;
        cout << "Направление: " << direction << endl;
        cout << "Отработанных часов: " << workedHours << endl;
    }
};

// Производный класс 1
class EventVolunteer : public Volunteer
{
private:
    string eventName;   // название мероприятия
    string role;        // роль (организатор / помощник)

public:
    EventVolunteer(string fullNameValue, int ageValue, string directionValue, int workedHoursValue,
        string eventNameValue, string roleValue)
        : Volunteer(fullNameValue, ageValue, directionValue, workedHoursValue)
    {
        if (eventNameValue != "")
            eventName = eventNameValue;
        else
        {
            cout << "Ошибка: название мероприятия не может быть пустым" << endl;
            eventName = "Не указано";
        }

        if (roleValue == "организатор" || roleValue == "помощник")
            role = roleValue;
        else
        {
            cout << "Ошибка: роль должна быть 'организатор' или 'помощник'" << endl;
            role = "помощник";
        }
    }

    ~EventVolunteer() override
    {
        cout << "Объект EventVolunteer (" << fullName << ") уничтожен" << endl;
    }

    // Собственный метод
    int calcBonusHoursByRole() const
    {
        if (role == "организатор")
            return 10;
        else
            return 5;
    }

    // Переопределение виртуального метода
    double calcContribution() const override
    {
        return workedHours + calcBonusHoursByRole();
    }

    // Переопределение виртуального метода
    bool canParticipate(int requiredAge) const override
    {
        return (age >= requiredAge && workedHours >= 5);
    }

    // Переопределение printInfo
    void printInfo() const override
    {
        Volunteer::printInfo();
        cout << "Название мероприятия: " << eventName << endl;
        cout << "Роль: " << role << endl;
        cout << "Бонусные часы по роли: " << calcBonusHoursByRole() << endl;
        cout << "----------------------------------------" << endl;
    }
};

// Производный класс 2
class RegularVolunteer : public Volunteer
{
private:
    string workSchedule;    // график работы
    string specialization;  // специализация

public:
    RegularVolunteer(string fullNameValue, int ageValue, string directionValue, int workedHoursValue,
        string workScheduleValue, string specializationValue)
        : Volunteer(fullNameValue, ageValue, directionValue, workedHoursValue)
    {
        if (workScheduleValue != "")
            workSchedule = workScheduleValue;
        else
        {
            cout << "Ошибка: график работы не может быть пустым" << endl;
            workSchedule = "Не указано";
        }

        if (specializationValue != "")
            specialization = specializationValue;
        else
        {
            cout << "Ошибка: специализация не может быть пустой" << endl;
            specialization = "Не указано";
        }
    }

    ~RegularVolunteer() override
    {
        cout << "Объект RegularVolunteer (" << fullName << ") уничтожен" << endl;
    }

    // Собственный метод
    int calcPlannedHoursPerMonth() const
    {
        if (workSchedule == "ежедневно")
            return 80;
        else if (workSchedule == "по будням")
            return 60;
        else if (workSchedule == "по выходным")
            return 32;
        else
            return 40;
    }

    // Переопределение виртуального метода
    double calcContribution() const override
    {
        return workedHours * 1.2;
    }

    // Переопределение виртуального метода
    bool canParticipate(int requiredAge) const override
    {
        return (age >= requiredAge);
    }

    // Переопределение printInfo
    void printInfo() const override
    {
        Volunteer::printInfo();
        cout << "График работы: " << workSchedule << endl;
        cout << "Специализация: " << specialization << endl;
        cout << "Плановые часы на месяц: " << calcPlannedHoursPerMonth() << endl;
        cout << "----------------------------------------" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Rus");

    // Массив указателей на базовый класс
    Volunteer* volunteers[4];

    // Заполнение массива объектами разных производных классов
    volunteers[0] = new EventVolunteer(
        "Иванов Иван", 19, "Экологические акции", 12,
        "Чистый город", "организатор"
    );

    volunteers[1] = new RegularVolunteer(
        "Петров Петр", 20, "Социальная помощь", 10,
        "по выходным", "работа с пожилыми"
    );

    volunteers[2] = new EventVolunteer(
        "Сидорова Анна", 17, "Культурные мероприятия", 8,
        "Фестиваль", "помощник"
    );

    volunteers[3] = new RegularVolunteer(
        "Кузнецов Максим", 22, "Медицина", 15,
        "по будням", "первая помощь"
    );

    cout << "===== Информация о волонтерах =====" << endl;
    for (int i = 0; i < 4; i++)
    {
        volunteers[i]->printInfo();
    }

    cout << endl;
    cout << "===== Расчет вклада волонтеров =====" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << volunteers[i]->getFullName() << ": "
            << volunteers[i]->calcContribution()
            << " баллов" << endl;
    }

    cout << endl;
    cout << "===== Проверка участия в мероприятии =====" << endl;
    for (int i = 0; i < 4; i++)
    {
        if (volunteers[i]->canParticipate(18))
            cout << volunteers[i]->getFullName() << " может участвовать" << endl;
        else
            cout << volunteers[i]->getFullName() << " не может участвовать" << endl;
    }

    cout << endl;
    cout << "===== Добавление часов =====" << endl;
    for (int i = 0; i < 4; i++)
    {
        volunteers[i]->addWorkedHours(2);
    }

    cout << endl;
    cout << "===== Удаление объектов =====" << endl;
    for (int i = 0; i < 4; i++)
    {
        delete volunteers[i];
    }

    return 0;
}
