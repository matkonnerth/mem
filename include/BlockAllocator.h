#include <Mem_BlockAllocator.h>

namespace mem
{
class BlockAllocator
{
public:
    BlockAllocator(size_t defaultBlockSize = 1024) {
        m_allocator = Mem_BlockAllocator_new(defaultBlockSize);
    }
    ~BlockAllocator()
    {
        Mem_BlockAllocator_delete(m_allocator);
        m_allocator = nullptr;
    }
    void* alloc(size_t size)
    {
        return Mem_BlockAllocator_malloc(m_allocator, size);
    }
    void* realloc(size_t size)
    {
        return Mem_BlockAllocator_realloc(m_allocator, size);
    }
private:
    Mem_BlockAllocator* m_allocator{nullptr};
};
} // namespace mem