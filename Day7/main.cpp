#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int intcode(vector<int>&nums, queue<int> &inputs) 
{
    int i=0,op=0,output=0;
    while (i<nums.size())
    {
        op = nums[i];
        int a=0,b=0,c=0;
        if (op>4)
        {
            int top = op;
            op = top % 100;
            if (op==99)
                return output;
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
            {
                int f = inputs.front();
                nums[nums[i+1]] = inputs.front();
                inputs.pop();
            }
            else
            {
                output = c;
                inputs.push(output);
            }
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
    return output;
}

int getOutput(vector<int>&nums,vector<int>&phases)
{
    int result = 0;
    queue<int> inputs;
    inputs.push(phases[0]);
    inputs.push(result);
    for (int i=1; i<phases.size(); i++)
    {
        inputs.push(phases[i]);
    }
    result = intcode(nums,inputs);
    return result;
}

int perm(vector<int>&nums, vector<int>&phases, int pos) 
{
    if (pos==phases.size())
        return getOutput(nums,phases);
    int result = 0;
    for (int i=pos; i<phases.size(); i++)
    {
        swap(phases[pos],phases[i]);
        result = max(result,perm(nums,phases,pos+1));
        swap(phases[pos],phases[i]);
    }
    return result;
}


int main()
{
    vector<int> nums;
    ifstream file("input.txt");
    string inputLine, line;
    getline(file,inputLine);
    istringstream wordStream(inputLine);
    int input = 0;
    while (getline(wordStream,line,','))
    {
        nums.push_back(stoi(line));
    }
    vector<int> phases = {9,8,7,6,5};//{5,6,7,8,9}; 
    int maxResult = getOutput(nums,phases);
   // int maxResult = perm(nums,phases,0);
    cout << "maxResult = " << maxResult << endl;
    return 0;
}