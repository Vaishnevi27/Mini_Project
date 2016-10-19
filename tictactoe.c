#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>


static void enter_callback( GtkWidget *widget, GtkWidget *cell ){
	const gchar *entry_text[3][3];
	int i = 0, j = 0;
	int xcount = 0;
	char cross[2] = "X";
	
	int xflag0 = 0, xflag1 = 0, xflag2 = 0, xflag3 = 0;

	
	for(i = 0; i < 3; i++ ) {
			for(j = 0; j < 3; j++ ) {
				entry_text[i][j] = gtk_entry_get_text (GTK_ENTRY (cell));
				if(*entry_text[i][j] == 'X'){
					xcount++;
				}
			}
	}
	
	if(xcount >= 3){
	
		for(i = 0; i < 3; i++ ) {
			for(j = 0; j < 3; j++ ) {

				if((strcmp(entry_text[0][0], entry_text[0][1]) == 0) && (strcmp(entry_text[0][1], entry_text[0][2]) == 0) && (strcmp(entry_text[0][2], cross) == 0)) {
					xflag0 = 1;
				}

				if((strcmp(entry_text[1][0], entry_text[1][1]) == 0) && (strcmp(entry_text[1][1], entry_text[1][2]) == 0)  && (strcmp(entry_text[1][2], cross) == 0)) {
					xflag1 = 1;
				}

				if((strcmp(entry_text[2][0], entry_text[2][1]) == 0) && (strcmp(entry_text[2][1], entry_text[2][2]) == 0) && (strcmp(entry_text[2][2], cross) == 0)) {
					xflag2 = 1;
				}

				if((strcmp(entry_text[0][0], entry_text[1][1]) == 0) && (strcmp(entry_text[1][1], entry_text[2][2]) == 0) && (strcmp(entry_text[2][2], cross) == 0)) {
					xflag3 = 1;
				}
				
									
			}
		}

		if(xflag0 == 1 || xflag1 == 1 || xflag2 == 1 || xflag3 == 1) {

					printf("Player X wins!\n");
					
				}	
			
	
	}
}


static void board( GtkWidget *widget, gpointer data ) {

	GtkWidget *wind3;

	GtkWidget *board;
	GtkWidget *cell;

	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *save;
	GtkWidget *quit;

	GtkWidget *valign;
	GtkWidget *halign;

	GtkWidget *button; /*for text entry*/

	wind3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(wind3), 15);
	

	
	board = gtk_table_new(3, 3, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(board), 1); //spacing btw rows n columns is of 1 pixel
	gtk_table_set_col_spacings(GTK_TABLE(board), 1);


	int i = 0, j = 0;
	
	for(i = 0; i < 3; i++ ) {
		for(j = 0; j < 3; j++ ) {

			cell = gtk_entry_new ();
			gtk_entry_set_max_length (GTK_ENTRY (cell), 1);
    			g_signal_connect (cell, "activate",G_CALLBACK (enter_callback),cell);
			gtk_table_attach_defaults(GTK_TABLE(board), cell, i, i + 1, j, j + 1 );
			
		}
	}

	vbox = gtk_vbox_new(TRUE, 5);
	
	valign = gtk_alignment_new(0, 1, 0, 0);
	gtk_container_add(GTK_CONTAINER(vbox), valign);
	gtk_container_add(GTK_CONTAINER(wind3), vbox);
	
	hbox = gtk_hbox_new(TRUE, 3);
 
	save = gtk_button_new_with_label("Save");
	gtk_container_add(GTK_CONTAINER(hbox), save);
	quit = gtk_button_new_with_label("Quit");
	gtk_container_add(GTK_CONTAINER(hbox), quit);

	
	halign = gtk_alignment_new(1, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(halign), hbox);

	gtk_box_pack_start(GTK_BOX(vbox), board, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), halign, TRUE, TRUE, 0); 

	g_signal_connect_swapped (quit, "clicked",G_CALLBACK (gtk_widget_destroy),wind3);

	gtk_window_fullscreen((GtkWindow *)wind3);
	gtk_widget_show_all(wind3);



}

static void player_info( GtkWidget *widget, gpointer   data ) {

	GtkWidget *wind2;

	GtkWidget *done;

	GtkWidget *table;

	GtkWidget *vbox;

	GtkWidget *label1; /*label*/
	GtkWidget *label2;
	GtkWidget *label3;

	GtkWidget *cross;
	GSList *group; /*radio*/
	
	
	GtkWidget *name; /*entry*/
	GtkWidget *size;

	char *temp;

	GtkWidget *separator1;
	GtkWidget *separator2;

	
	wind2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(wind2), "Tic Tac Toe");
	gtk_container_set_border_width(GTK_CONTAINER(wind2), 15);

	vbox = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(wind2), vbox);
	
	table = gtk_table_new(2, 2, FALSE);
	
	label1 = gtk_label_new("Enter your Name");
	label2 = gtk_label_new("Enter Board size(<100)");

	gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	name = gtk_entry_new();
	size = gtk_entry_new();

	gtk_table_attach(GTK_TABLE(table), name, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), size, 1, 2, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 0);

	separator1 = gtk_hseparator_new ();
	gtk_box_pack_start(GTK_BOX(vbox), separator1, TRUE, TRUE, 0);

	label3 = gtk_label_new("Choose");
	gtk_box_pack_start(GTK_BOX(vbox), label3, TRUE, TRUE, 0);

	cross = gtk_radio_button_new_with_label (NULL, "cross 'X'");
	gtk_box_pack_start (GTK_BOX (vbox), cross, TRUE, TRUE, 0);
	gtk_widget_show (cross);
	group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (cross));
	cross = gtk_radio_button_new_with_label (group, "nought 'O'");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (cross), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox), cross, TRUE, TRUE, 0);
	gtk_widget_show (cross);

	separator2 = gtk_hseparator_new ();
	gtk_box_pack_start(GTK_BOX(vbox), separator2, TRUE, TRUE, 0);

	done = gtk_button_new_with_label("Done");
	gtk_box_pack_start(GTK_BOX(vbox), done, TRUE, TRUE, 0);

	g_signal_connect (GTK_OBJECT(done), "clicked", G_CALLBACK(board), NULL);
	g_signal_connect_swapped (done, "clicked",G_CALLBACK (gtk_widget_destroy),wind2);


	gtk_widget_show(done);
	gtk_window_fullscreen((GtkWindow *)wind2);
	gtk_widget_show_all(wind2);

}



int main( int argc, char *argv[] ) {

	GtkWidget *wind1;
	GtkWidget *mainmenu;

	GtkWidget *start;
	//GtkWidget *highscore;
	GtkWidget *information;
	GtkWidget *exit;


	gtk_init(&argc, &argv);

	wind1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(wind1), "Tic Tac Toe");
	gtk_container_set_border_width(GTK_CONTAINER(wind1), 15);

	mainmenu = gtk_vbox_new( TRUE, 1 );
	gtk_container_add(GTK_CONTAINER(wind1), mainmenu);

	start = gtk_button_new_with_label("Start Game!");
	//highscore = gtk_button_new_with_label("High Score");
	information = gtk_button_new_with_label("How To Play");
	exit = gtk_button_new_with_label("Exit");

	gtk_box_pack_start(GTK_BOX(mainmenu), start, FALSE, FALSE, 0);
	//gtk_box_pack_start(GTK_BOX(mainmenu), highscore, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), information, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), exit, FALSE, FALSE, 0);

	g_signal_connect(GTK_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	
	g_signal_connect(GTK_OBJECT(start), "clicked", G_CALLBACK(player_info), NULL);
	
	/*g_signal_connect(GTK_OBJECT(information), "clicked", G_CALLBACK(information), NULL);*/

	/*g_signal_connect(GTK_OBJECT(highscore), "clicked", G_CALLBACK(highscore), NULL);*/
	

	gtk_window_fullscreen((GtkWindow *)wind1);
	
	gtk_widget_show_all(wind1);

	g_signal_connect(wind1, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	gtk_main();

	return 0;
}
