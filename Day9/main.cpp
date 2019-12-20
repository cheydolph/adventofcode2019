#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

void intcode(vector<int>&nums, int input)
{
    int i=0,op=0;
    long rb = 0;
    while (i<nums.size())
    {
        op = nums[i];
        int a=0,b=0,c=0;
        if (op>4)
        {
            int top = op;
            op = top % 100;
            if (op==99)
                break;
            top /= 100;
            if (top>=0)
            {
                c = top%10;
                top /= 10;
            }
            if (top>=0)
            {
                b = top%10;
                top /= 10;
            }
            if (top>0)
                a = top%10;
        }
        if (c==0)
            c = nums[nums[i+1]];
        else
            c = nums[i+1];
        if (op==3 || op==4)
        {
            if (op==3)
                nums[nums[i+1]] = input;
            else if(op==9)
                rb += c;
            else
                cout << c << endl;
            i += 2;
        }
        else
        {
            if (b==0)
                b = nums[nums[i+2]];
            else
                b = nums[i+2];
            if (op==1)
                nums[nums[i+3]] = c + b; 
            else if (op==2)
                nums[nums[i+3]] = c * b;
            else if (op==5 || op==6)
            {
                if (c!=0 && op==5 || c==0 && op==6)
                    i = b-4;
                else
                    i--;
            }
            else if (c<b && op==7 || c==b && op==8)
                nums[nums[i+3]] = 1;
            else
                nums[nums[i+3]] = 0;
            i += 4;
        }
    }
}

int main()
{
    vector<int> nums;
    ifstream file("input.txt");
    string inputLine, line;
    getline(file,inputLine);
    istringstream wordStream(inputLine);
    while (getline(wordStream,line,','))
    {
        nums.push_back(stoi(line));
    }
    intcode(nums,0);
}