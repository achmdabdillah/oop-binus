#include <string>

using namespace std;

struct Car
{
protected:
    string name;
    int year;
    double pricePerDay;
    bool available;

public:
    Car(string name, int year, double pricePerDay, bool available)
        : name(name), year(year), pricePerDay(pricePerDay), available(available) {}

    virtual double getRentPrice(int durasi) const
    {
        return pricePerDay * durasi;
    }

    string getName() const { return name; }
    int getYear() const { return year; }
    double getPricePerDay() const { return pricePerDay; }
    bool isAvailable() const { return available; }
    void setAvailable(bool status) { available = status; }

    virtual string getType() const = 0;

    virtual ~Car() {}
};

class Sedan : public Car
{
public:
    Sedan(string name, int year, double pricePerDay, bool available)
        : Car(name, year, pricePerDay, available) {}

    double getRentPrice(int durasi) const override
    {
        return pricePerDay * durasi;
    }

    string getType() const override
    {
        return "Sedan";
    }
};

class SUV : public Car
{
public:
    SUV(string name, int year, double pricePerDay, bool available)
        : Car(name, year, pricePerDay, available) {}

    double getRentPrice(int durasi) const override
    {
        return pricePerDay * durasi * 1.1; // Misal ada surcharge 10%
    }

    string getType() const override
    {
        return "SUV";
    }
};

class Minivan : public Car
{
public:
    Minivan(string name, int year, double pricePerDay, bool available)
        : Car(name, year, pricePerDay, available) {}

    double getRentPrice(int durasi) const override
    {
        return pricePerDay * durasi * 1.05; // Misal ada surcharge 5%
    }

    string getType() const override
    {
        return "Minivan";
    }
};
