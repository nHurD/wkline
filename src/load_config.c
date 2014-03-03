#include "load_config.h"

#include <string.h>

int
load_config_file (wkline_config_t *config) {
	const char *user_config_file = g_build_filename(g_get_user_config_dir(), "wkline", "config.json", NULL);
	json_error_t err;
	json_t *widget_data;
	json_t *enabled_widgets;
	size_t enabled_widget_length;
	json_t *json_config = json_load_file(user_config_file, 0, &err);
	int idx;

	if (! json_config) {
		fprintf(stderr, "\n***************************\nFailed to load config file!\n***************************\n\n%s\n\nPlease make sure that '%s' exists and contains valid JSON data.\n\n", err.text, user_config_file);
		exit(1);
	}

	config->height = json_integer_value(json_object_get(json_config, "height"));
	config->position = json_string_value(json_object_get(json_config, "position")) == "top" ? WKLINE_POSITION_TOP : WKLINE_POSITION_BOTTOM;
	
	const char *tmp_str = json_string_value(
			json_object_get(json_config, "theme_uri")
			);
	config->theme_uri = strdup(tmp_str);

	tmp_str = json_string_value(json_object_get(json_config, "background"));
	config->background = strdup(tmp_str);

	widget_data = json_object_get(json_config, "widgets_config");
	config->widgets_config = malloc(sizeof(widget_data) * sizeof(json_t *));
	memcpy(config->widgets_config, widget_data, sizeof(widget_data) * sizeof(json_t *));

	// Store enabled widgets
	enabled_widgets = json_object_get(json_config, "widgets_enabled");
	if (enabled_widgets != NULL) {
		enabled_widget_length = json_array_size(enabled_widgets);
		config->enabled_widgets = malloc(enabled_widget_length * sizeof(char *));
		for (idx = 0; idx < enabled_widget_length; idx++) {
			const char *tmp_value = json_string_value(
					json_array_get(enabled_widgets, idx)
					);
			config->enabled_widgets[idx] = strdup(tmp_value);
		}
	}

	json_decref(json_config);

	return 0;
}
