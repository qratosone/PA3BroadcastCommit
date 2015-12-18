#include "import.h"
#include "stdlib.h"
#include <iostream>
using namespace std;
class VertexNode {
public:
    int num;
    int flag;
    int indegree;
    int outdegree;
    int neiboIndex;
    int  neibo[2000];
    VertexNode() {
        num = 0;
        indegree = 0;
        outdegree = 0;
        neiboIndex = 0;
        flag = 0;

    }
    ~VertexNode() {
    }
};
typedef VertexNode* pNode;
VertexNode v[20000];
void createGraph(const int &n, const int&m) {
    int* eBegin = new int[m];
    int* eEnd = new int[m];
    for (int i = 0; i < m; i++) //插入边
    {
        cin >> eBegin[i] >> eEnd[i];
        int start = eBegin[i];
        int end = eEnd[i];
        if (!v[start].num) {   //给V中的节点赋值，把每边端点的数字赋值给start，end下同
            v[start].num = start;
        }
        if (!v[end].num) {
            v[end].num = end;
        }
        v[start].outdegree++; //start出度加1
        v[end].indegree++; //end入度加1
    }

    for (int i = 0; i < m; i++)
    {
        int start = eBegin[i];//对于每一条边，把边上的end节点添加到start的neibo上
        int end = eEnd[i];
        int index = v[start].neiboIndex;
        v[start].neibo[index] = end;
        v[start].neiboIndex++;
    }
    delete eBegin, eEnd;
}

int BFS() {
    Queue<int> q;
    int start = 1;
    v[start].flag = 1;
    q.enqueue(start);
    while (!q.empty())
    {
        start = q.dequeue();
        VertexNode n = v[start];
        int temp = n.flag;
        for (int i = 0; i < n.neiboIndex; i++)
        {
            int neiboNum = n.neibo[i];
            if (v[neiboNum].flag==temp)
            {
                return -1;
            }
            if (v[neiboNum].flag==0)
            {
                v[neiboNum].flag = -temp;
                temp = v[neiboNum].flag;
                q.enqueue(neiboNum);
            }
        }
    }
    return 1;
}

int main() {
    int n, m;

    cin >> n >> m;
    createGraph(n, m);
    int result = BFS();
    cout << result << endl;
    return  0;
}