/*
 * Copyright 2014 © Samsung Research America, Silicon Valley
 *
 * Use of this source code is governed by the 3-Clause BSD license
 * specified in the COPYING file included with this source code.
 */
#ifndef __TESTS_H__
#define __TESTS_H__

#include "forward.h"

typedef struct _caskbench_perf_test {
  const char *name;
  int (*setup)(struct _caskbench_context*);
  void (*teardown)(void);
  int (*test_case)(struct _caskbench_context*);
  void (*write_image)(const char *, struct _caskbench_context*);
  void (*context_setup)(struct _caskbench_context*, const device_config_t& config);
  void (*context_destroy)(struct _caskbench_context*);
  void (*context_update)(struct _caskbench_context*);
  void (*context_clear)(struct _caskbench_context*);
} caskbench_perf_test_t;

extern caskbench_perf_test_t perf_tests[];
extern const int num_perf_tests;

void   write_image_file_cairo(const char *fname, struct _caskbench_context *context);
void   write_image_file_skia(const char *fname, struct _caskbench_context *context);

void   context_setup_cairo(struct _caskbench_context *context, const device_config_t& config);
void   context_setup_skia(struct _caskbench_context *context, const device_config_t& config);

void   context_destroy_cairo(struct _caskbench_context *context);
void   context_destroy_skia(struct _caskbench_context *context);

void   context_update_cairo(struct _caskbench_context *context);
void   context_update_skia(struct _caskbench_context *context);

void   context_clear_cairo(struct _caskbench_context *context);
void   context_clear_skia(struct _caskbench_context *context);
#endif // __TESTS_H__
/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
