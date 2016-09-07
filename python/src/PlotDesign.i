// SWIG file

%{
#include "otlhs/PlotDesign.hxx"
%}

%include PlotDesign_doc.i

%template(PlotDesigndInterfaceObject)           OT::TypedInterfaceObject<OTLHS::PlotDesign>;

%include otlhs/PlotDesign.hxx
namespace OTLHS { %extend PlotDesign { PlotDesign(const PlotDesign & other) { return new OTLHS::PlotDesign(other); } } }
