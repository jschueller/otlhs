// SWIG file

%{
#include "PlotDesign.hxx"
%}

%include PlotDesign_doc.i

%template(PlotDesigndInterfaceObject)           OT::TypedInterfaceObject<OTLHS::PlotDesign>;

%include PlotDesign.hxx
namespace OTLHS { %extend PlotDesign { PlotDesign(const PlotDesign & other) { return new OTLHS::PlotDesign(other); } } }
