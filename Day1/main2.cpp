#include <iostream>
using namespace std;
int main()
{
    int mass = 0, total = 0;
    string line;
    for (int i=0; i<100; i++)
    {
        getline(cin, line);
        mass = stoi(line);
        while (mass > 0)
        {
            mass = (mass/3)-2;
            if (mass < 0)
                mass = 0;
            total += mass;
        }
    }
    cout << "Total = " << total << endl;
}