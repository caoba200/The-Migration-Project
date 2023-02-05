
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main() {
    
    int n;
    cout << "Enter a positive integer n: ";
    cin >> n;
    
    if(n < 0) {
        cout << "Why are you doing this? I have a bunch of assignments therefore I have no time to write code for exceptions (which is not required in this assignment itself)" << endl;
        return 0;
    }
    
    if (n == 0 || n == 1) {
        cout << "n is not a prime number." << endl;
        return 0;
    }
    
    if (n < 4) {
        cout << "n is prime." << endl;
        return 0;
    }
    
    clock_t begin = clock();
    
    int temp = (int)sqrt(n);
    for (int i = 2; i <= temp; i++) {
        if (n % i == 0) {
            cout << "n is not prime." << endl;
            return 0;
        }
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "n is prime." << endl;
    cout << "Running time: " << elapsed_secs << endl;
    
    return 0;
}
