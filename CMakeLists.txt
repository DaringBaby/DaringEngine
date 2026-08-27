cmake_minimum_required(VERSION 3.16)
project(DaringEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Configurazione percorsi SDL3
# Assicurati che questo percorso contenga effettivamente SDL3Config.cmake
set(SDL3_DIR "D:/Progettini/DaringEngine/SDL3-3.4.4/x86_64-w64-mingw32/lib/cmake/SDL3")

# 2. Ricerca del pacchetto SDL3
find_package(SDL3 REQUIRED)

# 3. Impostazione cartella di uscita (l'eseguibile apparirà dove hai il main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

# 4. Definizione dell'eseguibile
add_executable(DaringEngine main.cpp src/scripts/engine/language.cpp src/scripts/engine/ui.cpp src/scripts/engine/Battle.cpp src/scripts/classes/entity.cpp src/scripts/classes/Attack.cpp
                src/scripts/classes/Character.cpp src/scripts/classes/Enemy.cpp src/scripts/classes/Equip.cpp src/scripts/classes/Item.cpp src/scripts/classes/Magic.cpp
                src/scripts/classes/PlayerVars.cpp)

# 5. ATTIVAZIONE INCLUDE (Fondamentale per risolvere l'errore C1083)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Aggiungiamo sia gli include di SDL3 che la tua cartella 'include' locale
target_include_directories(DaringEngine PRIVATE
    "D:/Progettini/DaringEngine/SDL3-3.4.4/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include" # <--- Nota bene il percorso
)

# 6. Collegamento librerie (.lib)
target_link_libraries(DaringEngine PRIVATE SDL3::SDL3)

# 7. AUTOMAZIONE DLL
# Se la build fallisce qui, controlla se la DLL è in /bin/ o in /bin/x64/
add_custom_command(TARGET DaringEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "D:/Progettini/DaringEngine/SDL3-3.4.4/bin/SDL3.dll"
    $<TARGET_FILE_DIR:DaringEngine>
)
