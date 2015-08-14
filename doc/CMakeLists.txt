
find_package ( LATEX )
set ( IMAGEMAGICK_CONVERT convert )
set ( LATEX2HTML_CONVERTER latex2html )
include ( UseLATEX )

# latex part 
if ( PDFLATEX_COMPILER AND BIBTEX_COMPILER )

  if ( ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    # in-source build
    set ( LATEX_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build )
#     execute_process (
#       COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/logoOpenTURNS.jpg ${CMAKE_CURRENT_SOURCE_DIR}/logoOpenTURNS.jpg
#     )  
  else ()
    # out-of-source build
    set ( LATEX_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )
  endif ()
  add_latex_document ( OTLHS_Documentation.tex
    INPUTS logoOTLHS.png GenericInformation.tex.in OTLHS_summary.tex OTLHS_UserManual.tex Math_Notations.sty OTLHS_ArchitectureGuide.tex OTLHS_title.tex OTLHS_Documentation.sty OTLHS_ReferenceGuide.tex OTLHS_UseCasesGuide.tex OTLHS_Validation.tex
    LHSResult.png OptimalLHS.png SpaceFilling.png ishigami_test.py design_ishigami.png ishigami_model_validation.png lhs_mc_c2_10.png lhs_mc_mindist_10.png crit_sa_lin.png crit_sa_geom.png lhs_sa_geom_10.png lhs_sa_lin_10.png
    dice_c2_crit.png dice_lhs_sa_geom_10.png dice_lhs_sa_lin_10.png dice_mindist_crit.png dice_c2_crit_big.png dice_mindist_crit_big.png otlhs_c2_crit_big.png otlhs_mindist_crit_big.png
    lhs_mc_criterion.png lhs_mc_cpu_time.png
    lhs_mindist_proba.png lhs_c2_proba.png dice_mindist_proba.png dice_c2_proba.png
    comp_c2_small.png comp_mindist_small.png comp_c2_large.png comp_mindist_large.png
DEFAULT_PDF
    MANGLE_TARGET_NAMES
  ) 

  configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/GenericInformation.tex.in 
                  ${LATEX_OUTPUT_PATH}/GenericInformation.tex
                  @ONLY
  )
  
#   execute_process (
#     COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/latex2html/latex2html.sty ${LATEX_OUTPUT_PATH}/latex2html.sty
#     COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/Math_Notations.sty ${LATEX_OUTPUT_PATH}/Math_Notations.sty
#     COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/src/GenericInformation.tex ${LATEX_OUTPUT_PATH}/GenericInformation.tex
#   )     
  install ( FILES ${LATEX_OUTPUT_PATH}/OTLHS_Documentation.pdf DESTINATION ${DOC_INSTALL_PATH}/pdf )

endif ()
