/*
 * quecto.h - Tiny mono-header C testing library
 * Version 0.1
 *
 * Copyright (c) 2026 Matteo Pauroso
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef QUECTO_H
#define QUECTO_H

#include <stdio.h>

typedef void (*quecto_test_fn)(void);

typedef struct {
  const char *name;
  quecto_test_fn fn;
} quecto_test;

#if defined(__GNUC__) || defined(__clang__)

#define QUECTO_SECTION __attribute__((used, section("quecto_tests")))

#define TEST(name)                                                             \
  static void quecto_test_##name(void);                                        \
  static const quecto_test quecto_entry_##name QUECTO_SECTION = {              \
      #name, quecto_test_##name};                                              \
  static void quecto_test_##name(void)

#else

#error "quecto only supports GCC or Clang for now"

#endif // defined(__GNUC__) || defined(__clang__)

#include <setjmp.h>

void _quecto_assert(const char *file, int line, const char *expr);

#define ASSERT(expr)                                                           \
  do {                                                                         \
    if (!(expr)) {                                                             \
      _quecto_assert(__FILE__, __LINE__, #expr);                               \
    }                                                                          \
  } while (0)

#ifdef QUECTO_IMPLEMENTATION

static jmp_buf quecto_jmp;
static int quecto_failed;

void _quecto_assert(const char *file, int line, const char *expr) {
  fprintf(stderr, "\t%s:%d: assertion failed: %s\n", file, line, expr);
  quecto_failed = 1;
  longjmp(quecto_jmp, 1);
}

extern const quecto_test __start_quecto_tests[];
extern const quecto_test __stop_quecto_tests[];

int quecto_run(void) {
  const quecto_test *test;
  int failed = 0;
  int total = 0;

  for (test = __start_quecto_tests; test < __stop_quecto_tests; test++) {
    total++;

    printf("[ RUN  ] %s\n", test->name);

    if (setjmp(quecto_jmp) == 0)
      test->fn();

    if (quecto_failed) {
      printf("[ FAIL ] %s\n", test->name);
      failed++;
    } else {
      printf("[ PASS ] %s\n", test->name);
    }
  }

  printf("\n%d test%s, %d failed\n", total, total == 1 ? "" : "s", failed);

  return failed != 0;
}

#endif // QUECTO_IMPLEMENTATION

#endif // QUECTO_H
