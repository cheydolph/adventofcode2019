#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <utility>
#include <cmath>
#include <map>

using namespace std;

map<pair<int,int>,int> makeCoord(string d, map<string,int> m)

{
    map<pair<int,int>,int> steps;
    pair<int,int> p;
    int coord[2] = {0,0};
    int move = 0, stepCount = 0;
    string temp;
    while (d.length()>0)
    {
        temp = d.substr(0,1);
        if (d.find(",")==-1)
        { 
            move = stoi(d.substr(1));
            d = "";
        }
        else
        {
            move = stoi(d.substr(1,d.find(",")));
            d = d.substr(d.find(",")+1);
        }
        for (int i=move; i>0; i--)
        {
            if (temp=="R" || temp=="L")
                coord[0] += m[temp];
            if (temp=="D" || temp=="U")
                coord[1] += m[temp];
            p = make_pair(coord[0],coord[1]); 
            steps[p] = ++stepCount;
        }
    }
    return steps;
}

void Part1(set<pair<int,int>> &grid1, set<pair<int,int>> &grid2)
{
    int min = INT16_MAX;
    int x = 0, y = 0;
    for (auto e : grid2)
    {
        if (grid1.count(e)!=0)
        {
            x = e.first * ((e.first>0)-(e.first<0)); 
            y = e.second * ((e.second>0)-(e.second<0)); 
            if ((x+y)<min)
                min = x+y;
        }
    }
    cout << "Smallest Intersection = " << min << endl;
}

void Part2(map<pair<int,int>,int> m1, map<pair<int,int>,int> m2)
{
    int min = INT16_MAX;
    for (auto e : m2)
    {
        if (m1.count(e.first)!=0)
        {
            if (m1[e.first]+e.second<min)
                min =  m1[e.first]+e.second;
        }
    }
    cout << "MinSteps = " << min << endl;
}

int main()
{
    string dir1, dir2;
    ifstream f("input.txt");
    getline(f,dir1);
    getline(f,dir2);
    map<string,int> m = { {"L",-1},{"R",1},{"D",-1},{"U",1}};
    map<pair<int,int>,int> m1 = makeCoord(dir1,m);
    map<pair<int,int>,int> m2 = makeCoord(dir2,m);
    Part2(m1,m2);
}