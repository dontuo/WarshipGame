mkdir build/
cd build/
cp ../textures -r .
rm WarshipGame
cmake ../CMakeLists.txt -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug

make -j8

if [ ! -f WarshipGame ]; then
    echo "Compile failed"
else
    echo "Starting game: "
    gf2 WarshipGame
fi

