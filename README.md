MultiLayerGraph
==================================================================

	MultiLayerGraph - Software for computing the multilabel problem in a graph
	                       Version 1.0
	
	https://github.com/liaoxl/MultiLayerGraph
	Xiangli Liao(liaoxl2012@gmail.com)
	Reimplemented to make it available for public use
	2012~2013

--------------------------------------------------------------------

### 1. Introduction.

This software library implements the maxflow algorithm described in
	
	"Interactively multiphase image segmentation based on variational formulation and graph cuts"
	Wenbing Tao, Feng Chang, Liman Liu, Hai Jin, Tianjiang Wang
	In Pattern Recognition 
	October 2010

This algorithm was developed by Wenbing Tao and Feng Chang in Research.
To make it available for public use,
it was later reimplemented by Xiangli Liao based on open publications.

If you use this software for research purposes, you should cite
the aforementioned paper in any resulting publication.

----------------------------------------------------------------------

### 2. Example usage.

This section shows how to use the library to compute
a minimum cut on the following graph:

///////////////////////////////////////////////////


                           SOURCE               Node_Layer 0
                       /  |      |   \
                    2 / 5 |     4|   1\         Layer 1
                     /    |      |     \
                   n0 --- n1 --- n2 --- n3      Node_Layer 1
                    |  2  |   4  |   2  |
                   4|   2 |     2|     4|       Layer 2
                    |     |      |      |
                   n0 --- n1 --- n2 --- n3      Node_Layer 2
                     \  2 |   4  |   2 /
                    1 \ 5 |     3|   2/         Layer 3
                       \  |      |   /
                            SINK                Node_Layer 3


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

///////////////////////////////////////////////////
