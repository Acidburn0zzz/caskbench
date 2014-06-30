/*
 * Copyright 2014 © Samsung Research America, Silicon Valley
 *
 * Use of this source code is governed by the 3-Clause BSD license
 * specified in the COPYING file included with this source code.
 */
#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>

#include "caskbench.h"
#include "caskbench_context.h"
#include "cairo-shapes.h"
#include <math.h>

static cairo_surface_t *image;

int
ca_setup_image_scale(caskbench_context_t *ctx)
{
    image = cairoCreateSampleImage (ctx);
    return 1;
}

void
ca_teardown_image_scale(void)
{
    cairo_surface_destroy (image);
}

int
ca_test_image_scale(caskbench_context_t *ctx)
{
    cairo_t *cr = ctx->cairo_cr;

    int w = ctx->canvas_width;
    int h = ctx->canvas_height;
    int iw = cairo_image_surface_get_width (image);
    int ih = cairo_image_surface_get_height (image);
    for (int i=0; i<ctx->size; i++) {
        double x1 = (double)rand()/RAND_MAX * w;
        double x2 = (double)rand()/RAND_MAX * w;
        double y1 = (double)rand()/RAND_MAX * h;
        double y2 = (double)rand()/RAND_MAX * h;
        double x = MIN(x1, x2);
        double y = MIN(y1, y2);
        double width_ratio = float(fabs(x2 - x1)) / float(iw);
        double height_ratio = float(fabs(y2 - y1)) / float(ih);
        double scale_xy = MIN(height_ratio, width_ratio);

        cairo_save(cr);
        cairo_translate(cr,x,y);
        cairo_scale(cr,scale_xy, scale_xy);

        cairo_set_source_surface (cr, image, 0, 0);
        cairo_paint (cr);
        cairo_restore(cr);
    }
    return 1;
}

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
