#include "settings.h"

void
set_default_values(main_settings_t **settings) {

}

main_settings_t *
read_main_config_file(char *file) {
	main_settings_t *config;
	GKeyFile *key_file;
	GKeyFileFlags flags;
	GError *error = NULL;

	key_file = g_key_file_new();
	flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;

	if ( !g_key_file_load_from_file(key_file, file,flags, &error)) {
		g_error(error->message);
		return NULL;
	}

	/* Initialize the settings object */
	config = g_slice_new(main_settings_t);

	config->line_height = g_key_file_get_integer(key_file,
												  "main",
												  "line_height",
												  NULL);

	config->theme_url = g_key_file_get_string(key_file,
											  "main",
											  "theme_url",
											  NULL);

	config->widgets = g_key_file_get_string_list(key_file,
												 "main",
												 "widgets",
												 &config->widget_count,
												 NULL);

	config->plugin_paths = g_key_file_get_string_list(key_file,
												 "main",
												 "widgets",
												 &config->plugin_path_count,
												 NULL);

	return config;

}
