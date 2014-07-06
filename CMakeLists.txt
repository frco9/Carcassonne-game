cmake_minimum_required(VERSION 2.6) 

# Projet Carcassonne
project(Carcassonne)
 
add_subdirectory(doc)

file(
    GLOB_RECURSE
    source_files
    src/*
)



Find_Package(SDL REQUIRED)
Find_Package(SDL_image REQUIRED)
 
if ( NOT SDL_FOUND )
    message(FATAL_ERROR "SDL not found !")
endif ( NOT SDL_FOUND )

if ( NOT SDLIMAGE_FOUND )
    message(FATAL_ERROR "SDL_image not found !")
endif ( NOT SDLIMAGE_FOUND )

include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
 

set(CMAKE_C_FLAGS "-std=c99")
IF(APPLE)
   set(CMAKE_C_FLAGS "-lSDLmain -std=c99")
ENDIF (APPLE)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/img
                                                           ${CMAKE_BINARY_DIR}/img)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/logique/tuiles/tuiles.txt
                                                           ${CMAKE_BINARY_DIR}/tuiles.txt)


# Déclaration de l'exécutable
add_executable(
    carcassonne
    ${source_files}
)

IF(APPLE)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   MARK_AS_ADVANCED (COCOA_LIBRARY)

   target_link_libraries(carcassonne ${COCOA_LIBRARY} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
ENDIF (APPLE)
target_link_libraries(carcassonne ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})

