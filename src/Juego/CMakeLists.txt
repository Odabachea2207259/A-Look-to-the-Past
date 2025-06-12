project(CimaEngine3v)

#agregar los folders restantes
add_subdirectory(Figuras)
add_subdirectory(Sistemas)
add_subdirectory(Escenas)
add_subdirectory(Objetos)
add_subdirectory(Maquinas)
add_subdirectory(Componentes)
add_subdirectory(Dinosaurios)
add_subdirectory(Habilidades)
add_subdirectory(Estados)

target_sources(CimaEngine3v PRIVATE Juego.cpp)




