#include <stdlib.h>
#include <glib.h>
#include <jansson.h>
#include "../wkline.h"
#include <string.h>
#include <webkit/webkit.h>
#include <xcb/xcb_ewmh.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

struct widget {
	const char *name;
	json_t *config;
	WebKitWebView *web_view;
	char *data;
};

typedef void (* widget_handler) (struct widget *widget);

struct widget_call {
	widget_handler *func;
	const char *name;
};

typedef struct widget_call widget_call_t;

typedef widget_handler (* wk_widget_function) ();

void wkline_load_widgets(struct wkline *wkline);

gboolean update_widget (struct widget *widget);
void window_object_cleared_cb (WebKitWebView *web_view, GParamSpec *pspec, gpointer context, gpointer window_object, gpointer user_data);

struct widget_call *wkline_widgets;

#define MISSING_VALUE ""
#define LENGTH(X) (sizeof X / sizeof X[0])
