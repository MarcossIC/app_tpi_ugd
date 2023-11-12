cmake_minimum_required(VERSION 3.26)
project(app_tpi_ugd C)

set(CMAKE_C_STANDARD 11)

add_executable(app_tpi_ugd src/main.c
        src/user.c
        src/user.h
        src/utilidades.c
        src/utilidades.h
        src/inputs.c
        src/inputs.h
        src/cuenta.c
        src/cuenta.h
        src/movimientos.c
        src/movimientos.h
        src/validaciones.c
        src/validaciones.h
        src/transportes.c
        src/transportes.h
)
