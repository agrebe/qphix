message(STATUS "Finding QPhiXCodegen Library")
find_package(QPhiXCodegen REQUIRED)
if ( NOT  QPhiXCodegen_FOUND ) 
  message(FATAL_ERROR "  QPhiXCodegen Library Not Found")
endif()

message(STATUS "Finding QPhiXSolver Library")
find_package(QPhiXSolver REQUIRED)
if ( NOT QPhiXSolver_FOUND )
  message(FATAL_ERROR "  QPhiXSolver Library Not Found")
endif()

set( QPhiX_INCLUDE_DIRS "${QPHIX_DIR}/include")
set( QPhiX_LIBRARIES qphix_codegen qphix_solver ) 
set( QPhiX_FOUND TRUE )
