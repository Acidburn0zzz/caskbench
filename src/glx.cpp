/*
 * Copyright 2014 © Samsung Research America, Silicon Valley
 *
 * Use of this source code is governed by the 3-Clause BSD license
 * specified in the COPYING file included with this source code.
 */
#include <config.h>

#include <err.h>
#include <stdlib.h>

#include "glx.h"
#include "device_config.h"

bool
createGLXContextAndWindow(glx_state_t *state, const device_config_t& device_config)
{
    int rgba_attribs[] = {
        GLX_RGBA         ,
        GLX_RED_SIZE     , 1,
        GLX_GREEN_SIZE   , 1,
        GLX_BLUE_SIZE    , 1,
        GLX_ALPHA_SIZE   , 1,
        //GLX_STENCIL_SIZE , 8,
        //GLX_DOUBLEBUFFER , True,
        None
    };
    XVisualInfo *visinfo;
    XSetWindowAttributes attrs;

    state->dpy = XOpenDisplay (NULL);
    if (!state->dpy) {
        warnx ("Failed to open display: %s\n", XDisplayName (0));
        return false;
    }

    visinfo = glXChooseVisual (state->dpy, DefaultScreen (state->dpy), rgba_attribs);
    if (visinfo == NULL) {
        warnx ("Failed to create RGBA and double-buffered visuals\n");
        XCloseDisplay (state->dpy);
        return NULL;
    }

    attrs.colormap = XCreateColormap (state->dpy,
                                      RootWindow (state->dpy, visinfo->screen),
                                      visinfo->visual, AllocNone);
    attrs.border_pixel = 0;
    state->window = XCreateWindow (state->dpy, DefaultRootWindow (state->dpy),
                                   0, 0,
                                   device_config.width, device_config.height,
                                   0, // border width
                                   visinfo->depth,
                                   InputOutput, visinfo->visual,
                                   CWBorderPixel | CWColormap | CWEventMask,
                                   &attrs);
    state->width = device_config.width;
    state->height = device_config.height;
    XMapWindow (state->dpy, state->window);

    //state->gc = XCreateGC(state->dpy, state->window, 0, NULL);

    state->glx_context = glXCreateContext (state->dpy, visinfo, NULL, True);
    XFree (visinfo);

    if (state->glx_context == NULL) {
        warnx ("Could not create glx context\n");
        XCloseDisplay (state->dpy);
        return false;
    }

    return true;
}

void
destroyGLXContextAndWindow (glx_state_t *state)
{
    if (state->dpy) {
        if (state->glx_context)
            glXDestroyContext (state->dpy, state->glx_context);

        // XFreeGC (state->dpy, state->gc);
        XDestroyWindow (state->dpy, state->window);
        XCloseDisplay (state->dpy);
    }
}

void
cleanup_state_glx (void *data)
{
    glx_state_t *state = (glx_state_t*)data;
    destroyGLXContextAndWindow(state);
    free(state);
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
