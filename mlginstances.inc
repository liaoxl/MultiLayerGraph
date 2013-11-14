#include "multilayergraph.h"

#ifdef _MSC_VER
#pragma warning(disable: 4661)
#endif

// Instantiations: <captype, tcaptype, flowtype>
// IMPORTANT:
//    flowtype should be 'larger' than tcaptype
//    tcaptype should be 'larger' than captype

template class MultiLayerGraph<int,int,int>;
template class MultiLayerGraph<short,int,int>;
template class MultiLayerGraph<float,float,float>;
template class MultiLayerGraph<double,double,double>;

