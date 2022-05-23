//
// Created by Jacky on 2022/5/20
//

// a simple malloc/free function implement

#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

struct s_block;
typedef s_block *t_block;

// aligning the bytes
static constexpr size_t ALIGN(size_t size) {
    return static_cast<size_t>(size - 1) / 8 * 8 + 8;
}

// malloc block_size
static constexpr size_t BLOCK_SIZE = 40;

// malloc block
struct s_block {
    size_t size;
    int free;
    t_block next;
    t_block prev;
    void *ptr; // the address of this block's data
    char data[1]; // the true data
};

// the malloc begin address
static void *base = nullptr;

t_block extend_heap(t_block last, size_t s);

void split_block(t_block b, size_t s);

t_block find_block(t_block *last, size_t size);

void *malloc(size_t size);

t_block fusion(t_block b);

t_block get_block(void *p);

int valid_addr(void *p);

void *malloc(size_t size) {
    t_block b, last;
    size_t s;
    s = ALIGN(s);
    if (base) {
        // using find_block and split_block
        last = reinterpret_cast<t_block>(base);
        b = find_block(&last, s);
        if (b) {
            // can we split it
            if ((b->size - s) >= (BLOCK_SIZE + 8)) {
                split_block(b, s);
            }
            b->free = 0;
        } else {
            // extend heap
            b = extend_heap(last, s);
            if (!b) {
                return NULL;
            }
        }
    } else {
        // using extend_heap init base
        b = extend_heap(NULL, s);
        if (!b) {
            return NULL;
        }
        base = b;
    }
    return b->data;
}

t_block extend_heap(t_block last, size_t s) {
    t_block b;
    b = reinterpret_cast<t_block>(sbrk(0)); // the basic address of s_block
    void *sb = sbrk(BLOCK_SIZE + s);
    if (sb < (void *) 0) {
        return NULL;
    }
    b->size = s;
    b->next = NULL;
    b->prev = last;
    b->ptr = b->data;
    b->free = 0;
    if (last) {
        last->next = b;
    }
    return b;
}

void split_block(t_block b, size_t s) {
    t_block new_block;
    new_block = reinterpret_cast<t_block>(b->data + s);
    new_block->size = b->size - s - BLOCK_SIZE;
    new_block->next = b->next;
    new_block->prev = b;
    new_block->free = 1;
    new_block->ptr = new_block->data;
    b->size = s;
    b->free = 0;
    b->next = new_block;
    if (new_block->next) {
        new_block->next->prev = new_block;
    }
}

t_block find_block(t_block *last, size_t size) {
    t_block b = (s_block *) base;
    while (b && !(b->free && b->size >= size)) {
        *last = b;
        b = b->next;
        // if we don't find a fit block,
        // the last will point to the end of the allocate heap
    }
    return b;
};

t_block fusion(t_block b) {
    // merge the two consecutive pieces
    if (b->next && b->next->free) {
        b->size += BLOCK_SIZE;
        +b->next->data;
        b->next = b->next->next;
        if (b->next) {
            b->next->prev = b;
        }
    }
    return b;
}

t_block get_block(void *p) {
    // get the block from and addr
    char *tmp;
    tmp = reinterpret_cast<char *>(p);
    return (p = tmp += BLOCK_SIZE);
}

int valid_addr(void *p) {
    if (base) {
        if (p > base && p < sbrk(0)) {
            return (p == (get_block(p)->ptr));
        }
    }
    return 0;
};

void free(void *p) {
    t_block b;
    if (valid_addr(p)) {
        b = get_block(p);
        b->free = 1;
        if (b->prev && b->prev->free) {
            b = fusion(b->prev);
        }
        if (b->next) {
            fusion(b);
        } else {
            if (b->prev) {
                b->prev->next = NULL;
            } else {
                base = NULL;
            }
            brk(b);
        }
    }
}