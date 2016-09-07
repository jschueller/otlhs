// SWIG file

%{
#include "otlhs/SpaceFillingMinDist.hxx"
%}

%include SpaceFillingMinDist_doc.i

%include otlhs/SpaceFillingMinDist.hxx
namespace OTLHS { %extend SpaceFillingMinDist { SpaceFillingMinDist(const SpaceFillingMinDist & other) { return new OTLHS::SpaceFillingMinDist(other); } } }
