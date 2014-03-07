#include <stdlib.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <string.h>
#include <webkit/webkit.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef WKLINE_H
#define WKLINE_H
struct wkline_dimensions {
	int w;
	int h;
};

struct wkline {
	struct wkline_dimensions dim;
	json_t *config;
	const char *position;
};
#endif
