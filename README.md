## install cmake if not exist
sudo pacman -Sy cmake 

# instalation glfw for window and opengl support functions

sudo pacman -Sy glfw
sudo pacman -Sy glew


# compile and build

cd <CMAKE_TXT_LOCATION>

cmake -S . -B build/

cd build/

make

./OpenGLProject