#include <BlockAllocator.h>
#include <Mem_BlockAllocator.h>
#include <gtest/gtest.h>
#include <string.h>

TEST(Allocator, basics)
{
    Mem_BlockAllocator *a = Mem_BlockAllocator_new(1024);
    void *mem = Mem_BlockAllocator_malloc(a, 1024);
    memset(mem, 99, 1024);
    Mem_BlockAllocator_delete(a);
}

TEST(Allocator, highLevel)
{
    mem::BlockAllocator a(1024);
    void *mem = a.alloc(1024);
    memset(mem, 99, 1024);
}

TEST(Allocator, bigAlloc)
{
    mem::BlockAllocator a(100);
    void *mem = a.alloc(1024 * 1024);
    memset(mem, 99, 1024 * 1024);
}

TEST(Allocator, memcmp)
{
    mem::BlockAllocator a(100);
    char cmp1[100];
    memset(cmp1, 1, 100);
    char *mem = static_cast<char *>(a.alloc(100));
    memcpy(mem, cmp1, 100);
    char cmp2[100];
    char *mem2 = static_cast<char *>(a.alloc(100));
    memset(cmp2, 2, 100);
    memcpy(mem2, cmp2, 100);

    ASSERT_EQ(memcmp(mem, cmp1, 100), 0);
    ASSERT_EQ(memcmp(mem2, cmp2, 100), 0);
}

TEST(Allocator, realloc)
{
    mem::BlockAllocator a(100);
    char cmp1[100];
    memset(cmp1, 1, 100);
    char *mem = static_cast<char *>(a.alloc(100));
    memcpy(mem, cmp1, 100);
    char cmp2[100];
    char *mem2 = static_cast<char *>(a.realloc(200));
    memset(cmp2, 2, 100);
    memcpy(mem2+100, cmp2, 100);

    ASSERT_EQ(memcmp(mem2, cmp1, 100), 0);
    ASSERT_EQ(memcmp(mem2+100, cmp2, 100), 0);
}