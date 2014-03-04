#include <glib.h>
#include <jansson.h>
#include <string.h>
#include <webkit/webkit.h>
#include <xcb/xcb_ewmh.h>

typedef struct widget_data_t {
	char widget[32];
	char *data;
	WebKitWebView *web_view;
} widget_data_t;

typedef struct widget_t {
	void *func;
	char id[32];
	widget_data_t *data;
} widget_t;


gboolean update_widget (widget_data_t *widget_data);
void window_object_cleared_cb(WebKitWebView  *web_view,
                              WebKitWebFrame *frame,
                              gpointer context,
                              gpointer window_object,
                              gpointer user_data);

static const widget_t widgets[] = {

};

#define MISSING_VALUE ""
#define LENGTH(X) (sizeof X / sizeof X[0])
