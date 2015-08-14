// SWIG file

%{
#include "SpaceFillingMinDist.hxx"
%}

%include SpaceFillingMinDist_doc.i

%include SpaceFillingMinDist.hxx
namespace OTLHS { %extend SpaceFillingMinDist { SpaceFillingMinDist(const SpaceFillingMinDist & other) { return new OTLHS::SpaceFillingMinDist(other); } } }
