// This file is part of GNOME Boxes. License: LGPLv2+
using Gtk;

[GtkTemplate (ui = "/org/gnome/Boxes/ui/properties-toolbar.ui")]
private class Boxes.PropertiesToolbar: Gtk.Stack {
    private PropsWindowPage _page;
    public PropsWindowPage page {
        get { return _page; }
        set {
            _page = value;

            visible_child_name = PropertiesWindow.page_names[value];
        }
    }

    [GtkChild]
    public Gtk.HeaderBar main;

    [GtkChild]
    public Gtk.Button troubleshooting_back_button;

    [GtkChild]
    private EditableEntry title_entry;
    [GtkChild]
    private Button file_chooser_open_button;

    private AppWindow window;
    private unowned PropertiesWindow props_window;

    private CollectionItem item;
    private ulong item_name_id;

    construct {
        // Work around for https://bugzilla.gnome.org/show_bug.cgi?id=734676
        main.set_custom_title (title_entry);
    }

    public void setup_ui (AppWindow window, PropertiesWindow props_window) {
        this.window = window;
        this.props_window = props_window;

        var file_chooser = props_window.file_chooser;
        file_chooser.selection_changed.connect (() => {
            var path = file_chooser.get_filename ();

            file_chooser_open_button.sensitive = (path != null);
        });

        window.notify["ui-state"].connect (ui_state_changed);
    }

    public void click_back_button () {
        if (page != PropsWindowPage.TROUBLESHOOTING_LOG)
            return;

        troubleshooting_back_button.clicked ();
    }

    [GtkCallback]
    private void on_troubleshooting_back_clicked () requires (page == PropsWindowPage.TROUBLESHOOTING_LOG) {
        props_window.page = PropsWindowPage.MAIN;
    }

    [GtkCallback]
    private void on_copy_clipboard_clicked () requires (page == PropsWindowPage.TROUBLESHOOTING_LOG) {
        props_window.copy_troubleshoot_log_to_clipboard ();
    }

    [GtkCallback]
    private void on_file_chooser_cancel_clicked () requires (page == PropsWindowPage.FILE_CHOOSER) {
        props_window.page = PropsWindowPage.MAIN;
    }

    [GtkCallback]
    private void on_file_chooser_open_clicked () requires (page == PropsWindowPage.FILE_CHOOSER) {
        var file_chooser = props_window.file_chooser;
        var file = file_chooser.get_file ();
        assert (file != null);
        var file_type = file.query_file_type (FileQueryInfoFlags.NONE, null);

        switch (file_type) {
        case GLib.FileType.REGULAR:
        case GLib.FileType.SYMBOLIC_LINK:
            file_chooser.file_activated ();
            break;

        case GLib.FileType.DIRECTORY:
            file_chooser.set_current_folder (file.get_path ());
            break;

        default:
            debug ("Unknown file type selected");
            break;
        }
    }

    [GtkCallback]
    private void on_title_entry_changed () {
        window.current_item.name = title_entry.text;
    }

    private void ui_state_changed () {
        if (item_name_id != 0) {
            item.disconnect (item_name_id);
            item_name_id = 0;
        }

        if (window.ui_state == UIState.PROPERTIES) {
            item = window.current_item;

            item_name_id = item.notify["name"].connect (() => {
                title_entry.text = item.name;
            });
            title_entry.text = item.name;
        }
    }
}
