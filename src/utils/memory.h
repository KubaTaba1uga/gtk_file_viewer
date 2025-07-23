#ifndef GTK_FILE_VIEWER_UTILS_MEMORY_H
#define GTK_FILE_VIEWER_UTILS_MEMORY_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline void *my_malloc(uint32_t size) {
  void *out = malloc(size);
  if (!out) {
    fprintf(stderr, "my_malloc: failed to allocate %u bytes\n", size);
    exit(ENOMEM);
  }

  return out;
}

static inline void *my_calloc(uint32_t amount, uint32_t size) {
  void *out = calloc(amount, size);
  if (!out) {
    fprintf(stderr, "my_calloc: failed to allocate %u * %u bytes\n", amount,
            size);
    exit(ENOMEM);
  }

  return out;
}

#endif // GTK_FILE_VIEWER_UTILS_MEMORY_H
