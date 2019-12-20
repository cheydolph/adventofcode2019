#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int getLowest0s(string line)
{
    vector<int> zeroCount(1);
    vector<int> oneCount(1);
    vector<int> twoCount(1);
    int r=0,c=0,l=0;
    for (int i=0; i<line.length(); i++)
    {
        if (line[i]=='0')
            zeroCount[l]++;
        if (line[i]=='1')
            oneCount[l]++;
        if (line[i]=='2')
            twoCount[l]++;
        if (c==24)
        {
            c = 0;
            if (r==5)
            {
                zeroCount.push_back(0);
                oneCount.push_back(0);
                twoCount.push_back(0);
                r = 0;
                l++;
            }
            else
            {
                r++;
            }
        }
        else
            c++;
    }
    int zCount = 25*6, min=0;
    for (int i=0; i<zeroCount.size()-1; i++)
    {
        int o = zeroCount[i];
        if (zeroCount[i]<zCount)
        {
            min = i;
            zCount = zeroCount[i];
        }
    }
    return oneCount[min]*twoCount[min];
}
void image(string line)
{
    vector<vector<char>> layer(6,vector<char>(25));
    vector < vector< vector<char> > > layers;
    int r = 0, c = 0, l=0;
    for (int i=0; i<line.length(); i++)
    {
        layer[r][c] = line[i];
        if (c==24)
        {
            c = 0;
            if (r==5)
            {
                layers.push_back(layer);
                r = 0;
            }
            else
                r++;
        }
        else
            c++;
    }
    for (r=0; r<6; r++)
    {
        for (c=0; c<25; c++)
        {
            l = 0;
            while (l<layers.size())
            {
                if (layers[l][r][c]!='2')
                {
                    layer[r][c] = layers[l][r][c];
                    if (layer[r][c]=='0')
                        cout << " " << " ";
                    else
                        cout << layer[r][c] << " ";
                    break;
                }
                l++;
            }
        }
        cout << endl;
    }
}

int main()
{
    string line;
    ifstream file("input.txt");
    getline(file,line);
    cout << "Part 1 = " << getLowest0s(line) << endl;
    image(line); 
}