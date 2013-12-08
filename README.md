==================================================================

#                                                                 #
#    MAXFLOW - software for computing mincut/maxflow in a graph   #
#                        Version 3.01                             #
#    http://www.cs.ucl.ac.uk/staff/V.Kolmogorov/software.html     #
#                                                                 #
#    Yuri Boykov (yuri@csd.uwo.ca)                                #
#    Vladimir Kolmogorov (v.kolmogorov@cs.ucl.ac.uk)              #
#    2001-2006                                                    #
#                                                                 #
===================================================================

1. Introduction.

This software library implements the maxflow algorithm described in

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

##################################################################

2. License & disclaimer.

    Copyright 2001-2006 Vladimir Kolmogorov (v.kolmogorov@cs.ucl.ac.uk), Yuri Boykov (yuri@csd.uwo.ca).

    This software can be used for research purposes only.
    If you require another license, you may consider using version 2.21
    (which implements exactly the same algorithm, but does not have the option of reusing search trees).

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

##################################################################

3. Example usage.

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
