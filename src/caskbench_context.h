#ifndef __CASKBENCH_CONTEXT_H__    // -*- mode: c++ -*-
#define __CASKBENCH_CONTEXT_H__
#include "shapes.h"
#include "forward.h"
#include "device_config.h"

typedef struct _caskbench_context {
    int              size;
    int              canvas_width;
    int              canvas_height;

    cairo_t         *cairo_cr;
    cairo_surface_t *cairo_surface;

    SkPaint         *skia_paint;
    SkCanvas        *skia_canvas;
    SkBaseDevice    *skia_device;

    cairo_surface_t *(*setup_cairo)(const device_config_t& config);
    SkBaseDevice    *(*setup_skia)(const device_config_t& config);
    void             (*destroy_cairo)(void);
    void             (*destroy_skia)(void);
    void             (*update_cairo)(void);
    void             (*update_skia)(void);

    const char      *stock_image_path;
    shapes_t         shape_defaults;
    double tolerance;

} caskbench_context_t;

// Backend-specific graphics initialization
cairo_surface_t * create_cairo_surface_image (const device_config_t& config);
void destroy_cairo_image();
void update_cairo_image();

SkBaseDevice * create_skia_device_image (const device_config_t& config);
void destroy_skia_image();
void update_skia_image();

#if USE_GLX
cairo_surface_t *create_cairo_surface_glx (const device_config_t& config);
void destroy_cairo_glx();
void update_cairo_glx();

SkBaseDevice * create_skia_device_glx (const device_config_t& config);
void destroy_skia_glx();
void update_skia_glx();
#endif

#if USE_EGL
cairo_surface_t * create_cairo_surface_egl (const device_config_t& config);
void destroy_cairo_egl();
void update_cairo_egl();

SkBaseDevice * create_skia_device_egl (const device_config_t& config);
void destroy_skia_egl();
void update_skia_egl();
#endif


// Context initialization and management
void context_init(caskbench_context_t *context, int size);
void context_setup_cairo(caskbench_context_t *context, const device_config_t& config);
void context_update_cairo(caskbench_context_t *context);
void context_destroy_cairo(caskbench_context_t *context);
void context_setup_skia(caskbench_context_t *context, const device_config_t& config);
void context_update_skia(caskbench_context_t *context);
void context_destroy_skia(caskbench_context_t *context);
#endif // __CASKBENCH_CONTEXT_H__

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

