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

The MultiLayerGraph was firstly proposed in

	"Exact Optimization for Markov Random Fields with Convex Priors"
	Hiroshi Ishikawa
	In IEEE Transactions on PAMI
	October 2003

which can exactly optimize the multilabel MRF energy.
Bae and Tai devise a similar multilayer graph to solve the multiphase Mumford-Shah model in

	"Graph Cut Optimization for the Piecewise Constant Level Set Method Applied to Multiphase Image Segmentation"
	Egil Bae and Xue-Cheng Tai
	In The 2nd international conference, SSVM
	2009
	
This software is an implementation of the above publications and is applied in some publications of Wenbing Tao (Mentor of **Xiangli Liao**)

This software library implements the maxflow algorithm described in

	"Interactively multiphase image segmentation based on variational formulation and graph cuts"
	Wenbing Tao, Feng Chang, Liman Liu, Hai Jin, Tianjiang Wang
	In Pattern Recognition
	October 2010

This algorithm was developed by Wenbing Tao in Academic Research.
To make it available for public use,
it was later reimplemented by **Xiangli Liao** based on open publications.

If you use this software for research purposes, you should cite
the aforementioned paper in any resulting publication.

---------------------------------------------------------------------

### 2. Related Works.

Our work is based on the public available source code `MAXFLOW` developed by Boykov and Kolmogorov

    MAXFLOW - software for computing mincut/maxflow in a graph
                        Version 3.01
    http://www.cs.ucl.ac.uk/staff/V.Kolmogorov/software.html

    Yuri Boykov (yuri@csd.uwo.ca)
    Vladimir Kolmogorov (v.kolmogorov@cs.ucl.ac.uk)
    2001-2006

-------------------------------------------------------------------------

	"An Experimental Comparison of Min-Cut/Max-Flow Algorithms for Energy Minimization in Vision."
	Yuri Boykov and Vladimir Kolmogorov.
	In IEEE Transactions on Pattern Analysis and Machine Intelligence (PAMI),
	September 2004

This algorithm was developed by Yuri Boykov and Vladimir Kolmogorov
at Siemens Corporate Research. To make it available for public use,
it was later reimplemented by Vladimir Kolmogorov based on open publications.

If you use this software for research purposes, you should cite
the aforementioned paper in any resulting publication.

----------------------------------------------------------------------

REUSING TREES:

Starting with version 3.0, there is a also an option of reusing search
trees from one maxflow computation to the next, as described in

	"Efficiently Solving Dynamic Markov Random Fields Using Graph Cuts."
	Pushmeet Kohli and Philip H.S. Torr
	International Conference on Computer Vision (ICCV), 2005

If you use this option, you should cite
the aforementioned paper in any resulting publication.

Tested under windows, Visual C++ 6.0 compiler and unix (SunOS 5.8
and RedHat Linux 7.0, GNU c++ compiler).

----------------------------------------------------------------------

### 3. Example usage.

This section shows how to use the library to compute
a minimum cut on the following graph:

----------------------------------------------------------------

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

----------------------------------------------------------------


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

----------------------------------------------------------------------
