find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf 
								${CMAKE_CURRENT_BINARY_DIR}/doxygen.out.conf @ONLY)
add_custom_target(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.out.conf WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
		COMMENT ”Generating API documentation with Doxygen” VERBATIM)
endif(DOXYGEN_FOUND)
