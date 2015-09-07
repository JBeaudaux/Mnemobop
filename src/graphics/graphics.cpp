#include "graphics.h"


Graphics::Graphics()
{
	//Nothing to do here
}


int Graphics::initGraphics(int argNmb, char** argList)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("com.github.username.JBeaudaux.mnemobop", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(&_activate), NULL);
	status = g_application_run(G_APPLICATION(app), argNmb, argList);
	g_object_unref(app);

	return status;
}

void Graphics::_activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button;
	//GtkWidget *button_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Mnemobop flash-cards");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	button = gtk_button_new_with_label("Hello World 1");
	g_signal_connect(button, "clicked", G_CALLBACK(&_print_hello), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

	button = gtk_button_new_with_label("Hello World 2");
	g_signal_connect(button, "clicked", G_CALLBACK(&_print_hello), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

	button = gtk_button_new_with_label("Hello World 3");
	g_signal_connect(button, "clicked", G_CALLBACK(&_print_hello), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);



	/*button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(window), button_box);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", G_CALLBACK(&_print_hello), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(button_box), button);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);*/

	gtk_widget_show_all(window);
}

void Graphics::cb_quit(GtkWidget *p_widget, gpointer user_data)
{
	gtk_main_quit();

	(void)p_widget;
	(void)user_data;
}

void Graphics::_print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}