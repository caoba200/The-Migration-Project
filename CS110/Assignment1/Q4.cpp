//
//  Q4 - Assignment #1 - CS 110
//
//  Created by Bao D. Cao on 2016-09-18.
//  Copyright © 2016 Bao D. Cao. All rights reserved.
//

#include <iostream>
#include <cmath> // Insert cmath library to use the function calulate the power

using namespace std;

/* Question 4: Read in investment ammount, annual interest rate, and number of years, then display the future investment using given formula (Programming exercise 2.3)*/

int main() {
    
    // Step 1: Decleare necessary variables
    float investAmount; // invesment ammount
    float rate; // annual interest rate
    int years; // number of year
    
    // Step 2: Receive the information from user
    cout << "Enter investment amount: " ;
    cin >> investAmount;
    
    cout << "Enter annual interest rate in percentage: " ;
    cin >> rate;
    
    cout << "Enter number of years: " ;
    cin >> years;
    
    // Step 3: Calculate the monthly interest rate and store the value into the variable monthRate.
    float monthRate = rate / 12;
    
    // Step 4: Calculate future investment value and store the value into the variable futureInvestmentValue.
    float futureInvestmentValue = investAmount * pow(1 + monthRate / 100, years * 12); // The pow function is equivalent to (1 + monthRate / 100) ^ (years * 12). monthRate needs to be changed to percentage by divided it by 100
    
    // Step 5: Display the output
    cout << "Accumulated value is $" << futureInvestmentValue << endl;
    
    return 0;
}
