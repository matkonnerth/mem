#include <Mem_ArenaAllocator.h>

namespace mem
{
class ArenaAllocator
{
public:
    ArenaAllocator(size_t defaultArenaSize = 1024) {
        m_allocator = Mem_ArenaAllocator_new(defaultArenaSize);
    }
    ~ArenaAllocator()
    {
        Mem_ArenaAllocator_delete(m_allocator);
        m_allocator = nullptr;
    }
    void* alloc(size_t size)
    {
        return Mem_ArenaAllocator_malloc(m_allocator, size);
    }
    void* realloc(size_t size)
    {
        return Mem_ArenaAllocator_realloc(m_allocator, size);
    }
private:
    Mem_ArenaAllocator* m_allocator{nullptr};
};
} // namespace mem