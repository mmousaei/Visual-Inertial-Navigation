cmake_minimum_required (VERSION 2.8)
project(hello_world_plugin)

find_package(catkin_simple REQUIRED)

catkin_simple(ALL_DEPS_REQUIRED)

add_definitions(-fPIC -shared)

cs_add_library(hello_world_plugin /home/mohammadreza/Documents/CMU-Project/Visual-Inertial-Navigation/maplab_ws/hello-world-plugin/src/hello-world-plugin.cc)

create_console_plugin(hello_world_plugin)


cs_install()
cs_export()