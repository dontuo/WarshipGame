rm WarshipGame
rm CmakeCache.txt
rm Makefile
cmake CMakeLists.txt -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

make -j8

if [ ! -f WarshipGame ]; then
    echo "Compile failed"
else
    echo "Starting game: "
    ./WarshipGame
fi

