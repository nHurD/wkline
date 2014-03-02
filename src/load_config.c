#include "load_config.h"

#include <string.h>

int
load_config_file (wkline_config_t *config) {
	const char *user_config_file = g_build_filename(g_get_user_config_dir(), "wkline", "config.json", NULL);
	json_error_t err;
	json_t *json_config = json_load_file(user_config_file, 0, &err);
	json_t *widget_data;

	if (! json_config) {
		fprintf(stderr, "\n***************************\nFailed to load config file!\n***************************\n\n%s\n\nPlease make sure that '%s' exists and contains valid JSON data.\n\n", err.text, user_config_file);
		exit(1);
	}

	widget_data = json_object_get(json_config, "widgets");

	config->height = json_integer_value(json_object_get(json_config, "height"));
	config->position = json_string_value(json_object_get(json_config, "position")) == "top" ? WKLINE_POSITION_TOP : WKLINE_POSITION_BOTTOM;
	config->widget_data = widget_data;

	strcpy(config->theme_uri, json_string_value(json_object_get(json_config, "theme_uri")));
	strcpy(config->background, json_string_value(json_object_get(json_config, "background")));

	return 0;
}
