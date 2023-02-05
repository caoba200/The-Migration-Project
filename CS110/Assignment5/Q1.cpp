/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 5
 
 // Program name: Credit Card Number Validation
 
 // Created by Bao D. Cao on 2016-11-24.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Prompt user enter credit card number
                    2. Check the validation of the number by the steps indicated below
 //                 3. Display the result
 // Major variables: card
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;
// Return true if the card number is valid
bool isValid (const string&);

// Get the result from Step b
int sumOfDoubleEvenPlace(const string&);

// Return this number if it is a single digit, otherwise
// return the sum of two digits
int getDigit(int);

// Return sum of odd-place digit in the card number
int sumOfOddPlace(const string&);

// Return true if substr is the prefix for card number
bool startWith(const string&, const string&);

int main() {
    
    string card;
    
    // Step 1: Prompt user enter the card number
    
    cout << "Input card number: " ;
    cin >> card;
    
    // Step 2: Check the validation of the card and display the result
    
    if (startWith(card, card.substr(0, 2)) && isValid(card))
        cout << "The card number " << card << " is valid." << endl;
    else
        cout << "The card nubmer " << card << " is invalid." << endl;
    
    return 0;
}
/*****************************************************/
// Check if (sum of double even place) + (sum of odd place) is divisible by 10 --> number is valid

// Return true if the card number is valid
/*****************************************************/
bool isValid (const string& cardNumber) {
    return (sumOfDoubleEvenPlace(cardNumber) + sumOfOddPlace(cardNumber)) % 10 == 0;
}

/*****************************************************/
// Get the result from Step b
// Basically add all the digits in even places after double it
// The digit after being doubled is put into getDigit to create the corresponding digit for the sum
/*****************************************************/
int sumOfDoubleEvenPlace(const string& cardNumber) {
    int sum = 0;
    for (int i = 0; i < cardNumber.length(); i++)
        sum += i % 2 == 0 ? getDigit(2 * (cardNumber[i] - 48)) : 0;
    
    return sum;
}

/*****************************************************/
// Return this number if it is a single digit, otherwise
// return the sum of two digits
/*****************************************************/
int getDigit(int number) {
    return number / 10 == 0 ? number : (number + (number % 10) * 10 ) / 10;
}

/*****************************************************/
// Return sum of odd-place digit in the card number
/*****************************************************/
int sumOfOddPlace(const string& cardNumber) {
    int sum = 0;
    for (int i = 0; i < cardNumber.length(); i++)
        sum += i % 2 != 0 ? cardNumber[i] - 48 : 0;
    return sum;
}

/*****************************************************/
// Check if card's length is between 13 and 16 --> return false if the condition is wrong
// Check the fist letter of substr (4 or 5 or 6) and the substr (37) --> the prefix
// Return true if substr is the prefix for card number
/*****************************************************/
bool startWith(const string& cardNumber, const string& substr) {
    if (cardNumber.length() < 13 || cardNumber.length() > 16)
        return false;
    return substr[0] == '4' || substr[0] == '5' || substr[0] == '6' || substr == "37";
}

