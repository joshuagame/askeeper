echo "###########################################"
rm -rf build
mkdir build
cd build

cmake ..

make

cd ..
rm -rf dist
mkdir dist
cp build/askeeper* dist
cp /usr/local/bin/cygmicrohttpd-10.dll dist
