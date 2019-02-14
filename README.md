Test case for an interesting TSAN false positive(?) with Protocol Buffers.

    protoc --cpp_out=. thing.proto
    clang++ -O0 -std=c++14 -fsanitize=thread -lprotobuf -o test test.cpp thing.pb.cc
    ./test
