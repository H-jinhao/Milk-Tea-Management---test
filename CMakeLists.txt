cmake_minimum_required(VERSION 4.1)
project(Tea_House_Management C)

set(CMAKE_C_STANDARD 11)

add_executable(Tea_House_Management main.c
        "include Milktea House Management.h"
        drink_module.c
        order_module.c
        material_module.c
        data_module.c
        ui_module.c)
