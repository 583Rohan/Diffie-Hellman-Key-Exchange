#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

int twoTypeInput(int a, int b);
bool is_Prime(int n);
int square_and_multiply(int base, int exponent, int modulus);
void fillGVector(vector <int> &a, int p);

int main(){
    srand(time(0));
    int p, xA, xB;
    cout << "Make your selection:" << endl;
    cout << "1. Manual Input" << endl;
    cout << "2. Auto Input" << endl;
    
    int choice = twoTypeInput(1, 2);
    switch(choice){
        case 1: //Manual

            //Getting p
            cout << "Enter a prime number lower than 100:" << endl;
            do{
                cin >> p;
                if(!is_Prime(p) || p >= 100){
                    cout << "Please enter a valid Prime Number, lower than 100" << endl;
                }
            } while(!is_Prime(p) || p >= 100);

            //Getting xA
            cout << "Enter xA (a number between 1 and " << p-1 << "):" << endl;
            do {
                cin >> xA;
                if(xA <= 0 || xA >= p) {
                    cout << "Invalid input for xA. Please enter a number between 1 and " << p-1 << "." << endl;
                }
            } while(xA <= 0 || xA >= p);

            //Getting xB
            cout << "Enter xB (a number between 1 and " << p-1 << "):" << endl;
            do {
                cin >> xB;
                if(xB <= 0 || xB >= p) {
                    cout << "Invalid input for xB. Please enter a number between 1 and " << p-1 << "." << endl;
                }
            } while(xB <= 0 || xB >= p);
            
            break;

        case 2: //Auto

        cout << "Generating random p" << endl;
        do{
            p = rand() % 100 + 1;
        } while(!is_Prime(p));

        cout << "Generating random xA" << endl;
        xA = rand() % (p-1) + 1;
        cout << "Generating random xB" << endl;
        xB = rand() % (p-1) + 1;

    }

    vector<int> g;
    int yA, yB, kA, kB;

    //calculate and store the values of primitive modulus in g
    fillGVector(g, p);

    cout << endl <<endl;
    cout << "p:  " << p << endl;
    cout << "xA: " << xA <<endl;
    cout << "xB: " << xB <<endl << endl;
    cout << endl;
    cout << "For every value of g, there is a different value of key" << endl << endl;

    //Find key for ever value of g

    cout << setw(15) << "Value of g";
    cout << setw(15) << "Key" << endl;
    cout <<  "------------------------------" << endl;
    for(int i = 0; i < g.size(); i++){

        cout << setw(15) << g[i];

        yA = square_and_multiply(g[i], xA, p);
        yB = square_and_multiply(g[i], xB, p);

        kA = square_and_multiply(yB, xA, p);
        kB = square_and_multiply(yA, xB, p);

        if(kA == kB){
            cout << setw(15) << kA <<endl;
        }
        else{
            cout << "Potential errors in inputs validation";
        }

    }
    return 0;
}

int twoTypeInput(int a, int b){
    int choice;
    do{
        cin >> choice;
        if(choice !=a && choice !=b){
            cout << "Please make a selection between " << a << " and " << b << endl;
        }
    }
    while(choice !=a && choice !=b);
    return choice;
}
bool is_Prime(int n) {
    //Numbers smaller than 1 and 1 are not prime, so  return false
    if (n <= 1) {
        return false;
    }
    //if n is devisible by any number greater than n^(1/2), than is should also be devisible by smaller number
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int square_and_multiply(int base, int X, int p) {
    int result = 1;
    while (X > 0) {
        if (X % 2 == 1) {
            result = (result * base) % p;
        }
        
        X = X >> 1;
        base = (base * base) % p;
    }
    return result;
}
void fillGVector(vector <int> &a,int  p){
    for (int i = 2; i < p; i++) {
        bool isPrimitive = true;
        for (int j = 1; j < p - 1; j++) {
            // If i^j % p is 1 for any j other than p-1, then i is not a primitive root
            if (square_and_multiply(i, j, p) == 1 && j != p-1) {
                isPrimitive = false;
                break;
            }
        }
        if (isPrimitive) {
            a.push_back(i);
        }
    }
}
/*
int mod(int base, int X, int p){
    int result;
    result = (base^X)%p;
    return result;
}
*/