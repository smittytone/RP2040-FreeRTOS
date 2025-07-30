# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-src")
  file(MAKE_DIRECTORY "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-src")
endif()
file(MAKE_DIRECTORY
  "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-build"
  "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix"
  "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix/tmp"
  "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp"
  "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix/src"
  "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/smitty/GitHub/RP2040-FreeRTOS/tools/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
