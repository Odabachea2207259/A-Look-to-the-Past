if($1 -eq "build"){
    cd .\build\Debug
    cmake -G"MinGW Makefiles" ../.. -DCMAKE_BUILD_TYPE=Debug
    cd ../..
}
elseif($1 -eq "compile"){
    cmake --build build/Debug --target CimaEngine3v -j 8   
}
elseif($1 -eq "clean"){
    cmake --build build/Debug --target clean -j 8   
}