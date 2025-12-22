#pragma once
#include <vector>
#include <new>
#include <stdexcept>
#include <cstdint>

// Implementation of pool allocator. Improves allocation time and compactness of data.
// Deallocation cannot be performed for individual objects and does not cause their destructors to be called.
// Data are not removed by `reset()` and stay accessible until they become overwritten by another allocation.
class PoolAllocator {
    // Vector of bytes storing all the allocated data.
    std::vector<std::byte> pool;
    unsigned int offset = 0;
    template<typename T>
    void align() {
        unsigned int start = reinterpret_cast<std::uintptr_t>(pool.data());
        unsigned int aligned = (start + offset + alignof(T) - 1) & ~(alignof(T) - 1);
        offset = aligned - start;
    }
    public:
        PoolAllocator(unsigned int size = 1024): pool(size) {};
        template<typename T, typename... Args>
        T* alloc(Args&&... args) {
            align<T>();
            if (offset + sizeof(T) > pool.size()) {
                printf("PoolAllocator::alloc(): Resizing from %llu", pool.size());
                pool.resize((pool.size() + sizeof(T)) * 2);
                printf(" to %llu bytes.\n", pool.size());
            }
            void* address = pool.data() + offset;
            offset += sizeof(T);
            return new(address) T(std::forward<Args>(args)...);
        }
        void reset() {offset = 0;}
};