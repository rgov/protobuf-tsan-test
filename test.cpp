#include <thread>

#include "thing.pb.h"

/*
From: https://developers.google.com/protocol-buffers/docs/reference/cpp/

Thread-safety in the Protocol Buffer library follows a simple rule: unless
explicitly noted otherwise, it is always safe to use an object from multiple
threads simultaneously as long as the object is declared const in all threads
(or, it is only used in ways that would be allowed if it were declared const).
However, if an object is accessed in one thread in a way that would not be
allowed if it were const, then it is not safe to access that object in any
other thread simultaneously.

Put simply, read-only access to an object can happen in multiple threads
simultaneously, but write access can only happen in a single thread at a time.
*/

void reader(const Thing& thing)
{
    // This should only read, `thing` is a const reference and
    // DebugString() is a const method
    for (int i = 0; i < 1000; ++i)
        std::string foo = thing.DebugString();
}

int main()
{
    // Create a new Thing
    Thing thing;
    thing.set_content("Hello world!");

    // Spin off several threads that read `thing`
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i ++)
        threads.push_back(std::thread(reader, thing));

    // Wait for all threads to finish
    for (auto& t : threads) t.join();
}
