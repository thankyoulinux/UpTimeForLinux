#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//gcc -o UptimeForLinux UptimeForLinux.c `pkg-config --libs --cflags gtk+-3.0`
static void showUptimeNow(GtkWidget *w, gpointer btn){
#ifdef __linux__
    gchar getFile[23] = "/tmp/UptimeForLinux.txt";
    gchar uptime[35] = "uptime -p > ";
    strcat(uptime, getFile);
    system(uptime);
    FILE* fileReader = fopen(getFile, "r");
    if(fileReader){
        gchar *text = NULL;
        gchar buffer[25];
        fgets(buffer, 25, fileReader);
        if(strlen(buffer) != 0){
            text = buffer;
            if(strlen(text) > 24){
                text = "More than 24 hours";
            }
        } else {
            text = "Something went wrong";
        }
        gtk_button_set_label(GTK_BUTTON(btn), text);
    } else {
        gtk_button_set_label(GTK_BUTTON(btn), "Something went wrong");
    }
    fclose(fileReader);
#endif
}
//Main
int main(int argc, char* argv[]){
#ifdef __linux__
    gtk_init(&argc,&argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "UptimeForLinux");
    gtk_window_set_default_size(GTK_WINDOW(window), 100, 30);
    gtk_window_set_resizable(GTK_WINDOW(window), 0);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *button = gtk_button_new_with_label("Click here");
    gtk_widget_set_tooltip_text(button, "Refresh \" uptime -p > /tmp/UptimeForLinux.txt \"");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(showUptimeNow), button);
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);
    gtk_main();
#else
    printf("It works on \"GNU/linux\" only\n");
#endif
    return 0;
}
