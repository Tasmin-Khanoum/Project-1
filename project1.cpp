#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class FinanceManager {
private:
    double income;
    double expenses;
    double budget;
    double savings;
    const string filename = "finance_data.txt";

public:
    FinanceManager() {
        income = 0.0;
        expenses = 0.0;
        budget = 0.0;
        savings = 0.0;
        loadFromFile();
    }

    void addIncome(double amount) {
        income += amount;
        cout << "Income of $" << fixed << setprecision(2) << amount << " added. Total Income: $" << income << endl;
        saveToFile();
    }

    void addExpense(double amount) {
        if (amount > income - expenses) {
            cout << "Warning: Expense exceeds available balance!" << endl;
        } else {
            expenses += amount;
            cout << "Expense of $" << fixed << setprecision(2) << amount << " added. Total Expenses: $" << expenses << endl;
            saveToFile();
        }
    }

    void setBudget(double amount) {
        budget = amount;
        cout << "Monthly budget set to $" << fixed << setprecision(2) << budget << endl;
        saveToFile();
    }

    void trackSavings() {
        savings = income - expenses;
        cout << "Your savings are $" << fixed << setprecision(2) << savings << endl;
        saveToFile();
    }

    void displaySummary() {
        savings = income - expenses; // Ensure savings is updated before displaying
        cout << "\nFinancial Summary:" << endl;
        cout << "Total Income: $" << fixed << setprecision(2) << income << endl;
        cout << "Total Expenses: $" << fixed << setprecision(2) << expenses << endl;
        cout << "Savings: $" << fixed << setprecision(2) << savings << endl;
        cout << "Budget: $" << fixed << setprecision(2) << budget << endl;
        if (expenses > budget) {
            cout << "Warning: You have exceeded your budget!" << endl;
        } else {
            cout << "You are within your budget." << endl;
        }
    }

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            file << income << " " << expenses << " " << budget << " " << savings;
            file.close();
        } else {
            cout << "Error: Unable to save data to file!" << endl;
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            file >> income >> expenses >> budget >> savings;
            file.close();
        } else {
            cout << "No previous financial data found. Starting fresh." << endl;
        }
    }
};

void showMenu() {
    cout << "\nFinance Manager" << endl;
    cout << "1. Add Income" << endl;
    cout << "2. Add Expense" << endl;
    cout << "3. Set Budget" << endl;
    cout << "4. Track Savings" << endl;
    cout << "5. Display Financial Summary" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    FinanceManager manager;
    int choice;
    double amount;

    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter income amount: $";
                cin >> amount;
                manager.addIncome(amount);
                break;
            case 2:
                cout << "Enter expense amount: $";
                cin >> amount;
                manager.addExpense(amount);
                break;
            case 3:
                cout << "Enter monthly budget amount: $";
                cin >> amount;
                manager.setBudget(amount);
                break;
            case 4:
                manager.trackSavings();
                break;
            case 5:
                manager.displaySummary();
                break;
            case 6:
                cout << "Exiting Finance Manager. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
