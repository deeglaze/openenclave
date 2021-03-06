# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

# Use the edger8r to generate C bindings from the EDL file.
add_custom_command(OUTPUT localattestation_t.h localattestation_t.c localattestation_args.h
  DEPENDS ${CMAKE_SOURCE_DIR}/localattestation.edl
  COMMAND openenclave::oeedger8r --trusted ${CMAKE_SOURCE_DIR}/localattestation.edl)

# Create a library common to each of our two enclaves.
add_library(common STATIC attestation.cpp crypto.cpp dispatcher.cpp ${CMAKE_CURRENT_BINARY_DIR}/localattestation_t.c)
target_compile_definitions(common PUBLIC OE_API_VERSION=2)
target_link_libraries(common PUBLIC
  # `liboecore`, a dependency of `liboeenclave`, requires the ecalls
  # function table. Because the libraries linking `libcommon` do not
  # directly require this symbol, the linker skips the object in
  # `libcommon` which defines them. So we manually require it.
  #
  # Alternatively we could use a CMake OBJECT library, but that
  # requires a newish version of CMake.
  -Wl,--require-defined=__oe_ecalls_table
  openenclave::oeenclave
  openenclave::oelibcxx)
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
