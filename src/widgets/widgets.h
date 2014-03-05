#include <glib.h>
#include <jansson.h>
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
struct widget_call {
	void *func;
	const char *name;
};

gboolean update_widget (struct widget *widget);
void window_object_cleared_cb (WebKitWebView *web_view, GParamSpec *pspec, gpointer context, gpointer window_object, gpointer user_data);

static const struct widget_call wkline_widgets[] = {

};

#define MISSING_VALUE ""
#define LENGTH(X) (sizeof X / sizeof X[0])
