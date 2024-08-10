#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

#include "Transaction.cpp"

using namespace std;

// string formatRupiah(int num)
// {
//     string delimiter = ".";
//     string output = to_string(num);
//     int inspost = output.length() - 3;
//     while (inspost > 0)
//     {
//         output.insert(inspost, delimiter);
//         inspost -= 3;
//     }
//     return "Rp." + output + ",00";
// }

class RentalCar
{
    vector<Car *> carList;
    vector<Transaction> transactionList;

public:
    ~RentalCar()
    {
        for (Car *car : carList)
        {
            delete car;
        }
    }

    void addNewCar()
    {
        string name = "tst", type = "SUV";
        int year = 2020;
        double pricePerDay = 90000;
        bool typeValid = false;

        // Loop until valid inputs are provided
        while (true)
        {
            // Input Name
            cout << "Enter car name: ";
            cin >> name;

            // Input Type
            while (!typeValid)
            {
                cout << "Enter car type (Sedan, SUV, Minivan): ";
                cin >> type;
                for (int i = 0; i < type.length(); i++)
                {
                    type[i] = tolower(type[i]);
                }

                if (type == "sedan" || type == "suv" || type == "minivan")
                {
                    typeValid = true;
                    if (type == "suv")
                    {
                        for (int j = 0; j < type.length(); j++)
                        {
                            type[j] = toupper(type[j]);
                        }
                    }
                    else
                    {
                        type[0] = toupper(type[0]);
                    }
                }
                else
                {
                    cout << "Invalid input. Please enter Sedan, SUV, or Minivan.\n";
                }
            }

            // Input Year
            cout << "Enter car year ";
            cin >> year;

            // Input price
            cout << "Enter rent price per day: ";
            if (cin >> pricePerDay)
            {
                // Check if inputs are valid
                if (!name.empty() && !type.empty() && year > 0 && pricePerDay > 0)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please ensure that car name is not empty, car type is a string, and the number of price is positive.\n";
                }
            }
            else
            {
                // Clear input buffer if invalid input is encountered
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number.\n";
            }
        }

        insertCar(type, name, year, pricePerDay, true);
        writeCarData();

        return;
    }

    void insertCar(string type, string name, int year, double pricePerDay, bool available)
    {
        Car *car;

        // TODO create factory method
        if (type == "Sedan")
        {
            car = new Sedan(name, year, pricePerDay, available);
        }
        else if (type == "SUV")
        {
            car = new SUV(name, year, pricePerDay, available);
        }
        else if (type == "Minivan")
        {
            car = new Minivan(name, year, pricePerDay, available);
        }
        carList.push_back(car);
    }

    void addTransaction()
    {
        string customerName, carName;
        int rentDuration;
        Car *carRented;
        bool carAvailable = false;

        while (true)
        {
            cout << "Enter car that you want to rent: ";
            cin >> carName;

            for (Car *car : carList)
            {
                cout << "carName : " << car->getName() << endl;
                cout << "car find: " << carName << endl;
                cout << "isAvailable : " << car->isAvailable() << endl;
                if (car->getName() == carName && car->isAvailable())
                {
                    carRented = car;
                    carAvailable = true;
                    break;
                }
            }
            if (!carAvailable)
            {
                cout << "Car is not available.\n";
                return;
            }

            cout << "Enter your name: ";
            cin >> customerName;

            cout << "Enter duration: ";
            if (cin >> rentDuration)
            {
                // Check if inputs are valid
                if (!carName.empty() && !customerName.empty() && rentDuration > 0)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please ensure that car name is not empty, customer name is a string, and the rent duration is positive.\n";
                }
            }
            else
            {
                // Clear input buffer if invalid input is encountered
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number.\n";
            }
        }

        Transaction transaction(customerName, carRented, rentDuration);
        transactionList.push_back(transaction);
    }

    void printTransactionList() const
    {
        cout << '|' << setw(10) << "Name" << '|' << setw(10) << "Car Name" << '|' << setw(10) << "Duration" << '|' << endl;
        cout << "----------------------------------" << endl;
        for (const Transaction transaction : transactionList)
        {
            cout << '|' << setw(10) << transaction.getCustomerName() << '|' << setw(10) << transaction.getCarName() << '|' << setw(10) << transaction.getDuration() << '|' << endl;
        }
    }

    void readCarData()
    {
        ifstream file("car.txt");
        if (!file)
        {
            cerr << "File car.txt can't be opened!\n";
            return;
        }

        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (line.empty())
                    continue; // Skip empty lines

                std::stringstream ss(line);
                string name, type;
                int year;
                double pricePerDay;
                bool available;

                // Assuming the fields are separated by commas
                std::string field;
                int fieldCount = 0;
                while (std::getline(ss, field, ','))
                {
                    if (fieldCount == 0)
                        name = field;
                    else if (fieldCount == 1)
                        type = string(field);
                    else if (fieldCount == 2)
                        year = std::stoi(field);
                    else if (fieldCount == 3)
                        pricePerDay = std::stod(field);
                    else if (fieldCount == 4)
                        available = stoi(field);
                    fieldCount++;
                }
                insertCar(type, name, year, pricePerDay, available);
            }
            file.close();
        }
    }

    void writeCarData() const
    {
        ofstream file("car.txt");
        if (!file)
        {
            cerr << "File car.txt can't be opened!\n";
            return;
        }

        if (file.is_open())
        {
            for (int i = 0; i < carList.size(); i++)
            {
                file << carList[i]->getName() << "," << carList[i]->getType() << "," << carList[i]->getYear() << "," << carList[i]->getPricePerDay() << "," << carList[i]->isAvailable() << "\n";
            }
            file.close();
        }
        else
            cout << "File opening is fail.";
    }

    void findCar(string carName) const
    {
        for (const Car *car : carList)
        {
            if (car->getName() == carName)
            {
                cout << "Name Car: " << car->getName() << "\n"
                     << "Type: " << car->getType() << "\n"
                     << "Year: " << car->getYear() << "\n"
                     << "Rent Price per day: " << car->getPricePerDay() << "\n"
                     << "Status: " << (car->isAvailable() ? "Available" : "Unavailable") << "\n"
                     << "--------------------------\n";
            }
        }
    }

    void sortCarByName()
    {
        sort(carList.begin(), carList.end(), [](Car *a, Car *b)
             { return a->getName() < b->getName(); });
    }

    void sortCarByYear()
    {
        sort(carList.begin(), carList.end(), [](Car *a, Car *b)
             {
                 return b->getYear() < a->getYear(); // Descending
             });
    }

    void printCarList() const
    {
        cout << '|' << setw(10) << "Car Name" << '|' << setw(10) << "Type" << '|' << setw(10) << "Year" << '|' << setw(20) << "Rent Price" << "|" << setw(15) << "Status" << '|' << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        for (const Car *car : carList)
        {
            cout << '|' << setw(10) << car->getName() << '|' << setw(10) << car->getType() << '|' << setw(10) << car->getYear() << '|' << setw(20) << car->getPricePerDay() << "|" << setw(15) << (car->isAvailable() ? "Available" : "Unavailable") << '|' << endl;
        }
    }
};