all: server-bindings.h client-bindings.h server

#Rule to generate the binding headers
server-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=dbserv --mode=glib-server $<> $@

client-bindings.h:  servicename-infos.xml
	dbus-binding-tool --prefix=dbserv --mode=glib-client $<> $@

server: server.o
	$(CC) $(LDFLAGS) $< \
		$(shell pkg-config glib-2.0 dbus-glib-1 --libs) -o $@
server.o: server.c server-bindings.h
	$(CC) $(CFLAGS) $(shell pkg-config glib-2.0 dbus-glib-1 --cflags) -c $< -o $@

