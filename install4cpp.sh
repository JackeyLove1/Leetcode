rm -rf third_party
mkdir -p third_party && cd third_party
# install gtest
git clone https://github.com/google/googletest.git
cd googletest
cmake -S . -B build
cmake --build build

cd ..

# install gflags
# git clone https://github.com/gflags/gflags.git
# cd gflags
# rm -rf build
# mkdir build && cd build && cmake .. && make -j128
# cd ../..

# install glog
echo "download glog"
git clone https://github.com/google/glog.git
cd glog
echo "build glog"
cmake -S . -B build -G "Unix Makefiles"
cmake --build build

cd ..

# init CMakeLists.txt
rm -rf CMakeLists.txt
touch CMakeLists.txt
echo "add_subdirectory(\"googletest\")" >> CMakeLists.txt
# echo "add_subdirectory(\"gflags\")" >> CMakeLists.txt
echo "add_subdirectory(\"glog\")" >> CMakeLists.txt
# how to write cmake
# add_subdirectory(third)
# target_link_libraries(foo gflags::gflags glog::glog gtest)
# target_link_libraries(foo glog::glog gtest)