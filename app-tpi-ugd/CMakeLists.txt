cmake_minimum_required(VERSION 3.26)
project(app_tpi_ugd C)

set(CMAKE_C_STANDARD 11)

add_executable(app_tpi_ugd src/main.c
        src/accounts.c
        src/accounts.h
        src/validateData.c
        src/validateData.h
        src/inputs.c
        src/inputs.h
)
