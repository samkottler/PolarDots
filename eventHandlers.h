int key_up = 0;
int key_down = 0;
int key_right = 0;
int key_left = 0;

gboolean on_click(GtkWidget *widget, GdkEventButton *event, gpointer data){
    double x = event->x;
    double y = event->y;
    if(!settings.running && settings.frames_remaining && x<450 && x>350 && y<315 && y>275)
	start_game();
    return FALSE;
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data){
    switch (event->keyval){
    case GDK_KEY_Up:
	if (!key_down)
	    key_up = 1;
	break;
    case GDK_KEY_Down:
	if (!key_up)
	    key_down = 1;
	break;
    case GDK_KEY_Left:
	if (!key_right)
	    key_left = 1;
	break;
    case GDK_KEY_Right:
	if (!key_left)
	    key_right = 1;
	break;
    default:
	return FALSE;
    }
    return FALSE;
}

gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer data){
    switch (event->keyval){
    case GDK_KEY_Up:
	key_up = 0;
	break;
    case GDK_KEY_Down:
	key_down = 0;
	break;
    case GDK_KEY_Left:
	key_left = 0;
	break;
    case GDK_KEY_Right:
	key_right = 0;
	break;
    default:
	return FALSE;
    }
    return FALSE;
}

//timeout function for animating
gboolean animate(gpointer data){
    if (settings.animate){
	if(settings.running){
	    double dir = 1;
	    if ((key_right || key_left) && (key_up || key_down))
		dir = 1.0/sqrt(2);
	    if (key_right)
		player_rotate(dir);
	    if (key_left)
		player_rotate(-dir);
	    if (key_up)
		player_move_radial(dir);
	    if (key_down)
		player_move_radial(-dir);
	    if(rand() < RAND_MAX/FPS){
		add_dot((double)rand()/RAND_MAX*size.w-size.w/2,(double)rand()/RAND_MAX*size.h-size.h/2);
	    }
	    update_dots();
	    if (settings.frames_remaining)
		--(settings.frames_remaining);
	    else
		settings.running = 0;
	}
	gtk_widget_queue_draw(gtk_widget_get_toplevel(GTK_WIDGET(data)));
	return TRUE;
    }
    else
	return FALSE;
}

//toggles the animate setting and starts the timeout function
void toggle_animate(GtkWidget* widget, gpointer data){
    settings.animate = !settings.animate;
    if(settings.animate){
	g_timeout_add((int)(1000.0/FPS), (GSourceFunc) animate, widget);
    }
    gtk_widget_queue_draw(gtk_widget_get_toplevel(widget));
}
