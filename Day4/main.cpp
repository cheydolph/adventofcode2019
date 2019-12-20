#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

bool meetsNewCriteria(int n)
{
    string s;
    stringstream ss;
    ss << n;
    ss >> s;
    map<char,int> dupes;
    int minDup = 10;
    for (int i=0; i<s.length()-1; i++)
    {
        if (s[i]==s[i+1])
        {
            if (dupes.count(s[i])==0)
                dupes[s[i]] = 1;
            dupes[s[i]]++;
        }
        if (s[i]>s[i+1])
            return false;
    }
    for (auto e : dupes)
    {
        if (e.second<minDup)
            minDup = e.second;
    }
    return minDup==2;
}

bool meetsCriteria(int n)
{
    string s;
    stringstream ss;
    ss << n;
    ss >> s;
    bool isAdj = false;
    for (int i=0; i<s.length()-1; i++)
    {
        if (s[i]==s[i+1])
            isAdj = true;
        if (s[i]>s[i+1])
            return false;
    }
    return isAdj;
}

int inRange(int low, int high)
{
    int count = 0;
    for (int i=low; i<=high; i++)
    {
        if (meetsNewCriteria(i))
            count++;
    }
    return count;
}

int main()
{
    string line;
    ifstream file("input.txt");
    getline(file,line);
    string l = line.substr(0,line.find("-"));
    string h = line.substr(line.find("-")+1,line.length());
    cout << inRange(stoi(l),stoi(h)) << endl;
}