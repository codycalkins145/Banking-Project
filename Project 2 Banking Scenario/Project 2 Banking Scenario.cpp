#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <sstream>
using namespace std;

class Banking {
    private:
        double initialInvestmentAmount; //
        double monthlyDeposit;          // Private class variables
        double annualInterest;          //
        int numberOfYears;              //
        // Private class function
        void CalcYearInterest(double initialAmount, double& interestAmount, double& finalAmount); 

    public:
        bool UserInputandValidation(void); //
        void DisplayNoMonthly(void);       // Public class functions
        void DisplayWithMonthly(void);     //

};

// The following function is used to determine the final amount and interest amount 
// for the year when monthly payments are included
void Banking::CalcYearInterest(double initialAmount, double& interestAmount, double& finalAmount) { 
    interestAmount = 0.0;
    
    if (finalAmount < initialAmount) { // Only assigns finalAmount with initialAmount's 
        finalAmount = initialAmount;   // value if it has not been assigned already
    }
    
    for (int month = 0; month < 12; month++) { // Loops 12 times to account for months in a year
        finalAmount += monthlyDeposit; // Adds the monthly deposit to the final amount
        double monthlyInterestAmount = finalAmount * ((annualInterest / 100.0) / 12.0); // Calculating monthly interest
        finalAmount += monthlyInterestAmount; // Adding monthly interest to final amount
        interestAmount += monthlyInterestAmount; // Increases interest amount for each month, up to 12
    }
    
    
}

bool Banking::UserInputandValidation() { // Recieves user input
    // The following block is for formatting the header of the input menu
    for (int i = 0; i < 34; i++) {
        cout << "*";
    }
    cout << endl;
    cout << right << setw(10) << setfill('*') << "*" << " Data Input " 
         << setw(12) << "*" << endl;
    // The following block is for receiving user input for relevant data
    cout << "Initial Investment Amount: ";
    cin >> initialInvestmentAmount;
    cout << "Monthly Deposit: ";
    cin >> monthlyDeposit;
    cout << "Annual Interest: ";
    cin >> annualInterest;
    cout << "Number of years: ";
    cin >> numberOfYears;
    cout << "Press any key to continue...";

    while (!_kbhit()) { // Loop continues as long as a key has not been pressed
        continue;
    }
    _getch(); // Stores input so that it won't show up in next input request

    cout << endl; 

    return 0;
}

void Banking::DisplayNoMonthly() { // Displays yearly investment balances without monthly payments
    double finalAmount = initialInvestmentAmount;
    double interestValue = annualInterest / 100.0;
    double interestAmount; // This variable is used to store overall interest so interestValue remains unchanged
    stringstream stream; // These three variables are used to convert int amounts to strings
    string final;        // for formatting purposes
    string interest;     // 

    // The following block is for formatting the header of the output table
    cout << right << setw(58) << setfill(' ') 
         << "Balance and Interest Without Additional Monthly Deposits" << endl;
    for (int i = 0; i < 60; i++) {
        cout << "=";
    }
    cout << endl;
    cout << right << setw(6) << "Year" << setw(22) << "Year End Balance" 
         << setw(30) << "Year End Earned Interest" << endl;
    for (int i = 0; i < 60; i++) {
        cout << "-";
    }
    cout << endl;

    // This loop displays balances of each year for the number of years specified
    for (int i = 1; i <= numberOfYears; i++) { 
        interestAmount = interestValue * finalAmount; // Getting interest value for the final amount
        finalAmount += interestAmount; // Adding interest to the final amount

        stream << fixed << setprecision(2) << finalAmount; // Sets the precision for the final amount as a string
        final = "$" + stream.str(); // Assigns final amount string prepended with dollar sign to string variable
        stream.str(" "); // Clears stringstream variable for next set of formatting
        // The below block is the same as above, but for interest amount
        stream << fixed << setprecision(2) << interestAmount;
        interest = "$" + stream.str();
        stream.str(" ");
        // Formatting and outputting values for the table
        cout << right << setw(6) << i << setw(22) << final
             << setw(30) << interest << endl << endl << endl;
        
    }
    
}

void Banking::DisplayWithMonthly() { // Displays yearly investment balances with monthly payments
    // Much of the formatting and variables in this function are similar to DisplayNoMonthly()
    double finalAmount = 0.0;
    double interestAmount;
    stringstream stream;
    string final;
    string interest;

    cout << right << setw(56) << "Balance and Interest With Additional Monthly Deposits" << endl;
    for (int i = 0; i < 60; i++) {
        cout << "=";
    }
    cout << endl;
    cout << right << setw(6) << "Year" << setw(22) << "Year End Balance"
        << setw(30) << "Year End Earned Interest" << endl;
    for (int i = 0; i < 60; i++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 1; i <= numberOfYears; i++) { 
        // Calling CalcYearInterest to output balances with monthly payments
        CalcYearInterest(initialInvestmentAmount, interestAmount, finalAmount);

        stream << fixed << setprecision(2) << finalAmount;
        final = "$" + stream.str();
        stream.str(" ");

        stream << fixed << setprecision(2) << interestAmount;
        interest = "$" + stream.str();
        stream.str(" ");

        cout << right << setw(6) << i << setw(22) << final
             << setw(30) << interest << endl << endl << endl;
    }

}

int main() {
    Banking bankApp; // Object needed to call Banking class functions
    char exeConf = 'Y'; // Initializing program exit variable to 'Y' to start loop

    while (exeConf != 'N') { // Loop continues as long as user wants to keep inputting values
        bankApp.UserInputandValidation(); //
        bankApp.DisplayNoMonthly();       // Calling Banking class functions
        bankApp.DisplayWithMonthly();     //
        // Prompts the user with continuation dialogue
        cout << "Would you like to try different values? (Y/y or N/n): ";
        cin >> exeConf;
        exeConf = toupper(exeConf); // Sets input to uppercase so loop can exit properly

        for (int i = 0; i < 40; ++i) { // Clearing screen by outputting 40 new lines
            cout << endl;
        }
    }

    return 0;
}