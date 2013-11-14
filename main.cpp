
#include <stdio.h>
#include "multilayergraph.h"
#include <iostream>


using namespace std;


int main()
{
    typedef MultiLayerGraph<float,float,float> GraphType;
    int node_num=4;
    int edge_num=3;
    int label_num=3;

    float node[][3]={{2,4,1},{5,2,5},{4,2,3},{1,4,2}};
    float edge[3]={2,4,2};

    MultiLayerGraph<float,float,float> *mg=new GraphType(node_num,edge_num,label_num);

    for(int i=0; i<node_num; i++)
    {
        mg->add_node();
    }

    for(int i=0; i<node_num; i++)
    {
        for(int j=0; j<label_num; j++)
        {
            float cap=node[i][j];
            cout << cap << " ";
            mg->add_tweights(i,j,cap);
        }
    }
    cout << endl;

    int head, tail;
    for(int i=0; i<node_num; i++)
    {
        head=i;
        if(i+1<node_num)
        {
            tail=i+1;
            float cap=edge[i];
            cout << cap << " ";
            mg->add_edge(head,tail,cap,cap);
        }
    }
    cout << endl;
    cout << "Energy is : " << mg->maxflow() << endl;
    for(int i=0; i<node_num; i++)
    {
        cout << "label is : " << mg->what_segment(i) << endl;
    }
    return 0;
}
