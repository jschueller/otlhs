

ot_add_current_dir_to_include_dirs ()

ot_add_source_file ( PlotDesign.cxx )
ot_add_source_file ( LHSDesign.cxx )
ot_add_source_file ( TemperatureProfile.cxx )
ot_add_source_file ( TemperatureProfileImplementation.cxx )
ot_add_source_file ( GeometricProfile.cxx )
ot_add_source_file ( LinearProfile.cxx )
ot_add_source_file ( SpaceFilling.cxx )
ot_add_source_file ( SpaceFillingImplementation.cxx )
ot_add_source_file ( SpaceFillingC2.cxx )
ot_add_source_file ( SpaceFillingMinDist.cxx )
ot_add_source_file ( SpaceFillingPhiP.cxx )
ot_add_source_file ( OptimalLHS.cxx )
ot_add_source_file ( OptimalLHSImplementation.cxx )
ot_add_source_file ( MonteCarloLHS.cxx )
ot_add_source_file ( SimulatedAnnealingLHS.cxx )
ot_add_source_file ( LHSResult.cxx )

ot_install_header_file ( OTLHS.hxx )
ot_install_header_file ( PlotDesign.hxx )
ot_install_header_file ( LHSDesign.hxx )
ot_install_header_file ( TemperatureProfile.hxx )
ot_install_header_file ( TemperatureProfileImplementation.hxx )
ot_install_header_file ( GeometricProfile.hxx )
ot_install_header_file ( LinearProfile.hxx )
ot_install_header_file ( SpaceFilling.hxx )
ot_install_header_file ( SpaceFillingImplementation.hxx )
ot_install_header_file ( SpaceFillingC2.hxx )
ot_install_header_file ( SpaceFillingMinDist.hxx )
ot_install_header_file ( SpaceFillingPhiP.hxx )
ot_install_header_file ( OptimalLHS.hxx )
ot_install_header_file ( OptimalLHSImplementation.hxx )
ot_install_header_file ( MonteCarloLHS.hxx )
ot_install_header_file ( SimulatedAnnealingLHS.hxx )
ot_install_header_file ( LHSResult.hxx )

include_directories ( ${INTERNAL_INCLUDE_DIRS} )

add_library ( otlhs ${SOURCEFILES} )
if ( BUILD_SHARED_LIBS )
  set_target_properties ( otlhs PROPERTIES COMPILE_DEFINITIONS "OTLHS_DLL_EXPORTS" )
endif ()

if ( NOT DEFINED LIB_VERSION ) 
  set ( LIB_VERSION 0.0.0 )
endif ()
if ( NOT DEFINED LIB_SOVERSION ) 
  set ( LIB_SOVERSION 0 )
endif ()
set_target_properties ( otlhs PROPERTIES VERSION ${LIB_VERSION} )
set_target_properties ( otlhs PROPERTIES SOVERSION ${LIB_SOVERSION} )
target_link_libraries ( otlhs ${OPENTURNS_LIBRARIES} )

install ( TARGETS otlhs
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${OTLHS_LIBRARY_PATH}
  ARCHIVE DESTINATION ${OTLHS_LIBRARY_PATH}
)

