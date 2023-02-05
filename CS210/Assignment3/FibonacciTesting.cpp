/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #3
 
 // Program name: Fibonacci Number Calculation
 
 // Date : October 15, 2017
 **************************************************/
#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>

typedef clock_t SystemTime; //Rename the type clock_t

using namespace std;

//===================================================
//Class Timer : is used to determine the time which is used to run an algorithm
//      class timer is implemented by using methods from 2 libraries ctime and time.h
//===================================================
class Timer {
public:
    //start the timer
    void start() {
        startTime = clock();
    }
    //stop the timer
    void stop() {
        stopTime = clock();
    }
    //Computes the length of the time interval from startTime to stopTime (in seconds).
    double getElapsedTime() const {
        return double (stopTime - startTime) / (CLOCKS_PER_SEC);
    }
private:
    SystemTime startTime, stopTime;
};


//===================================================
// Fibonacci_Recursive(int) : long long -- calculate the nth Fibonacci by using recursion
//===================================================
long long Fibonacci_Recursive(int n) {
    //base case -- we assume the first Fibonacci is 1
    if (n == 0 || n == 1)
        return n;
    else //Recursive formula
        return Fibonacci_Recursive(n - 1) + Fibonacci_Recursive(n - 2);
}

//===================================================
// Fibonacci_Iteration(int) : long long -- calculate the nth Fibonacci by using iteration
//===================================================
long long Fibonacci_Iteration(int n) {
    long long result = 0;
    long long f2 = 0; //the second number before the current fibonacci
    long long f1 = 1; //the first number before the current fibonacci
    
    if(n < 2) //return n if n is 0 or 1
        return n;
    
    for (int i = 0; i < n - 1; i++) {
        result = f1 + f2; //calculate F(n)
        f2 = ((f2 = f1 + f2, f1 = f2 - f1), f2 - f1); //update n - 2 to the previous n - 1 -- one line swapping
        f1 = result; //update n - 1 to result;
    }
    
    return result;
}


//======================================================
// main function : tests the time used to run 2 algorithms (recursion and iteration) by using a set of testing values
//======================================================
int main() {
    
    int testing[] = {5, 10, 30, 40, 50}; //Testing values for 2 algorithm
    
    Timer time; //an object of class Timer
    
    //Set up the header
    cout << "N" << setw(15) << "Fibonacci" << setw(15) << "Time" << endl << endl;
    cout << "----------------------------------------";
    
    cout << endl << endl;
   
    for (int i = 0; i < 5; i++) { //go through each value for N
        //**************************** Recursion ****************************
        time.start(); //start the clock
        cout << testing[i] << setw(15) << Fibonacci_Recursive(testing[i]); //calculate the fibonacci using recursion
        time.stop(); //stop the clock
        cout << setw(15) << time.getElapsedTime() << " seconds" << endl; //get the elapsed time
        
        //*************************** Iteration *****************************
        time.start(); //start the clock
        cout << setw(17) << Fibonacci_Iteration(testing[i]); //calculate the fibonacci using iteration
        time.stop(); //stop the clock
        cout << setw(15) << time.getElapsedTime() << " seconds" << endl << endl; //get the elapsed time
        cout << "----------------------------------------";
        
        cout << endl << endl;
    }
    
    return 0;
}
