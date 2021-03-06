#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define FPS 15

//uncomment to print time to draw
//#define PRINT_TIMING

struct{
    int animate;
    int running;
    int frames_remaining;
}settings={0, 0, 60*FPS};

//size of drawing area so the solid knows how far to translate
struct{
    double w,h;
}size;

#include "player.h"
#include "game.h"

void start_game(){
    settings.running = 1;
    init_dots();
    for(int i = 0; i < 10; ++i){
	add_dot((double)rand()/RAND_MAX*800-400, (double)rand()/RAND_MAX*600-300);
	dots->remaining_frames = (int)((double)rand()/RAND_MAX*(dots->remaining_frames));
    }
}
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

    if (settings.running){
	cairo_translate(cr,w/2,h/2);
	cairo_scale(cr,1,-1);
	
	dot* current = dots;
	while (current->next){
	    double b = (double)current->remaining_frames/FPS/30;
	    b=b/4*3+0.25;
	    if (current->points == -50)
		cairo_set_source_rgba(cr, 1,0,0,b);
	    else if (current->points == 1)
		cairo_set_source_rgba(cr, 0,1,0,b);
	    else if (current->points == 5)
		cairo_set_source_rgba(cr, 0,1,1,b);
	    else if (current->points == 25)
		cairo_set_source_rgba(cr, 1,0,1,b);
	    else
		cairo_set_source_rgba(cr, 1,1,1,b);
	    cairo_arc(cr,current->x, current->y, DOT_RADIUS, 0,2*M_PI);
	    cairo_fill(cr);
	    current = current->next;
	}
	
	cairo_set_source_rgb(cr,1,1,1);
	
	cairo_set_dash(cr,(double[]){14.0,6.0},2,1);
	cairo_arc(cr,0,0,player.circle_r, 0,2*M_PI);
	cairo_stroke(cr);
	
	cairo_arc(cr,player_get_x(),player_get_y(),player.dot_r,0,2*M_PI);
	cairo_fill(cr);
	
	char buf[50];
	sprintf(buf,"Score: %d", points);
	cairo_set_font_size(cr, 30);
	cairo_scale(cr,1,-1);
	cairo_translate(cr, -w/2, -h/2);
	cairo_move_to(cr, 10, 30);
	cairo_show_text(cr, buf);

	int sec = settings.frames_remaining/FPS;
	int min = sec/60;
	sec -= min*60;
	sprintf(buf,"%d:%02d",min,sec);
	cairo_text_extents_t extents;
	cairo_text_extents(cr,buf,&extents);
	cairo_move_to(cr,w-extents.width-10,30);
	cairo_show_text(cr,buf);
    }
    else{
	if (settings.frames_remaining == 0){
	    settings.animate = 0;
	    cairo_set_source_rgb(cr,1,1,1);
	    char buf[50];
	    sprintf(buf,"Game Over");
	    cairo_set_font_size(cr, 40);
	    cairo_text_extents_t extents;
	    cairo_text_extents(cr,buf,&extents);
	    cairo_move_to(cr,w/2-extents.width/2, h*3/8);
	    cairo_show_text(cr, buf);
	    
	    sprintf(buf,"Score: %d", points);
	    cairo_text_extents(cr,buf,&extents);
	    cairo_move_to(cr,w/2-extents.width/2, h*3/8+extents.height*1.2);
	    cairo_show_text(cr,buf);
	}
	else{
	    cairo_set_font_size(cr, 40);
	    cairo_text_extents_t extents;
	    cairo_text_extents(cr,"Start",&extents);
	    cairo_set_source_rgb(cr, 0, 1, 1);
	    cairo_rectangle(cr, w/2-extents.width/2-5, h/2-extents.height/2-10, extents.width+10,extents.height+10);
	    cairo_fill(cr);
	    cairo_set_source_rgb(cr,0,0,0);
	    cairo_move_to(cr,w/2-extents.width/2,h/2+extents.height/4);
	    cairo_show_text(cr,"Start");
	}
    }
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
    g_signal_connect(G_OBJECT(window),"button_press_event", G_CALLBACK(on_click), NULL);
    
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),800,600);
    gtk_window_set_title(GTK_WINDOW(window), "Polar Dots");

    srand(time(NULL));
       
    toggle_animate(window,NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
