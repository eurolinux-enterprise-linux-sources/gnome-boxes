// This file is part of GNOME Boxes. License: LGPLv2+
using Gtk;
using Gdk;

[GtkTemplate (ui = "/org/gnome/Boxes/ui/app-window.ui")]
private class Boxes.AppWindow: Gtk.ApplicationWindow, Boxes.UI {
    public const uint TRANSITION_DURATION = 400; // milliseconds

    public UIState previous_ui_state { get; protected set; }
    public UIState ui_state { get; protected set; }

    // current object/vm manipulated
    private CollectionItem _current_item;
    public CollectionItem current_item {
        get {
            return _current_item;
        }

        set {
            if (_current_item != null) {
                _current_item.disconnect (machine_state_notify_id);
                machine_state_notify_id = 0;
                machine_deleted_notify_id = 0;
            }

            _current_item = value;
            if (_current_item != null) {
                var machine = (_current_item as Machine);

                machine_state_notify_id = machine.notify["state"].connect (on_machine_state_notify);
                machine_deleted_notify_id = machine.notify["deleted"].connect (on_machine_deleted_notify);
            }
        }
    }
    public signal void item_selected (CollectionItem item);

    private GLib.Binding status_bind;
    private ulong got_error_id;
    private ulong machine_state_notify_id;
    private ulong machine_deleted_notify_id;

    [CCode (notify = false)]
    public bool fullscreened {
        get { return WindowState.FULLSCREEN in get_window ().get_state (); }
        set {
            if (value)
                fullscreen ();
            else
                unfullscreen ();
        }
    }
    private bool maximized { get { return WindowState.MAXIMIZED in get_window ().get_state (); } }

    private bool _selection_mode;
    public bool selection_mode { get { return _selection_mode; }
        set {
            return_if_fail (ui_state == UIState.COLLECTION);

            _selection_mode = value;
        }
    }

    private void on_machine_state_notify () {
       if (this != App.app.main_window && (current_item as Machine).state != Machine.MachineState.RUNNING)
           on_delete_event ();
    }

    private void on_machine_deleted_notify () {
       if (this != App.app.main_window && (current_item as Machine).deleted)
           on_delete_event ();
    }

    [GtkChild]
    public Searchbar searchbar;
    [GtkChild]
    public Topbar topbar;
    [GtkChild]
    public Notificationbar notificationbar;
    [GtkChild]
    public Selectionbar selectionbar;
    [GtkChild]
    public Sidebar sidebar;
    [GtkChild]
    public Wizard wizard;
    [GtkChild]
    public Properties properties;
    [GtkChild]
    public DisplayPage display_page;
    [GtkChild]
    public EmptyBoxes empty_boxes;
    [GtkChild]
    public Gtk.Stack below_bin;
    [GtkChild]
    private Gtk.Stack content_bin;
    [GtkChild]
    private Gtk.Box below_bin_hbox;
    [GtkChild]
    public CollectionView view;

    public GLib.Settings settings;

    private uint configure_id;
    public static const uint configure_id_timeout = 100;  // 100ms

    public AppWindow (Gtk.Application app) {
        Object (application: app, title: _("Boxes"));

        settings = new GLib.Settings ("org.gnome.boxes");

        notify["ui-state"].connect (ui_state_changed);

        Gtk.Window.set_default_icon_name ("gnome-boxes");
        Gtk.Settings.get_default ().gtk_application_prefer_dark_theme = true;

        var provider = Boxes.load_css ("gtk-style.css");
        Gtk.StyleContext.add_provider_for_screen (Gdk.Screen.get_default (),
                                                  provider,
                                                  600);

        // restore window geometry/position
        var size = settings.get_value ("window-size");
        if (size.n_children () == 2) {
            var width = (int) size.get_child_value (0);
            var height = (int) size.get_child_value (1);

            set_default_size (width, height);
        }

        if (settings.get_boolean ("window-maximized"))
            maximize ();

        var position = settings.get_value ("window-position");
        if (position.n_children () == 2) {
            var x = (int) position.get_child_value (0);
            var y = (int) position.get_child_value (1);

            move (x, y);
        }
    }

    public void setup_ui () {
        topbar.setup_ui (this);
        wizard.setup_ui (this);
        display_page.setup_ui (this);
        view.setup_ui (this);
        selectionbar.setup_ui (this);
        searchbar.setup_ui (this);
        sidebar.setup_ui (this);
        properties.setup_ui (this);
        empty_boxes.setup_ui (this);
        notificationbar.searchbar = searchbar;
    }

    private void save_window_geometry () {
        int width, height, x, y;

        if (maximized)
            return;

        get_size (out width, out height);
        settings.set_value ("window-size", new int[] { width, height });

        get_position (out x, out y);
        settings.set_value ("window-position", new int[] { x, y });
    }

    private void ui_state_changed () {
        // The order is important for some widgets here (e.g properties must change its state before wizard so it can
        // flush any deferred changes for wizard to pick-up when going back from properties to wizard (review).
        foreach (var ui in new Boxes.UI[] { sidebar, topbar, view, properties, wizard, empty_boxes }) {
            ui.set_state (ui_state);
        }

        if (ui_state != UIState.COLLECTION)
            searchbar.search_mode_enabled = false;

        switch (ui_state) {
        case UIState.COLLECTION:
            if (App.app.collection.items.length != 0)
                below_bin.visible_child = view;
            else
                below_bin.visible_child = empty_boxes;
            fullscreened = false;
            view.visible = true;

            status_bind = null;
            topbar.status = null;
            if (current_item is Machine) {
                var machine = current_item as Machine;
                if (got_error_id != 0) {
                    machine.disconnect (got_error_id);
                    got_error_id = 0;
                }

                machine.connecting_cancellable.cancel (); // Cancel any in-progress connections
            }

            break;

        case UIState.CREDS:
        case UIState.DISPLAY:

            break;

        case UIState.WIZARD:
            below_bin.visible_child = below_bin_hbox;
            content_bin.visible_child = wizard;

            break;

        case UIState.PROPERTIES:
            below_bin.visible_child = below_bin_hbox;
            content_bin.visible_child = properties;

            break;

        default:
            warning ("Unhandled UI state %s".printf (ui_state.to_string ()));
            break;
        }

        if (current_item != null)
            current_item.set_state (ui_state);
    }

    public void show_properties () {
        var selected_items = view.get_selected_items ();

        selection_mode = false;

        // Show for the first selected item
        foreach (var item in selected_items) {
            current_item = item;
            set_state (UIState.PROPERTIES);
            break;
        }
    }

    public void connect_to (Machine machine) {
        current_item = machine;
        machine.window = this;

        // Track machine status in toobar
        status_bind = machine.bind_property ("status", topbar, "status", BindingFlags.SYNC_CREATE);

        got_error_id = machine.got_error.connect ( (message) => {
            notificationbar.display_error (message);
        });

        if (ui_state != UIState.CREDS)
            set_state (UIState.CREDS); // Start the CREDS state
    }

    public void select_item (CollectionItem item) {
        if (ui_state == UIState.COLLECTION && !selection_mode) {
            return_if_fail (item is Machine);

            var machine = item as Machine;

            if (machine.window != App.app.main_window) {
                machine.window.present ();

                return;
            }

            current_item = item;

            if (current_item is Machine)
                connect_to (machine);
            else
                warning ("unknown item, fix your code");

            item_selected (item);
        } else if (ui_state == UIState.WIZARD) {
            current_item = item;

            set_state (UIState.PROPERTIES);
        }
    }

    [GtkCallback]
    public bool on_key_pressed (Widget widget, Gdk.EventKey event) {
        var default_modifiers = Gtk.accelerator_get_default_mod_mask ();

        if (event.keyval == Gdk.Key.F11) {
            fullscreened = !fullscreened;

            return true;
        } else if (event.keyval == Gdk.Key.F1) {
            App.app.activate_action ("help", null);

            return true;
        } else if (event.keyval == Gdk.Key.q &&
                   (event.state & default_modifiers) == Gdk.ModifierType.CONTROL_MASK) {
            App.app.quit_app ();

            return true;
        } else if (event.keyval == Gdk.Key.n &&
                   (event.state & default_modifiers) == Gdk.ModifierType.CONTROL_MASK) {
            topbar.click_new_button ();

            return true;
        } else if (event.keyval == Gdk.Key.f &&
                   (event.state & default_modifiers) == Gdk.ModifierType.CONTROL_MASK) {
            topbar.click_search_button ();

            return true;
        } else if (event.keyval == Gdk.Key.a &&
                   (event.state & default_modifiers) == Gdk.ModifierType.MOD1_MASK) {
            App.app.quit_app ();

            return true;
        } else if (event.keyval == Gdk.Key.Left && // ALT + Left -> back
                   (event.state & default_modifiers) == Gdk.ModifierType.MOD1_MASK) {
            topbar.click_back_button ();
            return true;
        } else if (event.keyval == Gdk.Key.Right && // ALT + Right -> forward
                   (event.state & default_modifiers) == Gdk.ModifierType.MOD1_MASK) {
            topbar.click_forward_button ();
            return true;
        } else if (event.keyval == Gdk.Key.Escape) { // ESC -> cancel
            topbar.click_cancel_button ();
        }

        return false;
    }

    [GtkCallback]
    private bool on_configure_event () {
        if (fullscreened)
            return false;

        if (configure_id != 0)
            GLib.Source.remove (configure_id);
        configure_id = Timeout.add (configure_id_timeout, () => {
            configure_id = 0;
            save_window_geometry ();

            return false;
        });

        return false;
     }

    [GtkCallback]
    private bool on_window_state_event (Gdk.EventWindowState event) {
        if (WindowState.FULLSCREEN in event.changed_mask)
            this.notify_property ("fullscreened");

        if (fullscreened)
            return false;

        settings.set_boolean ("window-maximized", maximized);

        return false;
    }

    [GtkCallback]
    private bool on_delete_event () {
        return_if_fail (current_item == null || current_item is Machine);

        if (current_item != null)
            (current_item as Machine).window = null;

        return App.app.remove_window (this);
    }
}
