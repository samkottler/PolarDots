//timeout function for animating
gboolean animate(gpointer data){
    if (settings.animate){
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
