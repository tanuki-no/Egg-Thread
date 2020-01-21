# Public headers

# Egg
FILE (
  COPY "${CMAKE_CURRENT_SOURCE_DIR}/egg/thread/pool.hpp"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/egg/thread" )

# Egg public includes
SET (
  Public_Include

  "${CMAKE_CURRENT_BINARY_DIR}/egg/thread/pool.hpp"

  CACHE INTERNAL "Common headers" )


# Install the Egg::Variable library
INSTALL(
  FILES       ${Public_Include}
  DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}/egg/thread" )

# End of file
