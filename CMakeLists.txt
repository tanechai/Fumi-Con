cmake_minimum_required(VERSION 2.8)
project( Fumi-Con )
find_package( OpenCV REQUIRED )
file(GLOB SRC
    "src/*.hpp"
    "src/*.cpp"
)
add_executable( Fumi-Con ${SRC} )
target_link_libraries( Fumi-Con ${OpenCV_LIBS} )
