#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static GtkWidget *entry; // Entry field for input/output

// Function to handle button clicks
void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *button_label = (const char *)data;
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));

    if (strcmp(button_label, "C") == 0) {
        gtk_entry_set_text(GTK_ENTRY(entry), ""); // Clear entry
    } else if (strcmp(button_label, "=") == 0) {
        // Evaluate the expression
        char buffer[256];
        double result;

        // Use a simple `eval` logic for basic calculations
        // Note: This is NOT a full parser; improve this for complex cases
        if (sscanf(current_text, "%lf", &result) == 1) {
            snprintf(buffer, sizeof(buffer), "%.10g", result);
            gtk_entry_set_text(GTK_ENTRY(entry), buffer);
        } else {
            gtk_entry_set_text(GTK_ENTRY(entry), "Error");
        }
    } else if (strcmp(button_label, "del") == 0) {
        if (strlen(current_text) > 0) {
            char buffer[256];
            strncpy(buffer, current_text, strlen(current_text) - 1);
            buffer[strlen(current_text) - 1] = '\0';
            gtk_entry_set_text(GTK_ENTRY(entry), buffer);
        }
    } else {
        // Append button label to current text
        char new_text[256];
        snprintf(new_text, sizeof(new_text), "%s%s", current_text, button_label);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    }
}

// Create a button
GtkWidget *create_button(const char *label, GtkWidget *grid, int row, int col) {
    GtkWidget *button = gtk_button_new_with_label(label);
    gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)label);
    return button;
}

// Main function
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create entry field
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    // Create buttons
    const char *buttons[][4] = {
        {"C", "del", "/", "*"},
        {"7", "8", "9", "-"},
        {"4", "5", "6", "+"},
        {"1", "2", "3", "="},
        {"0", ".", "(", ")"}
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            create_button(buttons[i][j], grid, i + 1, j);
        }
    }

    // Show everything
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
