#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string line = "1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,10,1,19,2,19,6,23,2,13,23,27,1,9,27,31,2,31,9,35,1,6,35,39,2,10,39,43,1,5,43,47,1,5,47,51,2,51,6,55,2,10,55,59,1,59,9,63,2,13,63,67,1,10,67,71,1,71,5,75,1,75,6,79,1,10,79,83,1,5,83,87,1,5,87,91,2,91,6,95,2,6,95,99,2,10,99,103,1,103,5,107,1,2,107,111,1,6,111,0,99,2,14,0,0";
    string delimiter = ",";
    string token = "";
    int ci = 0;
    vector<int> nums;
    while (line.length()>0)
    {
        ci = line.find(delimiter);
        if (ci<0)
            ci = line.length();
        token = line.substr(0,ci);
        if (ci==line.length())
            ci--;
        line = line.substr(ci+1);
        nums.push_back(stoi(token));
    }
    int i = 0;
    int a = 0;
    int b = 0;
    int op = 0;
    nums[1] = 12;
    nums[2] = 2;
    while (i<nums.size())
    {
        a = nums[nums[i+1]];
        b = nums[nums[i+2]];
        op = nums[i];
        if (op==1)
            nums[nums[i+3]] = a+b; 
        if (op==2)
            nums[nums[i+3]] = a*b; 
        if (op==99)
            i = nums.size();
        i += 4;
    }
    cout << "final = " << nums[0] << endl;
    return 0;
}