#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> copy(vector<int> n)
{
    vector<int> c;
    for (int e : n)
    {
        c.push_back(e);
    }
    return c;
}

int main()
{
    string line;
    getline(cin, line);
    string delimiter = ",";
    string token = "";
    int ci = 0;
    vector<int> nums;
    vector<int> baseNums;
    while (line.length()>0)
    {
        ci = line.find(delimiter);
        if (ci<0)
            ci = line.length();
        token = line.substr(0,ci);
        if (ci==line.length())
            ci--;
        line = line.substr(ci+1);
        baseNums.push_back(stoi(token));
    }


    for (int j=0; j<100; j++)
    {
        for (int k=0; k<100; k++)
        {
            int i = 0;
            int a = 0;
            int b = 0;
            nums = copy(baseNums);
            nums[1] = j;
            nums[2] = k;
            while (i<nums.size()-3)
            {
                a = nums[nums[i+1]];
                b = nums[nums[i+2]];
                if (nums[i]==1)
                    nums[nums[i+3]] = a+b; 
                if (nums[i]==2)
                    nums[nums[i+3]] = a*b; 
                if (nums[i]==99)
                    i = nums.size();
                i += 4;
            }
            if (nums[0]==19690720)
            {
                cout << "noun = " << j << endl;
                cout << "verb = " << k << endl;
                cout << "noun*verb = " << 100*j+k << endl;
            }
        }
    }
}