#include <iostream>

#include "calculator.h"

int main() {
    std::cout << "Hi, I'm here to help you......." << std::endl;
    std::cout << "You can choose any transaction you want to do from this list..\n";
    std::cout << "========================================\n";
    std::cout << "1) deposit\n";
    std::cout << "2) withdrawal\n";
    std::cout << "3) Fee\n";
    std::cout << "4) simpleInterest \n";
    std::cout << "5) compoundInterest \n";
    std::cout << "6) currencyConversion\n";
    std::cout << "========================================\n";
    std::cout << "Please enter your choice: ";

    while(true) {
        std::string out;
        std::string rounding;
        std::string transaction;
        std::string from_currency;
        std::string to_currency;
        int64_t balance; 
        int32_t amount;
        int64_t base;
        uint16_t days; 
        uint16_t years;
        uint16_t day_count_basis;
        uint16_t compounds_per_year;
        float apr; 

        std::cin >> transaction;
        if (transaction == "deposit") {
            std::cout << "please, enter the balance: ";
            std::cin >> balance;
            std::cout << "please, enter the amount: ";
            std::cin >> amount;
            balance = Apply_deposit(balance, amount);  
            std::cout << "Would you like to appear your new balance? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "New balance =  " << balance << std::endl;
            } else {
                //  DO NOTHING
            }         
        } else if (transaction == "withdrawal") {
            std::cout << "please, enter the balance: ";
            std::cin >> balance;
            std::cout << "please, enter the amount: ";
            std::cin >> amount;
            balance = Apply_withdrawal(balance, amount);
            std::cout << "Would you like to appear your new balance? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "New balance =  " << balance << std::endl;
            } else {
                //  DO NOTHING
            }  
        } else if (transaction == "Fee") {
            std::cout << "please, enter the balance: ";
            std::cin >> balance;
            std::cout << "please, enter the amount: ";
            std::cin >> amount;
            balance = Apply_fee(balance, amount);
            std::cout << "Would you like to appear your new balance? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "New balance =  " << balance << std::endl;
            } else {
                //  DO NOTHING
            }  
        } else if (transaction== "simpleInterest") {
            std::cout << "please, enter the base and apr: ";
            std::cin >> base >> apr;
            std::cout << "please, enter the days and day count basis: ";
            std::cin >> days >> day_count_basis;
            std::cout << "please, enter the rounding: ";
            std::cin >> rounding;
            balance = Simple_interest(base, apr, days, day_count_basis, rounding);
            std::cout << "Would you like to appear your interest? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "interest =  " << balance << std::endl;
            } else {
                //  DO NOTHING
            } 
        } else if (transaction == "compoundInterest") {
            std::cout << "please, enter the principal and apr: ";
            std::cin >> base >> apr;
            std::cout << "please, enter the years and compounds peryear: ";
            std::cin >> years >> compounds_per_year;
            std::cout << "please, enter the rounding: ";
            std::cin >> rounding;
            balance = Compound_amount(base, apr, years, compounds_per_year, rounding);
            std::cout << "Would you like to appear your new balance? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "balance =  " << balance << std::endl;
            } else {
                //  DO NOTHING
            } 
        } else if (transaction == "currencyConversion") {
            std::cout << "please, enter the balance: ";
            std::cin >> balance;
            std::cout << "please, enter from currency and to currency: ";
            std::cin >> from_currency >> to_currency;
            std::cout << "please, enter the rounding: ";
            std::cin >> rounding;
            int64_t new_currency = Fx_convert(balance, from_currency, to_currency, rounding);
            std::cout << "Would you like to appear your new currency? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "currency =  " << new_currency << std::endl;
            } else {
                //  DO NOTHING
            } 
        } else {
            std::cout << "Sorry, this process not found...";
            std::cout << "you can choose process from the list\n";
        }
        
        std::cout << "Would you like to perform another transaction? (yes/no): ";
        std::cin >> out;
        if (out == "yes") {
            std::cout << "Please enter your choice: ";
        } else {
            std::cout << "End of transaction......\n";
            return 0;
        }     
    }

}