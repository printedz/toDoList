#include <gtk/gtk.h>

// Function to handle adding tasks
static void add_task(GtkButton *button, gpointer user_data);

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *add_button;
    GtkWidget *vbox;
    GtkWidget *button_box;

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "To-Do Task Planner");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);

    // Create a vertical box container to hold the input and task list
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Create a grid to organize checkboxes and input fields
    grid = gtk_grid_new();
    gtk_box_append(GTK_BOX(vbox), grid);

    // Add a text entry field for new tasks
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter a new task");
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);
    gtk_widget_set_margin_end(entry, 15);
    gtk_widget_set_margin_start(entry, 15);
    gtk_widget_set_margin_top(entry, 15);

    // Add a button to add new tasks
    add_button = gtk_button_new_with_label("Add Task");
    gtk_grid_attach(GTK_GRID(grid), add_button, 1, 0, 1, 1);
    gtk_widget_set_margin_top(add_button, 15);

    // Create a button box to hold checkboxes
    button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), button_box);

    // Connect the button to an event handler
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_task), entry);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

// Function to handle adding tasks
static void add_task(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *task_text = gtk_editable_get_text(GTK_EDITABLE(entry));

    if (g_strcmp0(task_text, "") != 0) {
        GtkWidget *task_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget *check_button = gtk_check_button_new_with_label(task_text);

        gtk_box_append(GTK_BOX(task_box), check_button);

        // Find the vbox container to add the new task
        GtkWidget *window = gtk_widget_get_ancestor(GTK_WIDGET(entry), GTK_TYPE_WINDOW);
        GtkWidget *vbox = gtk_widget_get_first_child(GTK_WIDGET(window));
        GtkWidget *button_box = gtk_widget_get_last_child(GTK_WIDGET(vbox));
        gtk_box_append(GTK_BOX(button_box), task_box);

        gtk_widget_set_visible(task_box, TRUE);
        gtk_widget_set_visible(check_button, TRUE);

        // Clear the entry field
        gtk_editable_set_text(GTK_EDITABLE(entry), "");
    }
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.GtkTodoApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
