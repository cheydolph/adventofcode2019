#include <iostream>
using namespace std;

int main()
{
    int total = 0, mass = 0;
    string line;
    for (int i=0; i<100; i++)
    {
        getline(cin, line);
        mass = stoi(line);
        total += (mass/3)-2;
    }
    cout << "Total = " << total << endl;
}