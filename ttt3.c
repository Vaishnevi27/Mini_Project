/*    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>


#define playerX 10
#define playerO 20
#define MAXS 10
#define MAX2 100
int player;
int xcount, ocount;
int xno[MAXS][MAXS];
	
typedef struct tablecell{
	int x; 
	int y;
}tablecell;

tablecell id[MAX2];
GtkWidget *cell[MAXS][MAXS];


static int win(){ /*checks winner*/

	
	int i;

	for(i = 0; i < 3; i++){
		if(xno[i][0] == xno[i][1] && xno[i][1] == xno[i][2] && xno[i][2] == 1)
			return 1;

		else if(xno[i][0] == xno[i][1] && xno[i][1] == xno[i][2] && xno[i][2] == 2)
			return 1;
	}

	for(i = 0; i < 3; i++){
		if(xno[0][i] == xno[1][i] && xno[1][i] == xno[2][i] && xno[2][i] == 1)
			return 1;

		if(xno[0][i] == xno[1][i] && xno[1][i] == xno[2][i] && xno[2][i] == 2)
			return 1;
	}

	if(xno[0][0] == xno[1][1] && xno[1][1] == xno[2][2] && xno[2][2] == 1)
		return 1;

	else if(xno[0][0] == xno[1][1] && xno[1][1] == xno[2][2] && xno[2][2] == 2)
		return 1;

	if(xno[2][0] == xno[1][1] && xno[1][1] == xno[0][2] && xno[0][2] == 1)
		return 1;

	if(xno[2][0] == xno[1][1] && xno[1][1] == xno[0][2] && xno[0][2] == 2)
		return 1;

	return 0;

}
static void showxres(){ /*func to show x wins*/

	GtkWidget *wind, *button, *hbox, *image;

	wind = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(wind), 15);

	button = gtk_button_new_with_label("Player Cross Wins");
	image = gtk_image_new_from_file("win.jpg");
	
	hbox = gtk_hbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(wind), hbox);

	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), image, TRUE, TRUE, 0);


	g_signal_connect_swapped(button, "clicked",G_CALLBACK (gtk_widget_destroy),wind);

	gtk_window_fullscreen((GtkWindow *)wind);
	
	gtk_widget_show_all(wind);

}
static void showores(){ /*func to show result when o wins*/

	GtkWidget *wind, *button, *hbox, *image;

	wind = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(wind), 15);

	button = gtk_button_new_with_label("Player Nought Wins");
	image = gtk_image_new_from_file("win.jpg");
	
	hbox = gtk_hbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(wind), hbox);

	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), image, TRUE, TRUE, 0);

	g_signal_connect_swapped(button, "clicked",G_CALLBACK (gtk_widget_destroy),wind);

	gtk_window_fullscreen((GtkWindow *)wind);
	
	gtk_widget_show_all(wind);

}
static void showtieres(){ /*to show result when its a draw*/

	GtkWidget *tie, *button, *hbox, *timage;

	xcount = 0;
	ocount = 0;

	tie = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(tie), 15);

	button = gtk_button_new_with_label("It's a Draw!");
	timage = gtk_image_new_from_file("tie.jpg");
	
	hbox = gtk_hbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(tie), hbox);

	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), timage, TRUE, TRUE, 0);

	g_signal_connect_swapped(button, "clicked",G_CALLBACK (gtk_widget_destroy),tie);

	gtk_window_fullscreen((GtkWindow *)tie);
	
	gtk_widget_show_all(tie);

}

static void altcrossnought( GtkWidget *widget, gpointer data ) { /*function to put alternate cross and nought in the buttons*/

	GtkWidget *cross, *nought;
	tablecell *id = data;
	int res;

	if(player == playerX){
		
		cross = gtk_image_new_from_file("cross1.jpg");
		gtk_container_add (GTK_CONTAINER (cell[id->x][id->y]), cross);
		gtk_widget_show(cross);
		xno[id->y][id->x] = 1;
		xcount++;
	}

	else if(player == playerO){

		nought = gtk_image_new_from_file("nought1.jpg");
		gtk_container_add (GTK_CONTAINER (cell[id->x][id->y]), nought);
		gtk_widget_show(nought);
		xno[id->y][id->x] = 2;
		ocount++;
		
		
	}
	

		if((xcount + ocount) == 9)
			showtieres();
		else {
			res = win();
			if(res == 1){
				if(player == playerX)
					showxres();

				else if(player == playerO)
					showores();
			}
		}

	

	

	

	if(player == playerX){
		player = playerO;
	}
	else if(player == playerO){
		player = playerX;
	}
	

}

static void board( GtkWidget *widget, gpointer data ) { /*draws the board*/

	GtkWidget *wind3;
	GtkWidget *board;
	
	GtkWidget *vbox;
	GtkWidget *quit;

	GdkColor colorwin;

	int i = 0, j = 0;
	
	wind3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(wind3), 15);
	
	board = gtk_table_new(3, 3, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(board), 1); 
	gtk_table_set_col_spacings(GTK_TABLE(board), 1);

	

	player = playerX;
	
	for(i = 0; i < MAXS; i++ ) {
		for(j = 0; j < MAXS; j++ ) {
			xno[i][j] = 0;
		}
	}

	
	unsigned int counter = 0;
	
	for(i = 0; i < 3; i++ ) {
		for(j = 0; j < 3; j++ ) {

				id[counter].x = i;
				id[counter].y = j;
				cell[i][j] = gtk_button_new();
				gtk_signal_connect (GTK_OBJECT (cell[i][j]), "clicked", GTK_SIGNAL_FUNC(altcrossnought), &id[counter] );
				counter++;
				gtk_table_attach_defaults(GTK_TABLE(board),cell[i][j], i, i + 1, j, j + 1 );
				gtk_widget_show (cell[i][j]);
			
			
		}
	}
      
	vbox = gtk_vbox_new(FALSE, 1);
	gtk_container_add(GTK_CONTAINER(wind3), vbox);

	quit = gtk_button_new_with_label("Quit");

	gtk_box_pack_start(GTK_BOX(vbox), board, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), quit, TRUE, TRUE, 0); 

	g_signal_connect_swapped(quit, "clicked",G_CALLBACK (gtk_widget_destroy),wind3);

	gdk_color_parse ("#BED2F7", &colorwin);
	gtk_widget_modify_bg( GTK_WIDGET(wind3), GTK_STATE_NORMAL, &colorwin);

	
	gtk_window_fullscreen((GtkWindow *)(wind3));
	gtk_widget_show_all(wind3);

}

static void info(GtkWidget *widget, gpointer   data ){  /*game information window*/

	GtkWidget *wind;

	GtkWidget *label1, *label3, *label4, *label5;
	
	GtkWidget *vbox;
	GtkWidget *back;

	GdkColor colorwin;
	
	wind = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(wind), 15);
	

	vbox = gtk_vbox_new(TRUE, 5);
	
	gtk_container_add(GTK_CONTAINER(wind), vbox);

	
	label1 = gtk_label_new("* This is a 2 Player TIC TAC TOE game.");
	label3 = gtk_label_new("* The player with Cross 'X' starts first.");
	label4 = gtk_label_new("* The player which completes entire row or column or diagonal with her/his symbol first, wins.");
	label5 = gtk_label_new("BEST OF LUCK!!!");
	
	back = gtk_button_new_with_label("Back");
	
	gtk_box_pack_start(GTK_BOX(vbox), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label3, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label4, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label5, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), back, TRUE, TRUE, 0); 

	g_signal_connect_swapped(back, "clicked",G_CALLBACK (gtk_widget_destroy), wind);

	gdk_color_parse ("#BED2F7", &colorwin);
	gtk_widget_modify_bg( GTK_WIDGET(wind), GTK_STATE_NORMAL, &colorwin);

	gtk_window_fullscreen((GtkWindow *)(wind));
	gtk_widget_show_all(wind);

}

int main( int argc, char *argv[] ) {  /*main window*/

	GtkWidget *wind1;

	GtkWidget *mainmenu;
	GtkWidget *vbox1;

	GtkWidget *ttt;

	GtkWidget *start;
	GtkWidget *information;
	GtkWidget *exit;

	GdkColor bc1, bc2, bc3;
	
	gtk_init(&argc, &argv);

	wind1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(wind1), "Tic Tac Toe");
	gtk_container_set_border_width(GTK_CONTAINER(wind1), 15);
	
	vbox1 = gtk_vbox_new(TRUE, 1);
	gtk_container_add(GTK_CONTAINER(wind1), vbox1);
	mainmenu = gtk_vbox_new( TRUE, 1 );

	ttt = gtk_image_new_from_file("ttt.jpg");

	start = gtk_button_new_with_label("New Game!");
	information = gtk_button_new_with_label("How To Play");
	exit = gtk_button_new_with_label("Exit");

	gtk_box_pack_start(GTK_BOX(mainmenu), start, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), information, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainmenu), exit, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(vbox1), ttt, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox1), mainmenu, FALSE, FALSE, 0);

	g_signal_connect(GTK_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	
	g_signal_connect(GTK_OBJECT(start), "clicked", G_CALLBACK(board), NULL);
	
	g_signal_connect(GTK_OBJECT(information), "clicked", G_CALLBACK(info), NULL);

	
	gdk_color_parse ("#6495ED", &bc1);
	gtk_widget_modify_bg( GTK_WIDGET(start), GTK_STATE_NORMAL, &bc1);

	gdk_color_parse ("#6495ED", &bc2);
	gtk_widget_modify_bg( GTK_WIDGET(information), GTK_STATE_NORMAL, &bc2);

	gdk_color_parse ("#6495ED", &bc3);
	gtk_widget_modify_bg( GTK_WIDGET(exit), GTK_STATE_NORMAL, &bc3);

	
	gtk_window_fullscreen((GtkWindow *)wind1);
	
	gtk_widget_show_all(wind1);

	g_signal_connect(wind1, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	
	gtk_main();

	return 0;
}
