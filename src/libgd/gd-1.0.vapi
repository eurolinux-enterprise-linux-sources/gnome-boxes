/* gd-1.0.vapi generated by vapigen, do not modify. */

[CCode (cprefix = "Gd", gir_namespace = "Gd", gir_version = "1.0", lower_case_cprefix = "gd_")]
namespace Gd {
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_main_icon_view_get_type ()")]
	public class MainIconView : Gtk.IconView, Atk.Implementor, Gd.MainViewGeneric, Gtk.Buildable, Gtk.CellLayout, Gtk.Scrollable {
		[CCode (has_construct_function = false, type = "GtkWidget*")]
		public MainIconView ();
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_main_list_view_get_type ()")]
	public class MainListView : Gtk.TreeView, Atk.Implementor, Gd.MainViewGeneric, Gtk.Buildable, Gtk.Scrollable {
		[CCode (has_construct_function = false, type = "GtkWidget*")]
		public MainListView ();
		public void add_renderer (Gtk.CellRenderer renderer, owned Gtk.TreeCellDataFunc func);
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_main_view_get_type ()")]
	public class MainView : Gtk.ScrolledWindow, Atk.Implementor, Gtk.Buildable {
		[CCode (has_construct_function = false)]
		public MainView (Gd.MainViewType type);
		public unowned Gtk.Widget get_generic_view ();
		public unowned Gtk.TreeModel get_model ();
		public GLib.List<Gtk.TreePath> get_selection ();
		public bool get_selection_mode ();
		public Gd.MainViewType get_view_type ();
		public void select_all ();
		public void set_model (Gtk.TreeModel? model);
		public void set_selection_mode (bool selection_mode);
		public void set_view_type (Gd.MainViewType type);
		public void unselect_all ();
		public Gtk.TreeModel model { get; set construct; }
		public bool selection_mode { get; set construct; }
		public int view_type { get; set construct; }
		public signal void item_activated (string object, Gtk.TreePath p0);
		public signal void selection_mode_request ();
		public signal void view_selection_changed ();
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_notification_get_type ()")]
	public class Notification : Gtk.Bin, Atk.Implementor, Gtk.Buildable {
		[CCode (has_construct_function = false, type = "GtkWidget*")]
		public Notification ();
		public void dismiss ();
		public void set_show_close_button (bool show_close_button);
		public void set_timeout (int timeout_sec);
		[NoAccessorMethod]
		public bool show_close_button { get; set construct; }
		[NoAccessorMethod]
		[Version (since = "0.1")]
		public int timeout { get; set construct; }
		public virtual signal void dismissed ();
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_styled_text_renderer_get_type ()")]
	public class StyledTextRenderer : Gtk.CellRendererText {
		[CCode (has_construct_function = false, type = "GtkCellRenderer*")]
		public StyledTextRenderer ();
		public void add_class (string @class);
		public void remove_class (string @class);
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_toggle_pixbuf_renderer_get_type ()")]
	public class TogglePixbufRenderer : Gtk.CellRendererPixbuf {
		[CCode (has_construct_function = false, type = "GtkCellRenderer*")]
		public TogglePixbufRenderer ();
		[NoAccessorMethod]
		public bool active { get; set; }
		[NoAccessorMethod]
		public uint pulse { get; set; }
		[NoAccessorMethod]
		public bool toggle_visible { get; set; }
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_two_lines_renderer_get_type ()")]
	public class TwoLinesRenderer : Gtk.CellRendererText {
		[CCode (has_construct_function = false, type = "GtkCellRenderer*")]
		public TwoLinesRenderer ();
		[NoAccessorMethod]
		public string line_two { owned get; set; }
		[NoAccessorMethod]
		public int text_lines { get; set; }
	}
	[CCode (cheader_filename = "libgd/gd.h", type_id = "gd_main_view_generic_get_type ()")]
	public interface MainViewGeneric : Gtk.Widget {
		public abstract unowned Gtk.TreeModel get_model ();
		public abstract Gtk.TreePath get_path_at_pos (int x, int y);
		public abstract void scroll_to_path (Gtk.TreePath path);
		public void select_all ();
		public abstract void set_model (Gtk.TreeModel? model);
		public void set_rubberband_range (Gtk.TreePath start, Gtk.TreePath end);
		public abstract void set_selection_mode (bool selection_mode);
		public void unselect_all ();
		public signal void view_selection_changed ();
	}
	[CCode (cheader_filename = "libgd/gd.h", cprefix = "GD_MAIN_COLUMN_", has_type_id = false)]
	public enum MainColumns {
		ID,
		URI,
		PRIMARY_TEXT,
		SECONDARY_TEXT,
		ICON,
		MTIME,
		SELECTED,
		PULSE,
		LAST
	}
	[CCode (cheader_filename = "libgd/gd.h", cprefix = "GD_MAIN_VIEW_", has_type_id = false)]
	public enum MainViewType {
		ICON,
		LIST
	}
	[CCode (cheader_filename = "libgd/gd.h")]
	public static GLib.Icon create_symbolic_icon (string name, int base_size);
	[CCode (cheader_filename = "libgd/gd.h")]
	public static GLib.Icon create_symbolic_icon_for_scale (string name, int base_size, int scale);
	[CCode (cheader_filename = "libgd/gd.h")]
	public static Gdk.Pixbuf embed_image_in_frame (Gdk.Pixbuf source_image, string frame_image_url, Gtk.Border slice_width, Gtk.Border border_width);
	[CCode (cheader_filename = "libgd/gd.h")]
	public static Cairo.Surface embed_surface_in_frame (Cairo.Surface source_image, string frame_image_url, Gtk.Border slice_width, Gtk.Border border_width);
	[CCode (cheader_filename = "libgd/gd.h")]
	public static void ensure_types ();
	[CCode (cheader_filename = "libgd/gd.h")]
	public static void entry_focus_hack (Gtk.Widget entry, Gdk.Device device);
}
