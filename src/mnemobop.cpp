#include "common/common.h"
#include "mnemobop_def.h"

#include "flashcards/carddeck.h"
#include "graphics/graphics.h"


/**
 * @brief Lists the flash-cards packets, and request one to load
 * @return a string containing the requested filename if successfull
 * @return an empty string otherwise
 */
/*std::string _listSelection(void)
{
	unsigned int i, iter = 0;

	DIR *dir;
	struct dirent *ent;
	std::string filename;

	std::vector<string> availableLists;
	availableLists.clear();

	std::ifstream infile;

	if((dir = opendir("./lists/")) != NULL)
	{
		// List all files in directory
		printf(""YELLOW"Available flash-card lists :"NORMAL"\n");
		while ((ent = readdir (dir)) != NULL)
		{
			if(ent->d_name[0] != '.')
			{
				availableLists.push_back(string("lists/") + string(ent->d_name));
			}
		}
		closedir (dir);

		if(availableLists.size() == 0)
		{
			printf(""RED"No available flash-card list"NORMAL"\n");
			return "";
		}

		for(i=0; i<availableLists.size(); i++)
		{
			printf(""YELLOW"\t%d) %s"NORMAL"\n", i+1, availableLists[i].c_str());
		}

		do
		{
			cin >> i;

		//3 attemps before error
		if(iter++ >= 3)
		{
			printf(""RED"Failed to load a list"NORMAL"\n");

			return "";
		}

		if(i>availableLists.size() || i<=0)
		{
			printf(""RED"Bad file ID entered : %d "NORMAL"\n", i);
		}
		else
		{
			return availableLists[i-1];
			//_fillFlashCard(availableLists[i-1].c_str());
		}
		}while(i>availableLists.size() || i<=0);

	}
	else
	{
		/// Failed to open directory
		perror(""RED"The following error occurred : "NORMAL"");
		//printf(""RED"ERROR: Failed to open lists directory%s "NORMAL"\n", availableLists[i-1].c_str());

		return "";
	}

	return "";
}*/

/**
 * @brief From a given file, extracts the information to import a new flash-card deck.
 * @return true if the new flash-card deck was successfully filled
 * @return false otherwise
 */
/*bool _fillFlashCard(const char* myDeckFile, CardDeck& myCardDeck)
{
	std::string myline;
	std::ifstream infile;
	vector<std::string> sublines;

	infile.open(myDeckFile);

	if(infile.is_open() == true)
	{
		printf(""GREEN"List opened : %s "NORMAL"\n", myDeckFile);

		while(getline(infile, myline))
		{
			sublines = splitString(myline, ' ');
			if(sublines.size() != 2)
			{
				printf(""RED"Incorrect flash-card list format"NORMAL"\n");

				infile.close();
				return false;
			}
			else
			{
				/// Fill here FlashDeck filler
				myCardDeck.addCard(sublines[0], sublines[1]);
			}
		}

		printf(""GREEN"New flash-card deck successfully imported"NORMAL"\n");
	}
	else
	{
		printf(""RED"Failed to open list : %s "NORMAL"\n", myDeckFile);
	}

	infile.close();

	return true;
}*/

/*class Mnemo
{
	public:
		//Constructors
		Mnemo(void);

	private:
		
};*/


GdkPixbuf* create_pixbuf(const gchar * filename)
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


int main(int argc, char** argv)
{
	GtkWidget*	window;
	
	GdkPixbuf*	icon;
	GtkWidget*	button;
	
	GtkWidget*	grid;
	GtkWidget*	word1;
	GtkWidget*	word2;
	
	CardDeck	cards;
	
	
	gtk_init(&argc, &argv);

	printf("GTK+ version: %d.%d.%d\n", gtk_major_version, gtk_minor_version, gtk_micro_version);
	printf("Glib version: %d.%d.%d\n", glib_major_version, glib_minor_version, glib_micro_version);    
	
	
	//Defines main window properties
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Mnemobop : Language learning made easy");
	//gtk_window_set_default_size(GTK_WINDOW(window), 600, 200);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	
	icon = create_pixbuf("./src/graphics/Blueprint-logo.png");  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	//Flashcard construction
	cards.importDeck("lists/TestList.data");
	//cards.displayDeck();
	
	//Build the central window
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	word1 = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(word1), cards.getWord().c_str());
	gtk_entry_set_alignment(GTK_ENTRY(word1), 0.5);
	gtk_editable_set_editable(GTK_EDITABLE(word1), FALSE);
	gtk_grid_attach(GTK_GRID(grid), word1, 0, 0, 1, 1);

	word2 = gtk_entry_new();
	//gtk_entry_set_text(GTK_ENTRY(word2), "Word 2");
	gtk_entry_set_alignment(GTK_ENTRY(word2), 0.5);
	gtk_editable_set_editable(GTK_EDITABLE(word2), TRUE);
	gtk_grid_attach(GTK_GRID(grid), word2, 1, 0, 1, 1);


	button = gtk_button_new_with_label("Check");
	//g_signal_connect(button, "clicked", G_CALLBACK(&_displayAbout), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);
	
	gtk_widget_show_all(window);
  
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
 
	gtk_main();
}