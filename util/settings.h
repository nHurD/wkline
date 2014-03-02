#include<jansson.h>

typedef struct {
	int line_height;
	char *theme_url;
	json_t *widget_data;
} main_settings_t;

void set_default_values(main_settings_t **settings);
main_settings_t *read_main_config_file(char *file);
