#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string>
using namespace std;
//DFS( v )
//{
//  if ��������
//      do....
//      return
//  for ���� v �����п���ȡֵ
//      if ����ĳЩ����
//          visited[v] = true
//          DFS ��һ��
//          visited[v] = false
//}
//
//BFS()
//{
//  q.push(head);
//  visited[head] = 1;
//  while(!q.empty())
//  {
//      int temp = q.front();
//      q.pop();
//      for(....)
//      {
//          temp �ڽӵ� ����Ҫ��)
//          �жϣ� �Ƿ�Խ�缰�Ƿ��Ѿ�����
//          ���㣺
//          q.push(temp)
//          visited[temp] = 1;
//      }
//  }
//}
//
//stack : 
//s.empty() s.size() s.pop() (no return)
//s.top()(no delete)   s.push()

//queue : 
//q.empty() q.size() q.pop() (no return)
//q.front()(no delete)  q.back()  q.push()
//
string map[4] = {"--##---",
                 "-------",
                 "#---#--",
                 "-------"};
char visited[4][7]; 

typedef struct _node
{
    int x; int y;
} node_t;
int dfs(node_t start, node_t end)
{
    //cout << start.x  << ":" << start.y << endl;
    if(start.x == end.x && start.y == end.y)
        return 1;
    else
    {
        visited[start.x][start.y] = '1';
        if(start.x -1 >= 0  && map[start.x - 1][start.y] != '#' && visited[start.x -1][start.y] == '0')
        {
            //cout << "x-1" << endl;
            start.x--;
            if ( dfs(start, end) == 1)
                return 1;
        }
        
        if(start.y + 1 <= 6 && map[start.x][start.y + 1] != '#' && visited[start.x][start.y + 1] == '0')
        {
            //cout << "y+1" << endl;
            start.y++;
            if (dfs(start, end) == 1)
                return 1;
        }
        if(start.x + 1 <= 3  && map[start.x + 1][start.y] != '#' && visited[start.x+1][start.y] == '0')
        {
            //cout << "x+1" << endl;
            start.x++;
            if (dfs(start, end) == 1)
                return 1;
        }
        if(start.y -1 >= 0  && map[start.x][start.y -1] != '#' && visited[start.x][start.y-1] == '0')
        {
            cout << "y-1" << endl;
            start.y--;
            if (dfs(start, end) == 1)
                return 1;
        }
        visited[start.x][start.y] = '0';

    }
    return 0; 
}

int main()
{
   int x1, y1, x2, y2; 
   cin >> x1 >> y1 >> x2 >> y2;
   node_t start;
   start.x = x1;
   start.y = y1;
   node_t end;
   end.x = x2;
   end.y = y2;
   cout << map[start.x][start.y] << map[end.x][end.y] << endl;
   memset(visited, '0', sizeof(visited));
   visited[start.x][start.y] = '1';
   cout << dfs(start, end) << endl;

}

