#include <gtest/gtest.h>
#include <Mem_BlockAllocator.h>
#include <string.h>
#include <BlockAllocator.h>

TEST(Allocator, basics) {
    Mem_BlockAllocator* a = Mem_BlockAllocator_new(1024);
    void* mem = Mem_BlockAllocator_malloc(a, 1024);
    memset(mem, 99, 1024);
    Mem_BlockAllocator_delete(a);
}

TEST(Allocator, highLevel)
{
    mem::BlockAllocator a(1024);
    void *mem = a.alloc(1024);
    memset(mem, 99, 1024);
}