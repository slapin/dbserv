all: server-bindings.h client-bindings.h

#Rule to generate the binding headers
server-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=dbserv --mode=glib-server $<> $@

client-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=dbserv --mode=glib-client $<> $@

