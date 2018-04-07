# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp )


add_library( rt_nonfinite3
             SHARED
             src/main/cpp/ADist/rt_nonfinite.cpp )
add_library( rtGetInf3
             SHARED
             src/main/cpp/ADist/rtGetInf.cpp )
add_library( rtGetNaN3
             SHARED
             src/main/cpp/ADist/rtGetNaN.cpp )
add_library( ADist
             SHARED
             src/main/cpp/ADist/ADist.cpp )


add_library( rt_nonfinite4
             SHARED
             src/main/cpp/MyCic_16/rt_nonfinite.cpp )
add_library( rtGetInf4
             SHARED
             src/main/cpp/MyCic_16/rtGetInf.cpp )
add_library( rtGetNaN4
             SHARED
             src/main/cpp/MyCic_16/rtGetNaN.cpp )
add_library( MyCic_16
             SHARED
             src/main/cpp/MyCic_16/MyCic_16.cpp )


add_library( LEVD
             SHARED
             src/main/cpp/sup/levd.cpp )

add_library( Peak
             SHARED
             src/main/cpp/sup/Peak.cpp )
add_library( support
             SHARED
             src/main/cpp/sup/support.cpp )








# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.


target_link_libraries( # Specifies the target library.
                       rt_nonfinite3

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       rtGetNaN3
                       rtGetInf3)

target_link_libraries( # Specifies the target library.
                       ADist

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       rt_nonfinite3)

target_link_libraries( # Specifies the target library.
                       rt_nonfinite4

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       rtGetNaN4
                       rtGetInf4)

target_link_libraries( # Specifies the target library.
                       MyCic_16

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       rt_nonfinite4)

target_link_libraries( # Specifies the target library.
                       support

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       LEVD
                       Peak
                       ADist
                       MyCic_16)

target_link_libraries( # Specifies the target library.
                       native-lib android log

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ADist
                       support
                       MyCic_16)