BUILT_SOURCES = server-bindings.h client-bindings.h
# We don't want to install this header
noinst_HEADERS = $(BUILT_SOURCES)

# Correctly clean the generated headers, but keep the xml description
CLEANFILES = $(BUILT_SOURCES)
EXTRA_DIST = servicename-infos.xml

#Rule to generate the binding headers
server-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=server_object --mode=glib-server $<> $@

client-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=server_object --mode=glib-client $<> $@

