mkdir -p build

pushd build

rm test

clang ../test.cpp -o test

popd 

build/test