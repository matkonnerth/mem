/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2020 (c) Matthias Konnerth
 */

#ifndef Mem_BlockAllocator_H
#define Mem_BlockAllocator_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
struct Mem_BlockAllocator;
typedef struct Mem_BlockAllocator Mem_BlockAllocator;

Mem_BlockAllocator *Mem_BlockAllocator_new(size_t defaultBlockSize);
void *Mem_BlockAllocator_malloc(struct Mem_BlockAllocator *allocator, size_t size);
void *Mem_BlockAllocator_realloc(struct Mem_BlockAllocator *allocator, size_t size);
void Mem_BlockAllocator_delete(struct Mem_BlockAllocator *allocator);

#ifdef __cplusplus
}
#endif
#endif
