
add_subdirectory ( include )
add_subdirectory ( src )
add_subdirectory ( test )

install ( FILES ${HEADERFILES}
          DESTINATION ${OTLHS_INCLUDE_PATH}/${PACKAGE_NAME}
        )

