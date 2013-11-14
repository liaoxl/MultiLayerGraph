#ifndef MULTILAYERGRAPH_H
#define MULTILAYERGRAPH_H

#include "graph.h"

template<typename captype, typename tcaptype, typename flowtype> class MultiLayerGraph
{
private:
    typedef typename Graph<captype,tcaptype,flowtype>::node_id node_id;
    typedef typename Graph<captype,tcaptype,flowtype>::node node;
    typedef typename Graph<captype,tcaptype,flowtype>::arc arc;
    typedef int label_id;

public:

    MultiLayerGraph(int node_num_max, int arc_num_max, int label_max);

    ~MultiLayerGraph();

    void add_node();

    void add_edge(node_id i, node_id j, captype cap, captype rev_cap);

    void add_tweights(node_id i, label_id j, tcaptype cap);

    flowtype maxflow();

    label_id what_segment(node_id i);

private:
    int label_num;
    int node_num;
    int layer_num;
    int arcs;
    int current_node;
    label_id *final_label;

    Graph<captype,tcaptype,flowtype> *graph;
};

#endif // MULTILAYERGRAPH_H
