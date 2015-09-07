#include <gtk/gtk.h>

class Graphics
{
	public:
		//Constructors
		Graphics(void);

		//Other methods
		int initGraphics(int argNmb, char** argList);
		void cb_quit(GtkWidget *p_widget, gpointer user_data);

	private:
		static void _activate (GtkApplication* app, gpointer user_data);
		static void _print_hello (GtkWidget *widget, gpointer data);
		
};