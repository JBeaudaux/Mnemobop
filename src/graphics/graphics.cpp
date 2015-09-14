#include "graphics.h"


//Declaration of class members
CardDeck Graphics::myDeck;

GtkWidget*	Graphics::entryWord1;
GtkWidget*	Graphics::entryWord2;
GtkWidget*	Graphics::resultLabel;

Graphics::Graphics()
{
	//Nothing to do here
}


int Graphics::initGraphics(int argNmb, char** argList)
{
	GtkApplication *app;
	int status;

	//gtk_init(&argNmb, &argList);
	
	printf("GTK+ version: %d.%d.%d\n", gtk_major_version, gtk_minor_version, gtk_micro_version);
	printf("Glib version: %d.%d.%d\n", glib_major_version, glib_minor_version, glib_micro_version);

	app = gtk_application_new("com.github.username.JBeaudaux.mnemobop", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(&_activate), NULL);
	status = g_application_run(G_APPLICATION(app), argNmb, argList);
	g_object_unref(app);

	return status;
}

GdkPixbuf* Graphics::create_pixbuf(const gchar * filename)
{
	GdkPixbuf* pixbuf;
	GError* error = NULL;
	
	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf)
	{
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}

	return pixbuf;
}

void Graphics::_mnemohome_init(MnemoAppWindow *win)
{
	gtk_widget_init_template(GTK_WIDGET (win));
}

void Graphics::_activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget*	window;
	
	GdkPixbuf*	icon;
	GtkWidget*	button;
	
	GtkWidget*	grid;

	//Load flashcards deck
	myDeck.importDeck("lists/TestList.data");
	myDeck.displayDeck();
	
	
	//Defines main window properties
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Mnemobop : Language learning made easy");
	//gtk_window_set_default_size(GTK_WINDOW(window), 600, 200);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	
	icon = create_pixbuf("./src/graphics/Blueprint-logo.png");  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	//Build the central window
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	entryWord1 = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entryWord1), myDeck.getWord().c_str());
	gtk_entry_set_alignment(GTK_ENTRY(entryWord1), 0.5);
	gtk_editable_set_editable(GTK_EDITABLE(entryWord1), FALSE);
	gtk_grid_attach(GTK_GRID(grid), entryWord1, 0, 0, 1, 1);

	entryWord2 = gtk_entry_new();
	//gtk_entry_set_text(GTK_ENTRY(entryWord2), "Word 2");
	gtk_entry_set_alignment(GTK_ENTRY(entryWord2), 0.5);
	gtk_editable_set_editable(GTK_EDITABLE(entryWord2), TRUE);
	gtk_grid_attach(GTK_GRID(grid), entryWord2, 1, 0, 1, 1);


	button = gtk_button_new_with_label("Check");
	g_signal_connect(button, "clicked", G_CALLBACK(&checkWord), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

	resultLabel = gtk_label_new("Find translation");
	gtk_grid_attach(GTK_GRID(grid), resultLabel, 0, 2, 2, 1);
	
	gtk_widget_show_all(window);
  
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
 
	gtk_main();
		
		
	/*
	GtkBuilder	*builder;
	GMenuModel	*app_menu;

	GtkWidget	*window;
	GtkWidget	*grid;
	GtkWidget	*button;
	GtkWidget	*buttonBox;
	//GtkWidget	*entry;

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
	
	
	buttonBox = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(buttonBox), GTK_BUTTONBOX_START);
	
	button = gtk_button_new_with_label("Lesson");*/
	//buttonBox.add(button);
	
	
	/*button = gtk_button_new_with_label("Lesson");
	//g_signal_connect(button, "clicked", G_CALLBACK(&_displayAbout), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
	
	button = gtk_button_new_with_label("Flashcards");
	//g_signal_connect(button, "clicked", G_CALLBACK(&_displayAbout), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);
	
	button = gtk_button_new_with_label("Grammar");
	//g_signal_connect(button, "clicked", G_CALLBACK(&_displayAbout), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 3, 0, 3, 3);*/
	

	/*grid = gtk_grid_new();
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
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);*/

	//gtk_widget_show_all(window);
}

void Graphics::checkWord(GtkWidget *widget, gpointer data)
{
	const gchar* buffer;
	buffer = gtk_entry_get_text(GTK_ENTRY(entryWord2));

	if(strcmp(buffer, myDeck.getAnswer().c_str()) == 0)
	{
		//printf("perfect!\n");
		gtk_label_set_text(GTK_LABEL(resultLabel), "Correct :-)");
		myDeck.removeFromDeck();
	}
	else
	{
		//printf("snif\n");
		gtk_label_set_text(GTK_LABEL(resultLabel), "Incorrect result :-(");
		myDeck.duplicateInDeck();
	}

	while( gtk_events_pending() )
	{
    	gtk_main_iteration();
    }

	//sleep(1);

    if(myDeck.remainingWords() > 0)
    {
		gtk_entry_set_text(GTK_ENTRY(entryWord1), myDeck.getWord().c_str());
		gtk_entry_set_text(GTK_ENTRY(entryWord2), "");
		//gtk_label_set_text(GTK_LABEL(resultLabel), "Find translation");
    }
    else
    {
    	gtk_entry_set_text(GTK_ENTRY(entryWord1), "");
		gtk_entry_set_text(GTK_ENTRY(entryWord2), "");
    	gtk_label_set_text(GTK_LABEL(resultLabel), "Congratulation, you finished the deck!");
    }
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