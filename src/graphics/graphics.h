#include <gtk/gtk.h>
#include <gio/gio.h>

struct MnemoAppWindow
{
	GtkApplicationWindow parent;
};

struct MnemoAppWindowClass
{
	GtkApplicationWindowClass parent_class;
};

class Graphics
{
	public:
		//Constructors
		Graphics(void);

		//Other methods
		int initGraphics(int argNmb, char** argList);
		void cb_quit(GtkWidget *p_widget, gpointer user_data);

	private:
		//GMenuModel *myMenuModel;

		static void _activate (GtkApplication* app, gpointer user_data);
		static void _print_hello (GtkWidget *widget, gpointer data);
		static void _displayAbout(GtkWidget *widget, gpointer data);
		static void preferences_activated(GSimpleAction *action, GVariant* parameter, gpointer app);

		static void quitActivated(GSimpleAction *action, GVariant *parameter, gpointer appPtr);
		static void aboutActivated(GSimpleAction *action, GVariant *parameter, gpointer appPtr);
		
		static void _mnemohome_init(MnemoAppWindow *win);
};