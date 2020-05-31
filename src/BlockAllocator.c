/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2020 (c) Matthias Konnerth
 */

#include <Mem_BlockAllocator.h>
#include <stdlib.h>
#include <string.h>

struct Block;

struct Block {
  size_t capacity;
  size_t size;
  struct Block *next;
  char *mem;
  char *userPtr;
  size_t userSize;
};

struct Mem_BlockAllocator {
  size_t defaultBlockSize;
  struct Block *current;
};

static struct Block *Block_new(size_t capacity) {
  struct Block *Block = (struct Block *)calloc(1, sizeof(struct Block));
  if (!Block) {
    return NULL;
  }
  Block->mem = (char *)calloc(capacity, sizeof(char));
  if (!Block->mem) {
    free(Block);
    return NULL;
  }
  Block->capacity = capacity;
  Block->userPtr = Block->mem;
  return Block;
}

Mem_BlockAllocator *Mem_BlockAllocator_new(size_t defaultBlockSize) {
  Mem_BlockAllocator *allocator =
      (Mem_BlockAllocator *)calloc(1, sizeof(Mem_BlockAllocator));
  if (!allocator) {
    return NULL;
  }
  allocator->defaultBlockSize = defaultBlockSize;
  allocator->current = Block_new(allocator->defaultBlockSize);
  return allocator;
}

static size_t getBlockSize(size_t requested, size_t initialallocatorSize) {
  size_t BlockSize = initialallocatorSize;
  if (requested > initialallocatorSize) {
    BlockSize = requested * 2;
  }
  return BlockSize;
}

void *Mem_BlockAllocator_malloc(Mem_BlockAllocator *allocator, size_t size) {
  if ((allocator->current->size + size) > allocator->current->capacity) {
    struct Block *newBlock =
        Block_new(getBlockSize(size, allocator->defaultBlockSize));
    if (!newBlock) {
      return NULL;
    }
    newBlock->next = allocator->current;
    allocator->current = newBlock;
  }
  allocator->current->userPtr =
      allocator->current->mem + allocator->current->size;
  allocator->current->size += size;
  allocator->current->userSize = size;
  return allocator->current->userPtr;
}

void *Mem_BlockAllocator_realloc(Mem_BlockAllocator *allocator, size_t size) {
  if ((allocator->current->size + size) > allocator->current->capacity) {
    // we also have to consider the size we have to transfer
    struct Block *newBlock = Block_new(getBlockSize(
        size + allocator->current->userSize * 2, allocator->defaultBlockSize));
    if (!newBlock) {
      return NULL;
    }
    // we have to copy over the old stuff
    memcpy(newBlock->userPtr, allocator->current->userPtr,
           allocator->current->userSize);
    newBlock->userSize = allocator->current->userSize;
    newBlock->next = allocator->current;
    newBlock->size = newBlock->userSize;
    allocator->current = newBlock;
  }
  allocator->current->userSize += size;
  allocator->current->size += size;
  return allocator->current->userPtr;
}

void Mem_BlockAllocator_delete(Mem_BlockAllocator *allocator) {
  struct Block *r = allocator->current;
  while (r) {
    struct Block *tmp = r->next;
    free(r->mem);
    free(r);
    r = tmp;
  }
  free(allocator);
}
