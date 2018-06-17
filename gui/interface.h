#ifndef _MY_EXAMPLE_TEXT_VIEW_
#define _MY_EXAMPLE_TEXT_VIEW_

#include <gtk/gtk.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <err.h>

#define UNUSED(x) (void)(x)

struct components
{
  GtkWidget *window;
  GtkWidget *text_view;
  GtkWidget *result_img;
  char *filename;
  char *text;
  gboolean saved;
};

void close_result();

gboolean start_ocrx(GtkWidget *widget, GdkEvent *event, gpointer data);

void loading_image();

void about_window_cb();

void result_window_cb();

void close_about_window();

void close_result_window();

void close_home_window();

#endif
