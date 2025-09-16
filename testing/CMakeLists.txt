set( TESTINGS_SRC 
    testing_dsyrk.c
    testing_dgemm.c
    testing_dgemmcd.c
    testing_sgemm.c
    )

list(REMOVE_DUPLICATES HCORE_DEP) # WARNING: is it safe, respect order?
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
#message(${CMAKE_EXE_LINKER_FLAGS})
#list(APPEND CMAKE_EXE_LINKER_FLAGS "${LAPACKE_LINKER_FLAGS}")
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../src/misc/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../src/include )
foreach(_testing ${TESTINGS_SRC})
    get_filename_component(_name_exe ${_testing} NAME_WE)
    # Prefix with hcore_ to avoid conflicts with DPLASMA test targets
    set(_target_name "hcore_${_name_exe}")
    add_executable(${_target_name} ${_testing}) 
    #    add_dependencies(${_target_name} testing_include)
    #target_link_libraries(${_target_name} ${libs_for_testings})
    target_link_libraries(${_target_name} hcore ${HCORE_DEP})
    install(TARGETS ${_target_name} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/hcore/testing)

    add_test( NAME ${_target_name} COMMAND ${_target_name})
endforeach()
