bin_PROGRAMS = wkline

lib_LTLIBRARIES = libwidget_desktops.la
libwidget_desktops_la_SOURCES = src/widgets/desktops.c
libwidget_desktops_la_CFLAGS = \
	$(GTK3_CFLAGS) \
	$(WEBKIT_CFLAGS) \
	$(JSON_GLIB_CFLAGS) \
	$(XCB_CFLAGS) \
	$(AM_CFLAGS)

wkline_SOURCES = \
	util/copy_prop.c \
	util/log.c \
	util/load_config.c \
	src/wkline.c \
	src/widgets/widgets.c

wkline_LDADD = \
	$(GTK3_LIBS) \
	$(WEBKIT_LIBS) \
	$(XCB_LIBS) \
	$(JSON_GLIB_LIBS)

wkline_CFLAGS = \
	$(GTK3_CFLAGS) \
	$(WEBKIT_CFLAGS) \
	$(XCB_CFLAGS) \
	$(JSON_GLIB_CFLAGS) \
	$(AM_CFLAGS)

if HAVE_LIBMPDCLIENT
lib_LTLIBRARIES += libwidget_now_playing_mpd.la
libwidget_now_playing_mpd_la_SOURCES = src/widgets/now_playing_mpd.c
libwidget_now_playing_mpd_la_LIBADD = $(wkline_LDADD) $(MPD_LIBS)
libwidgetnow_playing_CFLAGS = $(wkline_CFLAGS) $(MPD_CFLAGS)
endif
if HAVE_LIBCURL
lib_LTLIBRARIES += libwidget_weather.la libwidget_external_ip.la
libwidget_weather_la_SOURCES = \
	util/curl.c \
	src/widgets/weather.c

libwidget_external_ip_la_SOURCES = \
    util/curl.c \
	src/widgets/external_ip.c

libwidget_weather_la_CFLAGS = $(wkline_CFLAGS) $(CURL_CFLAGS)
libwidget_external_ip_la_CFLAGS = $(libwidget_weather_la_CFLAGS)
libwidget_weather_la_LIBADD = $(wkline_LDADD) $(CURL_LIBS)
libwidget_external_ip_la_LIBADD = $(wkline_LDADD) $(CURL_LIBS)
endif

if HAVE_DBUS
lib_LTLIBRARIES += libwidget_notifications.la libwidget_battery.la
libwidget_notifications_la_SOURCES = \
	util/dbus_helpers.c \
	src/widgets/notifications.c
libwidget_battery_la_SOURCES = \
	util/dbus_helpers.c \
	src/widgets/battery.c

libwidget_notifications_la_CFLAGS = $(wkline_CFLAGS) $(DBUS_CFLAGS)
libwidget_battery_la_CFLAGS = $(wkline_CFLAGS) $(DBUS_CFLAGS)

libwidget_notifications_la_LIBADD = $(wkline_LDADD) $(DBUS_LIBS)
libwidget_battery_la_LIBADD = $(wkline_LDADD) $(DBUS_LIBS)
endif

if HAVE_ALSA
lib_LTLIBRARIES += libwidget_volume.la
libwidget_volume_la_SOURCES = src/widgets/volume.c
libwidget_volume_la_CFLAGS = $(wkline_CFLAGS) $(ALSA_CFLAGS)
libwidget_volume_la_LIBADD = $(wkline_LDADD) $(ALSA_LIBS)
endif

dist_doc_DATA = README.rst
libdir = @widgetdir@
