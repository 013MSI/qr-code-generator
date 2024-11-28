# SOURCE: https://rowannicholls.github.io/bash/intro/myscript.html
# SOURCE DESCRIPTION: how to write a shell script
rm -rf build/
mkdir build
cd build
cmake ..
make
./qr-code-generator
