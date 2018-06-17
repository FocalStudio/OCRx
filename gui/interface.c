/*
OCRX's GUI INTERFACE 
Version 3.42
By @Find3r
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <gtk/gtk.h>
#include "interface.h"

GtkWidget *main_window;    //Main Window
GtkWidget *about_window;   //About Window
GtkWidget *result_window;  //Result Window
GtkWidget *text_view;      //GtkTextView with the result
char *filename;            //Path to the image
GtkWidget *result_img;

#define SIZE_max 1000
gboolean start_ocrx(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	UNUSED(widget);
	UNUSED(event);
	struct components *elm = (struct components *) data;

	//(Start) Recovery Result
	FILE* temp = NULL;
    char result[SIZE_max] = "";
    temp = fopen("icon/temp.txt", "r");
 
    if (temp != NULL)
    {
        fgets(result, SIZE_max, temp);
        fclose(temp);
    }
	//(End) Recovery Result

	elm->text = result;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(elm->text_view));
	gtk_text_buffer_set_text(buffer, elm->text, strlen(elm->text));
	return TRUE;
}

void close_result() //Close Window Selected
{ gtk_main_quit(); }

char *conca(const char *s1, const char *s2) //Concatenate char
{
     char *s3 = NULL;
     s3 = (char *)malloc((strlen(s1)+strlen(s2))+1);
     strcpy(s3,s1);
     strcat(s3,s2);
     return s3;
}

void move_file(char *filename)
{
	char *cp_arg1 = conca("cp ", filename);
	char *arg1_arg2 = conca(cp_arg1, " icon/temp.png");
	//printf("%s",arg1_arg2);
	system(arg1_arg2);
}

GdkPixbuf *pbuf;
GtkWindow *window_chooser;
void loading_image() //OPEN IMAGE (from Main_Window)
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    
    dialog = gtk_file_chooser_dialog_new ("Open File",window_chooser,action,
        ("_Cancel"),GTK_RESPONSE_CANCEL,("_Open the image"),GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(main_window));


    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);

		char *segmentation = "../process/./main_seg ";
		char *name_shell = conca(segmentation, filename);

		move_file(filename);
		system(name_shell);
    }
    gtk_widget_destroy (dialog);
}

void about_window_cb() //OPEN ABOUT_WINDOW (from a button)
{
  	GtkBuilder	*builder;
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "interface.glade", NULL);
    
    about_window = GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
    gtk_window_set_transient_for(GTK_WINDOW(about_window), GTK_WINDOW(main_window));
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(about_window);
    gtk_main();
}

void result_window_cb() //RESULT_WINDOW
{
	char *text = calloc(1024, sizeof(char));
    struct components *elm = calloc(1, sizeof(struct components));
    elm->text = text;
    //gtk_init(&argc, &argv);

    GtkBuilder *builder;
	builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "interface.glade", NULL);
    elm->window = GTK_WIDGET(gtk_builder_get_object(builder, "result_window"));
    elm->text_view = GTK_WIDGET(gtk_builder_get_object(builder, "text_view"));

    gtk_builder_connect_signals(builder, (gpointer) elm);

    g_object_unref(builder);

    gtk_widget_show_all(elm->window);
    gtk_main();

    free(text);
    free(elm);
}

int main(int argc, char *argv[]) //OPEN MAIN_WINDOW
{
    GtkBuilder	*builder;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "interface.glade", NULL);
 
    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    about_window = GTK_WIDGET(gtk_builder_get_object(builder, "about_window"));
    result_window = GTK_WIDGET(gtk_builder_get_object(builder, "result_window"));    

    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(main_window);                
    gtk_main();
 
    return 0;
}

// CLOSE SPECIFIC WINDOW
void close_about_window() // About
{ gtk_main_quit(); }
void close_result_window() //Result
{ gtk_main_quit(); }
void close_home_window() //Main
{ gtk_main_quit(); }
