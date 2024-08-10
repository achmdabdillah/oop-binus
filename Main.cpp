#include <iostream>
#include "RentalCar.cpp"

using namespace std;

// TODO save transaction on txt files
// TODO create y/n option to payment
// TODO revamp struct

void showMenu()
{
    cout << "======= CLI Menu =======" << endl;
    cout << "1. Insert car" << endl;
    cout << "2. Insert transaction" << endl;
    cout << "3. Show available car" << endl;
    cout << "4. Show Transaction List" << endl;
    cout << "5. Find car by name" << endl;
    cout << "6. Sort car by name" << endl;
    cout << "7. Sort car by year" << endl;
    cout << "8. Show all car" << endl;
    cout << "9. Exit" << endl;
    cout << "========================" << endl;
}

int main()
{
    int choice;
    string name;
    RentalCar rental;
    rental.readCarData();
    do
    {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            rental.addNewCar();
            break;
        case 2:
            rental.addTransaction();
            break;
        case 3:
            rental.printCarList(true);
            break;
        case 4:
            rental.printTransactionList();
            break;
        case 5:
            cout << "Enter car name: ";
            cin >> name;
            rental.findCar(name);
            break;
        case 6:
            rental.sortCarByName();
            break;
        case 7:
            rental.sortCarByYear();
            break;
        case 8:
            rental.printCarList(false);
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }

        cout << endl; // Add a blank line for better readability
    } while (choice != 9);

    return 0;
}