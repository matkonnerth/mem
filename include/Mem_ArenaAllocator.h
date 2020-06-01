/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2020 (c) Matthias Konnerth
 */

#ifndef Mem_ArenaAllocator_H
#define Mem_ArenaAllocator_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
struct Mem_ArenaAllocator;
typedef struct Mem_ArenaAllocator Mem_ArenaAllocator;

Mem_ArenaAllocator *Mem_ArenaAllocator_new(size_t defaultArenaSize);
void *Mem_ArenaAllocator_malloc(struct Mem_ArenaAllocator *allocator, size_t size);
void *Mem_ArenaAllocator_realloc(struct Mem_ArenaAllocator *allocator, size_t size);
void Mem_ArenaAllocator_delete(struct Mem_ArenaAllocator *allocator);

#ifdef __cplusplus
}
#endif
#endif
