mkdir -p build

pushd build > /dev/null

rm test

clang ../test.cpp -o test

popd > /dev/null

build/test