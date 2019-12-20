#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

int main()
{
    string line, orbitee, orbiter, start, end;
    map<string,string> m;
    set<string> planets;
    int count = -2;
    ifstream input;
    input.open("input.txt");
    while (input >> line)
    {
        orbitee = line.substr(0,line.find(")"));
        orbiter = line.substr(line.find(")")+1,line.length());
        m[orbiter] = orbitee;
    }
    start = m["YOU"];
    end = m["SAN"];
    while (start!="")
    {
        planets.insert(start);
        start = m[start];
    }
    while (end!="")
    {
        count++;
        if (planets.count(end)>0)
            break;
        end = m[end];
    }
    start = m["YOU"];
    end = m["SAN"];
    planets.clear();
    while (end!="")
    {
        planets.insert(end);
        end = m[end];
    }
    while (start!="")
    {
        count++;
        if (planets.count(start)>0)
            break;
        start = m[start];
    }
    cout << "count = " << count << endl;
}