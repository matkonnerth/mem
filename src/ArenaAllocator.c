/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2020 (c) Matthias Konnerth
 */

#include <Mem_ArenaAllocator.h>
#include <stdlib.h>
#include <string.h>

struct Arena;

struct Arena {
  size_t capacity;
  size_t size;
  struct Arena *next;
  char *mem;
  char *userPtr;
  size_t userSize;
};

struct Mem_ArenaAllocator {
  size_t defaultArenaSize;
  struct Arena *current;
};

static struct Arena *Arena_new(size_t capacity) {
  struct Arena *Arena = (struct Arena *)calloc(1, sizeof(struct Arena));
  if (!Arena) {
    return NULL;
  }
  Arena->mem = (char *)calloc(capacity, sizeof(char));
  if (!Arena->mem) {
    free(Arena);
    return NULL;
  }
  Arena->capacity = capacity;
  Arena->userPtr = Arena->mem;
  return Arena;
}

Mem_ArenaAllocator *Mem_ArenaAllocator_new(size_t defaultArenaSize) {
  Mem_ArenaAllocator *allocator =
      (Mem_ArenaAllocator *)calloc(1, sizeof(Mem_ArenaAllocator));
  if (!allocator) {
    return NULL;
  }
  allocator->defaultArenaSize = defaultArenaSize;
  allocator->current = Arena_new(allocator->defaultArenaSize);
  return allocator;
}

static size_t getArenaSize(size_t requested, size_t initialallocatorSize) {
  size_t ArenaSize = initialallocatorSize;
  if (requested > initialallocatorSize) {
    ArenaSize = requested * 2;
  }
  return ArenaSize;
}

void *Mem_ArenaAllocator_malloc(Mem_ArenaAllocator *allocator, size_t size) {
  if ((allocator->current->size + size) > allocator->current->capacity) {
    struct Arena *newArena =
        Arena_new(getArenaSize(size, allocator->defaultArenaSize));
    if (!newArena) {
      return NULL;
    }
    newArena->next = allocator->current;
    allocator->current = newArena;
  }
  allocator->current->userPtr =
      allocator->current->mem + allocator->current->size;
  allocator->current->size += size;
  allocator->current->userSize = size;
  return allocator->current->userPtr;
}

void *Mem_ArenaAllocator_realloc(Mem_ArenaAllocator *allocator, size_t size) {
  if ((allocator->current->size + size) > allocator->current->capacity) {
    // we also have to consider the size we have to transfer
    struct Arena *newArena = Arena_new(getArenaSize(
        size + allocator->current->userSize * 2, allocator->defaultArenaSize));
    if (!newArena) {
      return NULL;
    }
    // we have to copy over the old stuff
    memcpy(newArena->userPtr, allocator->current->userPtr,
           allocator->current->userSize);
    newArena->userSize = allocator->current->userSize;
    newArena->next = allocator->current;
    newArena->size = newArena->userSize;
    allocator->current = newArena;
  }
  allocator->current->userSize += size;
  allocator->current->size += size;
  return allocator->current->userPtr;
}

void Mem_ArenaAllocator_delete(Mem_ArenaAllocator *allocator) {
  struct Arena *r = allocator->current;
  while (r) {
    struct Arena *tmp = r->next;
    free(r->mem);
    free(r);
    r = tmp;
  }
  free(allocator);
}
