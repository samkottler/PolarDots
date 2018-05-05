#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FPS 15

//uncomment to print time to draw
//#define PRINT_TIMING

struct{
    int animate;
}settings={0};

//size of drawing area so the solid knows how far to translate
struct{
    double w,h;
}size;

#include "player.h"
#include "eventHandlers.h"

//function to handle redrawing
void on_draw(GtkWidget* widget, cairo_t* cr, gpointer data){
    //get size of surface
    int w,h;
    GtkAllocation alloc;
    gtk_widget_get_allocation(widget,&alloc);
    w=alloc.width;
    h=alloc.height;
    size.w = w;
    size.h = h;

    //set background to black
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, w,h);
    cairo_fill(cr);

    cairo_translate(cr,w/2,h/2);
    cairo_scale(cr,1,-1);
    
    cairo_set_source_rgb(cr,1,1,1);
    cairo_arc(cr,player_get_x(),player_get_y(),player.dot_r,0,2*M_PI);
    cairo_fill(cr);
}

void clean_and_quit(GtkWidget* widget, gpointer data){
    settings.animate=0;
    gtk_main_quit();
}

//initializes the large gtk elements and displays the window
int main(int argc, char** argv){    
    gtk_init(&argc,&argv);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* stage = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    GtkWidget* darea = gtk_drawing_area_new();
    
    gtk_box_set_homogeneous(GTK_BOX(stage),TRUE);
    
    gtk_box_pack_start(GTK_BOX(stage),darea,TRUE,TRUE,0);
    
    gtk_container_add(GTK_CONTAINER(window),stage);
    g_signal_connect(G_OBJECT(darea),"draw",G_CALLBACK(on_draw),NULL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(clean_and_quit),NULL);
    g_signal_connect(G_OBJECT(window),"key_press_event",G_CALLBACK(on_key_press),NULL);
    g_signal_connect(G_OBJECT(window),"key_release_event",G_CALLBACK(on_key_release),NULL);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),800,600);
    gtk_window_set_title(GTK_WINDOW(window), "Cricle Game");

    toggle_animate(window,NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
