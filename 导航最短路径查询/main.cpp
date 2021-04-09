#include <iostream>
#include <algorithm>
#include <stack>

#define MaxVertexNum 1000010
#define INF 999999

using namespace std;

typedef int Vertex;
typedef int WeightType;
//边的定义
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};
typedef struct ENode* PtrToENode;
typedef PtrToENode Edge;

//图的结点的定义
struct GNode {
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum]; //邻接矩阵
    //DataType Data[MaxVertexNum]; //存顶点的数据
};
typedef struct GNode* PtrToGNode;
typedef PtrToGNode MGraph;

int n, e; //城市数量 n 和路径数 e
MGraph Gra; //图
int tag[MaxVertexNum];
int dis[MaxVertexNum];
int path[MaxVertexNum];

MGraph CreateGraph(int VertexNum)
{
    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph -> Nv = VertexNum;
    Graph -> Ne = 0;
    for (Vertex V = 1; V <= Graph -> Nv; V++)
    {
        for (Vertex W = 1; W <= Graph -> Nv; W++)
        {
            if (V == W)
            {
                Graph -> G[V][W] = 0;
            }
            else
                Graph -> G[V][W] = INF;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph -> G[E -> V1][E -> V2] = E -> Weight;
}

MGraph BuildGraph(int Nv, int Ne)
{
    MGraph Graph = CreateGraph(Nv);
    Graph -> Ne = Ne;
    if (Graph -> Ne != 0)
    {
        Edge E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph -> Ne; i++)
        {
            scanf("%d %d %d", &E -> V1, &E -> V2, &E -> Weight);
            InsertEdge(Graph, E);
        }
    }

    cout << "有向图构建成功!" << endl;
    //清屏
    return Graph;
}

void Dijkstra(Vertex v)
{
    for (int i = 1; i <= n; i++) {
        dis[i] = Gra -> G[v][i];
    }
    dis[v] = 0;

    tag[v] = 1;
    for (int i = 1; i <= n - 1; i++)
    {
        int min = INF;
        int u = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!tag[j] && dis[j] < min)
            {
                min = dis[j];
                u = j;
            }
        }
        if (u == -1)
            break;
        tag[u] = 1;
        for (int k = 1; k <= n; k++)
        {
            if (!tag[k] && dis[u] + Gra -> G[u][k] < dis[k])
            {
                path[k] = u;
                dis[k] = dis[u] + Gra -> G[u][k];
            }
        }
    }
}

void print_1(Vertex v)
{
    Dijkstra(v);
    cout << endl;
    cout << "路径长度\t\t路径" << endl;

    stack<Vertex> s;
    for (int i = 1; i <= n; i++)
    {
        int j = i;
        while (path[j] != -1)
        {
            s.push(j);
            j = path[j];
        }
        s.push(j);
        printf("%6d", dis[i]);
        cout << "\t\t" << v;
        while (!s.empty())
        {
            cout << " -> " << s.top();
            s.pop();
        }
        cout << endl;
    }
    cout << endl << endl << endl;
}

void print_2(Vertex v, Vertex m)
{
    Dijkstra(v);
    stack<Vertex> s;
    int i = m;
    while (path[i] != -1)
    {
        s.push(i);
        i = path[i];
    }
    s.push(i);
    cout << v;
    while (!s.empty()) {
        cout << " -> " << s.top();
        s.pop();
    }

    cout << "\t";
    cout << "路径长度: " << dis[m] << endl;
    cout << endl << endl << endl;
}

void menu()
{
    cout << "********* 欢迎进入交通资讯系统 *********" << endl;
    cout << "*    现在先构建交通网络图的存储结构      *" << endl;
    cout << "***** 请输入城市数量 n 和路径数 e :  ****" << endl;
    cin >> n >> e;
    cout << "请输入 " << e << " 条边的坐标 (i, j) 以及权值 W: " << endl;
    Gra = BuildGraph(n, e);
    /*
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << Gra -> G[i][j] << " ";
        }
        cout << endl;
    }
     */
    memset(path, -1, sizeof(path));
    memset(tag, 0, sizeof(tag));
    memset(dis, 0x3f, sizeof(dis));
    while (1)
    {
        cout << "***      咨询系统已开启, 请选择:    ***" << endl;
        cout << "*   1.查询一个城市到所有城市的最短路径  *" << endl;
        cout << "*   2.查询任意两个城市之间的最短路径    *" << endl;
        cout << "************ 输入0退出 **************" << endl;
        int cmd;
        cin >> cmd;
        if (cmd == 1)
        {
            cout << "输入顶点 V : " ;
            Vertex v;
            cin >> v;
            print_1(v);
        }
        else if (cmd == 2)
        {
            cout << "输入起点 v 和终点 m : ";
            Vertex v, m;
            cin >> v >> m;
            print_2(v, m);
        }
        else if (cmd == 0)
        {
            break;
        }
        else
        {
            cout << "没有此功能选项, 请重新输入!" << endl;
            continue;
        }
    }
    exit(0);
}

int main()
{
    menu();
    return 0;
}