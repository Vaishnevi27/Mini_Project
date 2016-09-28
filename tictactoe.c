#include<gtk/gtk.h>

//refer to statusbar.c o show whose turn it is in gtk2

int main( int argc, char *argv[] ) {

	GtkWidget *wind1;
	GtkWidget *mainmenu;

	GtkWidget *start;
	GtkWidget *highscore;
	GtkWidget *information;
	GtkWidget *exit;

	
	//GtkWidget *halign;
	
	gtk_init(&argc, &argv);

	wind1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(wind1), "Tic Tac Toe");
	gtk_window_set_default_size(GTK_WINDOW(wind1), 460, 300);
	gtk_container_set_border_width(GTK_CONTAINER(wind1), 15);
	gtk_window_set_position(GTK_WINDOW(wind1), GTK_WIN_POS_CENTER);

	mainmenu = gtk_vbox_new( TRUE, 1 );
	gtk_container_add(GTK_CONTAINER(wind1), mainmenu);

	start = gtk_button_new_with_label("Start Game!");
	highscore = gtk_button_new_with_label("High Score");
	information = gtk_button_new_with_label("How To Play");
	exit = gtk_button_new_with_label("Exit");

	gtk_box_pack_start(GTK_BOX(mainmenu), start, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), highscore, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), information, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), exit, FALSE, FALSE, 0);

	g_signal_connect(GTK_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);

	
	

	/*button = gtk_button_new_with_label("Menu");
	gtk_widget_set_tooltip_text(button, "Button widget");
  
	halign = gtk_alignment_new( 230, 150, 0, 0 );
	gtk_container_add(GTK_CONTAINER(halign), button);
	gtk_container_add(GTK_CONTAINER(window), halign);*/

	
	gtk_widget_show_all(wind1);

	g_signal_connect(wind1, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	gtk_main();

	return 0;
}
