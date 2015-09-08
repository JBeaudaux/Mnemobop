#include "graphics.h"


Graphics::Graphics()
{
	//Nothing to do here
}


int Graphics::initGraphics(int argNmb, char** argList)
{
	GtkApplication *app;
	int status;

	//gtk_init(&argNmb, &argList);

	app = gtk_application_new("com.github.username.JBeaudaux.mnemobop", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(&_activate), NULL);
	status = g_application_run(G_APPLICATION(app), argNmb, argList);
	g_object_unref(app);

	return status;
}

void Graphics::_activate(GtkApplication* app, gpointer user_data)
{
	GtkBuilder	*builder;
	GMenuModel	*app_menu;

	GtkWidget	*window;
	GtkWidget	*grid;
	GtkWidget	*button;
	GtkWidget	*entry;

	static GActionEntry app_entries[] =
	{
		{ "quit", quitActivated, NULL, NULL, NULL },
		{ "about", aboutActivated, NULL, NULL, NULL }
	};

	//const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

	g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);

	//g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);
	//gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.quit", quit_accels);

	window = gtk_application_window_new(app);

	gtk_window_set_title(GTK_WINDOW(window), "Mnemobop flash-cards");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 200);

	builder = gtk_builder_new_from_file("./src/graphics/Mnemomenu.ui");
	//builder = gtk_builder_new_from_resource("./src/graphics/Mnemomenu.ui");
	app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "mnemomenu"));
	gtk_application_set_app_menu(GTK_APPLICATION(app), app_menu);

	app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "menufields"));
	gtk_application_set_menubar(GTK_APPLICATION(app), app_menu);
	g_object_unref(builder);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), "Word 1");
	gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);
	gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
	gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);

	entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), "Word 2");
	gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);
	gtk_editable_set_editable(GTK_EDITABLE(entry), TRUE);
	gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);


	button = gtk_button_new_with_label("Check !");
	//g_signal_connect(button, "clicked", G_CALLBACK(&_displayAbout), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

	gtk_widget_show_all(window);
}

void Graphics::preferences_activated(GSimpleAction *action, GVariant* parameter, gpointer app)
{
	g_print("Hello World\n");
}

void Graphics::cb_quit(GtkWidget *p_widget, gpointer user_data)
{
	gtk_main_quit();

	(void)p_widget;
	(void)user_data;
}

void Graphics::_print_hello(GtkWidget *widget, gpointer data)
{
	g_print("Hello World\n");
}

void Graphics::_displayAbout(GtkWidget *widget, gpointer data)
{
	const char* authors[] = { "Julien Beaudaux", "Maryna Bry", NULL };

	gtk_show_about_dialog(NULL,
		"program-name", "Mnemobop",
		"authors", authors,
		"version", "V01.00B1",
		"website", "http://mywebsite",
		"copyright", "Copyright The Blue print project",
		"logo", NULL,
		"license", "My own license",
		NULL);
}


/**
 * @brief Quits the cuttent application. Entered by Quit button in menu or key press.
 */
void Graphics::quitActivated(GSimpleAction *action, GVariant *parameter, gpointer appPtr)
{
	g_application_quit(G_APPLICATION(appPtr));
}

/**
 * @brief Displays application misc. informations. Entered by About button in menu or key press.
 */
void Graphics::aboutActivated(GSimpleAction *action, GVariant *parameter, gpointer appPtr)
{
	const char* authors[] = { "Julien Beaudaux", "Maryna Bry", NULL };

	gtk_show_about_dialog(NULL,
		"program-name", "Mnemobop",
		"authors", authors,
		"version", "V01.00B1",
		"website", "http://mywebsite",
		"copyright", "Copyright The Blue print project",
		"logo", NULL,
		"license", "My own license",
		NULL);
}