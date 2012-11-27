#include <dbus/dbus-glib-bindings.h>
/* Standard GObject class structures, etc */
typedef struct
{
	GObjectClass parent;
} ServerObjectClass;

typedef struct
{
	GObject parent;
	unsigned char data[80];
	GHashTable *reg;
} ServerObject;

static gboolean
server_setreg(ServerObject *server, GValue *key, GValue *value,
	GError **error);
static gboolean
server_getreg(ServerObject *server, GValue *key, GValue **value,
	GError **error);
static gboolean
server_select(ServerObject *server,
	GError **error);
static gboolean
server_count(ServerObject *server,
	GError **error);
static gboolean
server_delete(ServerObject *server,
	GError **error);

#include "server-bindings.h"


#define SERVER_TYPE_OBJECT (server_object_get_type())

#define SERVER_OBJECT(object) \
        (G_TYPE_CHECK_INSTANCE_CAST((object), \
         SERVER_TYPE_OBJECT, ServerObject))
#define SERVER_OBJECT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST((klass), \
         VALUE_TYPE_OBJECT, ServerObjectClass))
#define SERVER_IS_OBJECT(object) \
        (G_TYPE_CHECK_INSTANCE_TYPE((object), \
         SERVER_TYPE_OBJECT))
#define SERVER_IS_OBJECT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE((klass), \
         SERVER_TYPE_OBJECT))
#define SERVER_OBJECT_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS((obj), \
         SERVER_TYPE_OBJECT, ServerObjectClass))

G_DEFINE_TYPE(ServerObject, server_object, G_TYPE_OBJECT)

static void server_object_class_init(ServerObjectClass *klass)
{
	GError *error = NULL;
	g_assert(klass != NULL);

#if 0
	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
	if (klass->connection == NULL)
	{
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}
#endif

	/* &dbus_glib__object_info is provided in the server-bindings.h file */
	/* OBJECT_TYPE_SERVER is the GType of your server object */
	dbus_g_object_type_install_info (SERVER_TYPE_OBJECT, &dbus_glib_dbserv_object_info);
}

static void server_object_init(ServerObject *server)
{
	g_assert(server != NULL);
	g_print("called");
	server->reg = g_hash_table_new(g_str_hash, g_str_equal);
#if 0
	GError *error = NULL;
	DBusGProxy *driver_proxy;
	int request_ret;

	/* Register the service name, the constant here are defined in dbus-glib-bindings.h */
	driver_proxy = dbus_g_proxy_new_for_name (klass->connection,
			DBUS_SERVICE_DBUS,
			DBUS_PATH_DBUS,
			DBUS_INTERFACE_DBUS);

	if(!org_freedesktop_DBus_request_name (driver_proxy,
			"ru.itetra.Database",
			0, &request_ret,    /* See tutorial for more infos about these */
			&error))
	{
		g_warning("Unable to register service: %s", error->message);
		g_error_free (error);
	}
	g_object_unref (driver_proxy);
#endif
}

static gboolean
server_setreg (ServerObject *server, GValue *key, GValue *value, GError **error)
{
	g_print("CALLED\n");
	if (G_VALUE_TYPE(key) == G_TYPE_STRING) {
		g_print(g_value_get_string(key));
		g_hash_table_insert(server->reg, key, value);
	}
#if 0
	*echo = g_strdup (original);

	if (problem)
	{
		/* We have an error, set the gerror */
		g_set_error (error, g_quark_from_static_string ("echo"),
					0xdeadbeef,
					"Some random problem occured, you're screwed");
		return FALSE;
	}
#endif
	return TRUE;
}

static gboolean
server_getreg(ServerObject *server, GValue *key, GValue **value, GError **error)
{
	*value = g_hash_table_lookup(server->reg, key);
	return TRUE;
}

static gboolean
server_select(ServerObject *server, GError **error)
{
	return TRUE;
}

static gboolean
server_count(ServerObject *server, GError **error)
{
	return TRUE;
}


static gboolean
server_delete(ServerObject *server, GError **error)
{
	return TRUE;
}

int main()
{
	GMainLoop* mainloop = NULL;
	DBusGConnection* bus = NULL;
	ServerObject *srv;
	GError* error = NULL;
	DBusGProxy* busProxy = NULL;
	int ret;
	unsigned int result;

	g_type_init();
	mainloop = g_main_loop_new(NULL, FALSE);
	g_assert(mainloop != NULL);
	bus = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
	busProxy = dbus_g_proxy_new_for_name(bus,
				DBUS_SERVICE_DBUS,
				DBUS_PATH_DBUS,
				DBUS_INTERFACE_DBUS);
	g_assert(busProxy != NULL);
	ret = dbus_g_proxy_call(busProxy,
			"RequestName",
			&error,
			G_TYPE_STRING,
			"ru.itetra.Database",
			G_TYPE_UINT,
			0,
			G_TYPE_INVALID,
			G_TYPE_UINT,
			&result,
			G_TYPE_INVALID);
	if (ret == 0) {
		g_error(error->message);
		return 1;
	}
	g_assert(result == 1);
	srv = g_object_new(SERVER_TYPE_OBJECT, NULL);
	g_assert(srv != NULL);
	dbus_g_connection_register_g_object(bus,
				"/",
				G_OBJECT(srv));
	g_main_loop_run(mainloop);
	return 0;
}

