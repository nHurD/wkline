#include <glib.h>
#include <jansson.h>

#define CONFIG_BUF_SIZE 256

enum wkline_position {
	WKLINE_POSITION_TOP,
	WKLINE_POSITION_BOTTOM
};

typedef struct wkline_config_t {
	int height;
	enum wkline_position position;
	char *theme_uri;
	char *background;
	json_t *widgets_config;
	char **enabled_widgets;
} wkline_config_t;
