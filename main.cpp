//
//  main.cpp
//  paycheck
//
//  Created by Alex Dickinson on 15.02.16.
//  Copyright © 2016 Alex Dickinson. All rights reserved.
//
//  This program calculates a user's monthly paycheck, including deductions, and prints the data to a file.

#include <iostream>
#include <fstream>
#include <iomanip>
using std::cout;
using std::cin;
using std::string;
using std::ofstream;

//This function takes a string and makes sure it only desired characters.
string stringValidator(string desiredChars, string inputMsg);
//This takes a string and makes sure it contains digits and lies between 0 and an upper bound.
double doubleValidator(int bound, string inputMsg);

int main() {
    string lastName;
    string firstName;
    double daysOfWork;
    double hoursPerDay;
    double wage;
    double paycheck;
    double fedDeduction;
    double stateDeduction;
    double otherDeductions;
    
    lastName = stringValidator("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", "last name");
    for(int i = 0; i < lastName.length(); i++){//capitalizes last name.
        lastName[i] = tolower(lastName[i]);
    }
    lastName[0] = toupper(lastName[0]);
    
    firstName = stringValidator("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", "first name");
    for(int i = 0; i < firstName.length(); i++){//capitalizes first name.
        firstName[i] = tolower(firstName[i]);
    }
    firstName[0] = toupper(firstName[0]);
    
    daysOfWork = doubleValidator(31, "work days this month");
    hoursPerDay = doubleValidator(24, "daily hours");
    wage = doubleValidator(INT_MAX, "hourly wages");
    paycheck = daysOfWork * hoursPerDay * wage;
    fedDeduction = paycheck * .15;//Calculates federal income tax.
    stateDeduction = paycheck * .035;//Calculates state tax.
    //These are deductions from social security, medicare/medicaid, pension, and health insurance.
    otherDeductions = paycheck * .0575 + paycheck * .0275 + paycheck * .05 + 75;
    paycheck = paycheck - (stateDeduction + fedDeduction + otherDeductions);
    
    ofstream out("paycheck.txt");
    out << lastName << ", " << firstName << std::endl;
    out << std::setprecision(2) << std::fixed;
    out << std::setw(20) << std::left << std::setfill('.') << "Gross Amount: " << "$" << paycheck << std::setw(4) << std::endl;
    out << std::setw(20) << std::left << std::setfill('.') << "Federal Tax: " << "$" << fedDeduction << std::setw(4) << std::endl;
    out << std::setw(20) << std::left << std::setfill('.') << "State Tax: " << "$" << stateDeduction << std::setw(4) << std::endl;
    out.close();
    
    return 0;
}

/*
 This function takes a string and makes sure it only contains characters in desiredChars. InputMsg is what
 the user is being asked to input (ex. user ID).
 Postcondition: Input is returned if all characters are digits. The user is repeatedly asked for input if any
 non-digit characters are found.
 */
string stringValidator(string desiredChars, string inputMsg){
    string input;
    
    while (true) { //input validation loop
        //Tells the user that they need to input a certain value.
        cout << "Please enter your " << inputMsg << ":\n";
        getline(cin >> std::ws, input);
        if (input.find_first_not_of(desiredChars) != string::npos) {
            //Tells the user that input has failed and that they must try again.
            cout << "The entered " << inputMsg << " is invalid\n";
            continue;
        }
        else{
            return input;
        }
    }
}

/*
 This takes a string and makes sure it is a numerical value.
 It also checks whether it lies between 0 and a boundary of your choice.
 */
double doubleValidator(int bound, string inputMsg){
    string input;
    double inputMath;
    
    while (true) { //input validation loop
        //Tells the user that they need to input a certain value.
        cout << "Please enter your " << inputMsg << ":\n";
        getline(cin >> std::ws, input);
        if (input.find_first_not_of("1234567890") == string::npos) {
            inputMath = stod(input);
            if (inputMath > bound) {//automatically assigns points to the upper bound if they exceed it.
                inputMath = bound;
            }
            else if(inputMath < 0) {//automatically assigns points to 0 if they are less than 0.
                inputMath = 0;
            }
            return inputMath;
        }
        else{
            cout << "The points entered are in an invalid format.\n";
            continue;
        }
    }
}