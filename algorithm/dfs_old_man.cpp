#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <vector>

using namespace std;

int deskAccu;

vector<int> firstdesk;
int firstAccu;
int firstNum;

vector<int> seconddesk;
int secondAccu;
int secondNum;

vector<int> thirddesk;
int thirdAccu;
int thirdNum;

vector<bool> visited;
vector<int>  value;

int detectValid()
{
    if(firstNum == 8 && firstAccu != deskAccu)
        return -1;
    if(secondNum == 8 && secondAccu != deskAccu)
        return -1;
    if(thirdNum == 8 && thirdAccu != deskAccu)
        return -1;

    if(firstAccu == deskAccu&&
       secondAccu == deskAccu&&
       thirdAccu == deskAccu&&
       firstNum == 8 && secondNum == 8&&
       thirdNum == 8)
        return 1;
    return 0;
}

void output()
{
    std::cout << "\nfirst desk:" << std::endl;
    for(int i = 0; i < 8; i++)
    {
        printf("%d ", firstdesk[i]);
    }
    std::cout << "\nsecond desk:" << std::endl;
    for(int i = 0; i < 8; i++)
    {
        printf("%d ", seconddesk[i]);
    }
    std::cout << "\nthird desk:" << std::endl;
    for(int i = 0; i < 8; i++)
    {
        printf("%d ", thirddesk[i]);
    }
}

void dfs_resolve(int pos)
{
    int flags = detectValid();
    if(flags < 0)
        return;
    if(flags > 0)
    {
        output();
        return;
    }
    if(pos >= value.size())
        return;
    if(firstNum < 8)
    {
        firstNum++;
        firstAccu+=value[pos];
        firstdesk.push_back(value[pos]);
        pos++;
        dfs_resolve(pos);
        pos--;
        firstdesk.pop_back();
        firstAccu-=value[pos];
        firstNum--;
    }    
    if(secondNum < 8)
    {
        secondNum++;
        secondAccu+=value[pos];
        seconddesk.push_back(value[pos]);
        pos++;
        dfs_resolve(pos);
        pos--;
        seconddesk.pop_back();
        secondAccu-=value[pos];
        secondNum--;
    }
    if(thirdNum < 8)
    {
        thirdNum++;
        thirdAccu+=value[pos];
        thirddesk.push_back(value[pos]);
        pos++;
        dfs_resolve(pos);
        pos--;
        thirddesk.pop_back();
        thirdAccu-=value[pos];
        thirdNum--;
    }
    return;
}



int main()
{
    int sum = 0;
    for(int i = 76; i <= 99; i++)
    {
        value.push_back(i);
        visited.push_back(false);
        sum += i;
    }
    deskAccu = sum/3;
    dfs_resolve(0);
}
