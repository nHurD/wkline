bin_PROGRAMS = wkline

lib_LTLIBRARIES = libdesktops.la
libdesktops_la_SOURCES = src/widgets/desktops.c
libdesktops_la_CFLAGS = \
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
lib_LTLIBRARIES += libnow_playing_mpd.la
libnow_playing_mpd_la_SOURCES = src/widgets/now_playing_mpd.c
libnow_playing_mpd_la_LIBADD = $(wkline_LDADD) $(MPD_LIBS)
libnow_playing_CFLAGS = $(wkline_CFLAGS) $(MPD_CFLAGS)
endif
if HAVE_LIBCURL
lib_LTLIBRARIES += libweather.la libexternal_ip.la
libweather_la_SOURCES = \
	util/curl.c \
	src/widgets/weather.c

libexternal_ip_la_SOURCES = \
    util/curl.c \
	src/widgets/external_ip.c

libweather_la_CFLAGS = $(wkline_CFLAGS) $(CURL_CFLAGS)
libexternal_ip_la_CFLAGS = $(libweather_la_CFLAGS)
libweather_la_LIBADD = $(wkline_LDADD) $(CURL_LIBS)
libexternal_ip_la_LIBADD = $(wkline_LDADD) $(CURL_LIBS)
endif

if HAVE_DBUS
lib_LTLIBRARIES += libnotifications.la libbattery.la
libnotifications_la_SOURCES = \
	util/dbus_helpers.c \
	src/widgets/notifications.c
libbattery_la_SOURCES = \
	util/dbus_helpers.c \
	src/widgets/battery.c

libnotifications_la_CFLAGS = $(wkline_CFLAGS) $(DBUS_CFLAGS)
libbattery_la_CFLAGS = $(wkline_CFLAGS) $(DBUS_CFLAGS)

libnotifications_la_LIBADD = $(wkline_LDADD) $(DBUS_LIBS)
libbattery_la_LIBADD = $(wkline_LDADD) $(DBUS_LIBS)
endif

if HAVE_ALSA
lib_LTLIBRARIES += libvolume.la
libvolume_la_SOURCES = src/widgets/volume.c
libvolume_la_CFLAGS = $(wkline_CFLAGS) $(ALSA_CFLAGS)
libvolume_la_LIBADD = $(wkline_LDADD) $(ALSA_LIBS)
endif

dist_doc_DATA = README.rst
