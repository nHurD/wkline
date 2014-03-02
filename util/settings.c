#include "settings.h"


void
set_default_values(main_settings_t **settings) {

}

main_settings_t *
read_main_config_file(char *file) {
	main_settings_t *config;
	json_t *data;
	json_t *itm_data;
	json_error_t error_data;
	int str_size = 0;

	config = malloc(sizeof(main_settings_t));

	data = json_load_file(file, JSON_DECODE_ANY, &error_data);


	if (data == NULL) {
		// Set default settings
		return NULL;
	}

	itm_data = json_object_get(data, "line_height");

	// Line Height
	if (itm_data == NULL) {
		config->line_height=26;
	} else {
		config->line_height = json_integer_value(itm_data);
	}

	// Theme_url
	itm_data = json_object_get(data, "theme_url");
	if (itm_data == NULL) {
		config->theme_url = "http://lokaltog.github.io/wkline-theme-default/";
	} else {
		str_size = snprintf(NULL, 0, json_string_value(itm_data));
		config->theme_url = malloc(str_size + 1);
		snprintf(config->theme_url,
				(str_size + 1),
				json_string_value(itm_data));

	}

	// Widgets
	itm_data = json_object_get(data, "widgets");
	if (itm_data == NULL) {
		config->widget_count = 0;
		config->widget_data = NULL;
	} else {
		// Save the array size and the information for later.
		config->widget_count = json_array_size(itm_data);
		config->widget_data = itm_data;
	}


	return config;

}
