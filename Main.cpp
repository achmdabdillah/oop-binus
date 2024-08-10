#include <iostream>
#include "RentalCar.cpp"

using namespace std;

// TODO Update car status whenever transaction is made
// TODO show car list sort by name, year,
// TODO save transaction on txt files
// TODO revamp struct
// TODO create y/n option to payment

void showMenu()
{
    cout << "======= CLI Menu =======" << endl;
    cout << "1. Insert car" << endl;
    cout << "2. Insert transaction" << endl;
    cout << "3. Show Car List" << endl;
    cout << "4. Show Transaction List" << endl;
    cout << "5. Find by" << endl;
    cout << "6. Exit" << endl;
    cout << "========================" << endl;
}

int main()
{
    int choice;
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
            rental.printCarList();
            break;
        case 4:
            rental.printTransactionList();
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }

        cout << endl; // Add a blank line for better readability
    } while (choice != 6);

    // rental.addTransaction("Alice", "CarA", 3);
    // rental.addTransaction("Bob", "CarB", 5);

    // rental.printTransactionList();

    // rental.sortCarByName();
    // cout << "Car list after Sorting by Name (Ascending):\n";
    // rental.printCarList();

    // rental.sortCarByYear();
    // cout << "Car list after Sorting by Year (Descending):\n";
    // rental.printCarList();

    // rental.writeCarData();

    return 0;
}