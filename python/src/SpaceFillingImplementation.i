// SWIG file

%{
#include "otlhs/SpaceFillingImplementation.hxx"
%}

%include SpaceFillingImplementation_doc.i

%template(SpaceFillingImplementationdInterfaceObject)           OT::TypedInterfaceObject<OTLHS::SpaceFillingImplementation>;

%include otlhs/SpaceFillingImplementation.hxx
namespace OTLHS { %extend SpaceFillingImplementation { SpaceFillingImplementation(const SpaceFillingImplementation & other) { return new OTLHS::SpaceFillingImplementation(other); } } }
