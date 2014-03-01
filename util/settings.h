#include<glib.h>

typedef struct {
	gint line_height;
	gchar *theme_url;
	gsize widget_count;
	gchar **widgets;
	gsize plugin_path_count;
	gchar **plugin_paths;
} main_settings_t;

void set_default_values( main_settings_t **settings);
main_settings_t *read_main_config_file(char *file);
