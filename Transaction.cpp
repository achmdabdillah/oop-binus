#include <string>
#include "Car.cpp"
#include <iostream>

using namespace std;

class Transaction
{
    string customerName;
    Car *car;
    int rentDuration;
    double totalPrice;

public:
    Transaction(string customerName, Car *car, int rentDuration)
        : customerName(customerName), car(car), rentDuration(rentDuration)
    {
        totalPrice = car->getRentPrice(rentDuration);
        car->setAvailable(false);
    }

    void printTransaction() const
    {
        cout << customerName << car->getName() << rentDuration << totalPrice << "\n";
    }

    string getCarName() const { return car->getName(); }
    string getCustomerName() const { return customerName; }
    int getDuration() const { return rentDuration; }
    int getYearCar() const { return car->getYear(); }
};