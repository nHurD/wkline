#include <glib.h>
#include <jansson.h>
#include <xcb/xcb_ewmh.h>

typedef struct widget_data_t {
	char *widget;
	char *data;
} widget_data_t;

gboolean update_widget (widget_data_t *widget_data);

static const void *wkline_widgets[] = {
};

#define MISSING_VALUE ""
