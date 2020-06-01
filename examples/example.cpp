#include <ArenaAllocator.h>
#include <iostream>

struct MyStruct
{
    int a;
    int b;
};

int main(int argc, const char* argv[])
{
    mem::ArenaAllocator a;
    auto mem1 = a.alloc(1);
    auto mem2 = a.alloc(sizeof(MyStruct));
    auto s1 = new(mem2)MyStruct();
    s1->a = 10;
    s1->b = 20;
    std::cout << s1->a << std::endl;
    std::cout << s1->b << std::endl;
    return 0;
}