#include "widgets.h"

GThread *widget_threads[LENGTH(wkline_widgets)];

#define MODULE_LOAD_STRING "%s/libwidget_%s.so"

gboolean
update_widget (struct widget *widget) {
	char *script_template = "if(typeof widgets!=='undefined'){try{widgets.update('%s',%s)}catch(e){console.log('Could not update widget: '+e)}}";
	int script_length = 0;
	char *script;

	// Get the length of the script payload.
	script_length = snprintf(NULL,
	                         0,
	                         script_template,
	                         widget->name,
	                         widget->data);
	// Add 1 for \0
	script = malloc(script_length + 1);

#ifdef DEBUG_JSON
	wklog("Updating widget %s: %s", widget->name, widget->data);
#endif
	sprintf(script, script_template, widget->name, widget->data);

	webkit_web_view_execute_script(widget->web_view, script);
	free(script);

	return FALSE; // only run once
}

void
window_object_cleared_cb (WebKitWebView *web_view, GParamSpec *pspec, gpointer context, gpointer window_object, gpointer user_data) {
	struct wkline *wkline = user_data;
	unsigned short i;

	wklog("webkit: window object cleared");
	for (i = 0; i < LENGTH(wkline_widgets); i++) {
		// FIXME this is pretty bad, it should probably join and recreate the threads instead
		if (! widget_threads[i]) {
			struct widget *widget = calloc(0, sizeof(struct widget));

			widget->config = wkline->config;
			widget->web_view = web_view;
			// Dont forget to free this one
			widget->name = strdup(wkline_widgets[i].name);

			wklog("creating thread for widget '%s'", wkline_widgets[i].name);
			widget_threads[i] = g_thread_new(wkline_widgets[i].name, (GThreadFunc)wkline_widgets[i].func, widget);
		}
	}
}

void
wkline_load_widgets(struct wkline *data) {
	json_t *widgets = wkline_get_config(data, "widgets");
	const char *widget_name;
	json_t *widget_data;
	json_t *tmp_value;
	char *module_path;
	int module_path_length;
	GModule *widget_module;
	int widget_count = 0;
	wk_widget_function widget_func;


	if (! widgets) {
		wklog("config error: widgets object not found");
		return;
	}

	// Iterate through the object to determine what to load
	json_object_foreach(widgets, widget_name, widget_data) {
		tmp_value = json_object_get(widget_data, "enabled");
		// If enabled is true, load it
		if (json_typeof(tmp_value) == JSON_TRUE) {
			module_path_length = snprintf(NULL,
				   	0,
				   	MODULE_LOAD_STRING,
				   	WIDGETDIR, 
					widget_name);
			module_path = malloc(module_path_length + 1);
			snprintf(module_path, 
					module_path_length, 
					MODULE_LOAD_STRING, 
					WIDGETDIR, 
					widget_name);
			widget_module = g_module_open(module_path, G_MODULE_BIND_LAZY);
			if (! widget_module) {
				wklog("Unable to load widget");
				continue;
			}

			if (! g_module_symbol(widget_module, "wkline_init", &widget_func)){
				wklog("Unable ot initialize module");
				continue;
			}

			widget_count++;
			
			// Initial initializaton of the collection of widgets.
			if (widget_count == 1) {
				wkline_widgets = malloc(sizeof(struct widget_call *));
			} else {
				struct wkline_widget *tmp = realloc(
						wkline_widgets, 
						sizeof(struct widget_call *) * widget_count
						);
				if (tmp == NULL) {
					wklog("Error loading widgets: Unable to allocate memory");
					return;
				}
			}

			wkline_widgets[(widget_count - 1)].func = widget_func();
			wkline_widgets[(widget_count - 1)].name = strdup(widget_name);

		}  
	}

}

