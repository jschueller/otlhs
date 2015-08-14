// SWIG file

%{
#include "LHSResult.hxx"
%}

%include LHSResult_doc.i

%include LHSResult.hxx
namespace OTLHS { %extend LHSResult { LHSResult(const LHSResult & other) { return new OTLHS::LHSResult(other); } } }
