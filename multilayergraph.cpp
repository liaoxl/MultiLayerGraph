#include "multilayergraph.h"

template <typename captype, typename tcaptype, typename flowtype>
MultiLayerGraph<captype,tcaptype,flowtype>::MultiLayerGraph(int node_num_max, int arc_num_max, int label_max)
{
    if(label_max < 2) label_max=2;
    label_num=label_max;
    layer_num=label_num-1;
    graph=new Graph<captype,tcaptype,flowtype>(node_num_max*(label_max-1),arc_num_max*(label_max-1)+node_num_max*label_max);
    node_num=node_num_max;
    final_label=new label_id[node_num_max];
    memset(final_label, -1, node_num_max*sizeof(label_id));
}

template <typename captype, typename tcaptype, typename flowtype>
MultiLayerGraph<captype,tcaptype,flowtype>::~MultiLayerGraph()
{
    if(graph)
    {
        delete graph;
        graph=NULL;
    }
    if(final_label)
    {
        delete final_label;
    }
}

template <typename captype, typename tcaptype, typename flowtype>
void MultiLayerGraph<captype,tcaptype,flowtype>::add_node()
{
    for(int i=0; i<layer_num; i++)
    {
        graph->add_node();
    }
}

template <typename captype, typename tcaptype, typename flowtype>
void MultiLayerGraph<captype,tcaptype,flowtype>::add_edge(node_id i, node_id j, captype cap, captype rev_cap)
{
    assert(i>=0 && i<node_num);
    assert(j>=0 && j<node_num);
    for(int k=0; k<layer_num; k++)
    {
        graph->add_edge(i*layer_num+k,j*layer_num+k,cap,rev_cap);
    }
}

template <typename captype, typename tcaptype, typename flowtype>
void MultiLayerGraph<captype,tcaptype,flowtype>::add_tweights(node_id i, label_id j, tcaptype cap)
{
    assert(j>=0 && j<label_num);
    if(j==0)
    {
        graph->add_tweights(i*layer_num,cap,0);
    }
    else if(j==label_num-1)
    {
        graph->add_tweights((i+1)*layer_num-1,0,cap);
    }
    else
    {
        graph->add_edge(i*layer_num+j-1,i*layer_num+j,cap,cap);
    }
}

template <typename captype, typename tcaptype, typename flowtype>
flowtype MultiLayerGraph<captype,tcaptype,flowtype>::maxflow()
{
    flowtype energy=graph->maxflow();

    node *i;
    node *j;
    arc *a;

    for(i=graph->nodes; i<graph->node_last; i++)
    {
        int node_index=(i-graph->nodes)/layer_num;
        if(final_label[node_index]!=-1) continue;
        int layer_index=(i-graph->nodes)%layer_num+1;
        if(layer_index==1)
        {
            if(i->is_sink)
            {
                final_label[node_index]=1;
                continue;
            }
        }
        if(layer_index==layer_num)
        {
            if(!i->is_sink)
            {
                final_label[node_index]=layer_num+1;
            }
        }
        for(a=i->first; a; a=a->next)
        {
            j=a->head;
            int jnode_index=(j-graph->nodes)/layer_num;
            int jlayer_index=(j-graph->nodes)%layer_num+1;
            if(jnode_index==node_index && i->is_sink!=j->is_sink)
            {
                final_label[node_index]=layer_index>jlayer_index?layer_index:jlayer_index;
                break;
            }
        }
    }

    return energy;
}

template <typename captype, typename tcaptype, typename flowtype>
typename MultiLayerGraph<captype,tcaptype,flowtype>::label_id MultiLayerGraph<captype,tcaptype,flowtype>::what_segment(node_id i)
{
    assert(i>=0 && i<node_num);
    return final_label[i];
}

#include "mlginstances.inc"
