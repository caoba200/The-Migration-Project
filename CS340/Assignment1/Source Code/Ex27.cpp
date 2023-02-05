#include <iostream>
#include <ctime>

using namespace std;

void funct1(int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        ++sum;
    }
}

void funct2(int n) {
    int sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            ++sum;
}

void funct3(int n) {
    int sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n * n; j++)
            ++sum;
}

void funct4(int n) {
    int sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
            ++sum;
}

void funct5(int n) {
    int sum =  0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i * i; j++)
            for(int k = 0; k < j; k++)
                sum++;
}

void funct6(int n) {
    int sum = 0;
    for(int i = 1; i < n; i++)
        for(int j = 1; j < i * i; j++)
            if(j % i == 0)
                for(int k = 0; k < j; k++)
                    sum++;
}

int main() {
    
    int n, n2;
    cout << "Enter n: ";
    cin >> n;
    
    cout << "Enter the code segment: ";
    cin >> n2;
    
    clock_t begin = clock();
    
    switch(n2) {
        case 1:
            funct1(n);
            break;
        case 2:
            funct2(n);
            break;
        case 3:
            funct3(n);
            break;
        case 4:
            funct4(n);
            break;
        case 5:
            funct5(n);
            break;
        case 6:
            funct6(n);
            break;
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "Running time: " << elapsed_secs << endl;
    
    return 0;
}
