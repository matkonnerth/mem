/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2020 (c) Matthias Konnerth
 */

#ifndef BLOCKALLOCATOR_H
#define BLOCKALLOCATOR_H
#include <stddef.h>

struct BlockAllocator;
typedef struct BlockAllocator BlockAllocator;

BlockAllocator *BlockAllocator_new(size_t defaultBlockSize);
char *BlockAllocator_malloc(struct BlockAllocator *allocator, size_t size);
char *BlockAllocator_realloc(struct BlockAllocator *allocator, size_t size);
void BlockAllocator_delete(struct BlockAllocator *allocator);

#endif
