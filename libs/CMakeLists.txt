cmake_minimum_required(VERSION 3.14)

# A big project that depends on corex-utils or a sibling dependency may have
# already added the library. If so, we no longer need to add the dependency.
# Doing so will result in an error. If it was not the case, let's add it since
# we need it. Other projects might also need it if corex-math is being used as
# part of a bigger project.
if (NOT TARGET corex-utils)
    add_subdirectory(corex-utils/)
endif()
