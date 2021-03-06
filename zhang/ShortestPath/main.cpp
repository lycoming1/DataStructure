/*****************************************************/
/*     产生迷宫，并找到迷宫的最短出路长度
/*     输入：迷宫的规模，以房间数限定。现
/*     在程序只能支持规模Row,Col <= 4的迷
/*     宫，若超过，将无法得到结果。
/*****************************************************/
#include "Cie2DGraph.h"
using namespace Cie2DGraph;

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

#define INFINITY 32768

typedef struct VertexData
{
    int x;
    int y;
    char id;
	//int id;
} VertexType;

#include "AdjacencyMatrix.h"
#include "GetMaze.h"
MGraph G;
char vStart = 'A', vEnd = 'P';

int RQ[MAX_VERTEX_NUM];
int g_len=0;
int g_step=0;

int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int D[MAX_VERTEX_NUM];

//Dijkstra算法求从v0到其余顶点v的最短路径P[v]及带权长度D[v]。
//若P[v][w]为1,则w是从v0到v当前求得最短路径上的顶点。
//final[v]为1当且仅当v∈S, 即已经求得从v0到v的最短路径
void ShortestPathDijkstra(MGraph G,char vStart)
{
    int v0, v,w,i,j,min;
    int final[MAX_VERTEX_NUM];

    v0 = LocateVex(G, vStart);

    if(v0==-1) return;
    for(v=0; v<G.vexnum; ++v)
    {
        final[v]=0;
        D[v]=G.arcs[v0][v];
        for(w=0; w<G.vexnum; ++w) P[v][w]=-2; // 设空路径
        if(D[v]<INFINITY)
        {
            P[v][v0]=v;
            P[v][v]=-1;
        }
    }
    D[v0]=0;
    final[v0]=1; // 初始化,v0顶点属于S集
    for(i=1; i<G.vexnum; ++i) // 其余G.vexnum-1个顶点
    {
        // 开始主循环,每次求得v0到某个v顶点的最短路径,并加v到S集
        min=INFINITY; // 当前所知离v0顶点的最近距离
        for(w=0; w<G.vexnum; ++w)
            if(!final[w]) // w顶点在V-S中
                if(D[w]<min)
                {
                    v=w;
                    min=D[w];
                } // w顶点离v0顶点更近
        final[v]=1; // 离v0顶点最近的v加入S集
        for(w=0; w<G.vexnum; ++w) // 更新当前最短路径及距离
        {
            if(!final[w]&&min<INFINITY
                &&G.arcs[v][w]<INFINITY
                &&(min+G.arcs[v][w]<D[w]))
            {
                // 修改D[w]和P[w],w∈V-S
                D[w]=min+G.arcs[v][w];
                for(j=0; j<G.vexnum; ++j)
                {
                    if(P[v][j]==-1)
                        P[w][j]=w;
                    else
                        P[w][j]=P[v][j];
                }
                P[w][w]=-1;
            }
        }
    }

    i = LocateVex(G, vEnd);
    if(i==-1) return;
    v=v0;
    while (v!=-1 && P[i][v]!=-2)
    {
        RQ[g_len++]=v;
        v = P[i][v];
    }
}

void DrawGraph(MGraph G)
{
    char str[32];
    int i, j, x0, y0, x, y;
    float radius = 30;

    SetLineWidth(3);
    for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
        {
            if(G.arcs[i][j]!=INFINITY)
            {
                x0 = G.vexs[i].x;
                y0 = G.vexs[i].y;
                x = G.vexs[j].x;
                y = G.vexs[j].y;
                SetPenColorHex(0x008800);
                DrawArrowLine(x0,y0, x, y, radius, radius);
                SetPenColorHex(0x0000FF);
                sprintf(str, "%d", G.arcs[i][j]);
                DrawText2D(helv18, (x+x0)/2, (y+y0)/2, str);
            }
        }
    }

    for(i=0; i<G.vexnum; ++i)
    {
        x = G.vexs[i].x;
        y = G.vexs[i].y;
        SetPenColorHex(0xFF6010);
        if(i==LocateVex(G, vStart)) SetPenColorHex(0x00CC44);
        if(i==LocateVex(G, vEnd)) SetPenColorHex(0x0044CC);
        DrawFillCircle(x, y, radius);
        SetPenColorHex(0x000000);
        DrawCircle(x, y, radius);
        str[0] = G.vexs[i].id;
        str[1]='\0';
        DrawText2D(helv18, x-5, y-5, str);
    }
    SetLineWidth(1);
}

void DrawShortestPath(MGraph G)
{
    int i, j, k, x, y, xNext, yNext;

    SetLineWidth(8);
    for(k=0; k<g_step; ++k)
    {
        i = RQ[k];
        x = G.vexs[i].x;
        y = G.vexs[i].y;
        j = RQ[k+1];
        xNext = G.vexs[j].x;
        yNext = G.vexs[j].y;
        SetPenColorHex(0x000000);
        DrawLine(x,y, xNext, yNext);
    }
    SetLineWidth(1);
}

void display(void)
{
    DrawShortestPath(G);
    DrawGraph(G);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
    case ' ':
        if(g_step<(g_len-1))
            g_step++;
        else
            g_step=0;
        break;
    case 'i':
        break;
    default:
        break;
    }
}

/*G1
6 10
A 343 513 B 551 348 C 303 131 D 138 201 E 551 130 F 136 349
B A 56 B C 17 B E 26 C D 6 C E 52 D F 23 E A 10 F A 130 F B 24 F C 10
*/
/*G2
6
10
A 400 520 B 200 400 C 400 300 D 600 400 E 280 140 F 520 140
A B 6 A C 1 A D 5 B C 5 B E 3 C D 5 C E 6 C F 4 D F 2 E F 6
*/

int main()
{
	GetMaze();
	vEnd = 65+Row*Col-1;
    //CreateGraph(G);
	CreatMgraph(&G);
	SaveAdjMatrix(G);  //输出迷宫得到的邻接矩阵，保存在路径d:/text2中
    Show(G);
    ShortestPathDijkstra(G,vStart);//// v0为源点

    printf("Path matrix:\n");
    for(int i=0; i<G.vexnum; ++i)
    {
        for(int j=0; j<G.vexnum; ++j)
            printf("%4d",P[i][j]);
        printf("\n");
    }

	//打印入口到所有顶点的最短距离
    printf("The shortest path starting from V%c: \n",vStart);
    for(int k=0; k<G.vexnum; ++k)
        if(k!=LocateVex(G, vStart))
            printf("V%c->V%c: %d\n", vStart, G.vexs[k].id, D[k]);

	//只打印入口到出口的最短距离
	//printf("V%c->V%c: %d\n", vStart, G.vexs[G.vexnum-1].id, D[G.vexnum-1]);

    InitGraphics();
    return 0;
}
