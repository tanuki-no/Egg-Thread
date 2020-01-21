# Project presets
#
# Configurure the server now as: "cmake <OPTIONS> <FLAGS>  .."
#
# Options:
#
# Flags:
#
# -DCMAKE_CXX_COMPILER= /usr/bin/g++
# -DCMAKE_INSTALL_PREFIX=/opt/phoenix
# -DCMAKE_BUILD_TYPE=debug | -DCMAKE_BUILD_TYPE=release

# Commons
PROJECT("Egg::Thread" C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

# Describe project
SET ( PROJECT_VERSION_MAJOR     0                                       )
SET ( PROJECT_VERSION_MINOR     0                                       )
SET ( PROJECT_VERSION_PATCH     1                                       )
SET ( PROJECT_VERSION_TWEAK     0                                       )
SET ( PROJECT_VERSION           ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK} )

STRING( TIMESTAMP TODAY "%d/%m/%Y"					)

SET ( ABIMajor          1                                               )
SET ( ABIMinor          0                                               )
SET ( ABIPatch          0                                               )
SET ( ABIVersion        ${ABIMajor}.${ABIMinor}.${ABIPatch}             )

SET ( LibraryName	"egg-thread"
      CACHE STRING	"Thread library ${PROJECT_VERSION}. ABI: ${ABIVersion}" FORCE )

SET ( Alias		"Go cat go"                                     )
SET ( Author		"Vladislav \\\"Tanuki\\\" Mikhailikov"		)
SET ( Copyright		"GNU GPLv3"					)
SET ( Description	"Egg (Linux daemon SDK) thread library"		)
SET ( SDKName		"EggSDK"					)

# Common build paramteres
OPTION ( BUILD_SHARED_LIBS    "Build shared libraries if ON or static if OFF" ON  )
OPTION ( BUILD_PKGCONFIG      "Generate pkgconfig configuration files"        ON  )
OPTION ( BUILD_TESTS          "Build tests"                                   OFF )

# Project directories
SET ( Project_Include_Dir	"${CMAKE_SOURCE_DIR}/include"		)
SET ( Project_Source_Dir	"${CMAKE_SOURCE_DIR}/source"		)

# Library search paths
SET ( LIBRARY_SEARCH_PATH	"/lib"					)
SET ( LIBRARY_SEARCH_PATH	"${LIBRARY_SEARCH_PATH} /lib32"		)
SET ( LIBRARY_SEARCH_PATH	"${LIBRARY_SEARCH_PATH} /lib64"		)
SET ( LIBRARY_SEARCH_PATH	"${LIBRARY_SEARCH_PATH} /usr/lib"	)
SET ( LIBRARY_SEARCH_PATH	"${LIBRARY_SEARCH_PATH} /usr/lib32"	)
SET ( LIBRARY_SEARCH_PATH	"${LIBRARY_SEARCH_PATH} /usr/lib64"	)

# GNU install dirs
INCLUDE ( GNUInstallDirs )

# Check for threads
INCLUDE ( FindThreads )
IF ( CMAKE_HAVE_PTHREAD_H )
  SET ( PTHREAD_LIBRARY   ${CMAKE_THREAD_LIBS_INIT} CACHE INTERNAL "POSIX Threads library" )
  MESSAGE ( STATUS "Enabling POSIX Threads" )
ENDIF ()

# Load cmake script
INCLUDE ( ${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${SDKName}/egg-common.cmake )
IF (NOT EggFound)
  MESSAGE ( ERROR "Configuration script not found!" )
ENDIF ()

# Includes
ADD_SUBDIRECTORY ( include )

# Sources
ADD_SUBDIRECTORY ( source )

# CMake scripts
CONFIGURE_FILE(
  egg-thread.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/egg-thread.cmake
  @ONLY )

INSTALL(
  FILES       ${CMAKE_CURRENT_BINARY_DIR}/egg-thread.cmake
  DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${SDKName} )

# PkgConfig
IF (BUILD_PKGCONFIG)

  CONFIGURE_FILE(
    egg-thread.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/egg-thread.pc
    @ONLY )

  INSTALL(
    FILES       ${CMAKE_CURRENT_BINARY_DIR}/egg-thread.pc
    DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig)

ENDIF ()

# Tests
IF (BUILD_TESTS)
  ENABLE_TESTING()
  INCLUDE (CTest)
  ADD_SUBDIRECTORY ( test )
ENDIF ()

# End of file
