// SWIG file

%{
#include "otlhs/LHSResult.hxx"
%}

%include LHSResult_doc.i

%include otlhs/LHSResult.hxx
namespace OTLHS { %extend LHSResult { LHSResult(const LHSResult & other) { return new OTLHS::LHSResult(other); } } }
