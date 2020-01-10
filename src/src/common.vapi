/* common.vapi generated by valac 0.35.3.8-bc5b, do not modify. */

namespace Boxes {
	namespace Fdo {
		[CCode (cheader_filename = "libcommon.h")]
		[DBus (name = "org.freedesktop.Accounts")]
		public interface Accounts : GLib.Object {
			public abstract async string FindUserByName (string name) throws GLib.IOError;
		}
		[CCode (cheader_filename = "libcommon.h")]
		[DBus (name = "org.freedesktop.Accounts.User")]
		public interface AccountsUser : GLib.Object {
			public abstract int32 AccountType { get; }
			public abstract bool AutomaticLogin { get; }
			public abstract string Email { owned get; }
			public abstract string HomeDirectory { owned get; }
			public abstract string IconFile { owned get; }
			public abstract string Language { owned get; }
			public abstract string Location { owned get; }
			public abstract bool Locked { get; }
			public abstract int32 PasswordMode { get; }
			public abstract string RealName { owned get; }
			public abstract string Shell { owned get; }
			public abstract bool SystemAccount { get; }
			public abstract string UserName { owned get; }
			public abstract string XSession { owned get; }
		}
	}
	[CCode (cheader_filename = "libcommon.h")]
	public class ActivityProgress : GLib.Object {
		public ActivityProgress ();
		public Boxes.ActivityProgress add_child_activity (double scale);
		public string info { get; set; }
		public double progress { get; set; }
	}
	[CCode (cheader_filename = "libcommon.h")]
	public class AsyncLauncher {
		public delegate void RunInThreadFunc () throws GLib.Error;
		public void await_all ();
		public static Boxes.AsyncLauncher get_default ();
		public async void launch (owned Boxes.AsyncLauncher.RunInThreadFunc func) throws GLib.Error;
	}
	[CCode (cheader_filename = "libcommon.h")]
	public class BoxConfig : GLib.Object, Boxes.IConfig {
		public struct SavedProperty {
			public string name;
			public GLib.Value default_value;
		}
		public BoxConfig ();
		public int compare (Boxes.BoxConfig other);
		public bool contains_strings (string[] strings);
		public void @delete ();
		public void save_properties (GLib.Object object, Boxes.BoxConfig.SavedProperty[] properties);
		public void set_category (string category, bool enabled);
		public BoxConfig.with_group (Boxes.CollectionSource source, string group);
		public int64 access_first_time { get; set; }
		public int64 access_last_time { get; set; }
		public int64 access_ntimes { get; set; }
		public int64 access_total_time { get; set; }
		public string[]? categories { owned get; set; }
		public string group { get; private set; }
		public string? last_seen_name { owned get; set; }
		public string? uuid { owned get; set; }
	}
	[CCode (cheader_filename = "libcommon.h")]
	public class CollectionSource : GLib.Object, Boxes.IConfig {
		public CollectionSource (string name, string source_type, string uri);
		public void @delete ();
		public void purge_stale_box_configs (GLib.List<Boxes.BoxConfig> used_configs);
		public CollectionSource.with_file (string filename) throws GLib.Error;
		public bool enabled { get; set; }
		public string? name { owned get; set; }
		public string? source_type { owned get; set; }
		public string? uri { owned get; set; }
	}
	[CCode (cheader_filename = "libcommon.h")]
	public class Pair<T1,T2> {
		public T1 first;
		public T2 second;
		public Pair (T1 first, T2 second);
	}
	[CCode (cheader_filename = "libcommon.h")]
	public class Query : GLib.Object {
		public Query (string query);
		public new string? @get (string key);
		public void parse ();
	}
	[CCode (cheader_filename = "libcommon.h")]
	public interface IConfig {
		public bool get_boolean (string group, string key, bool default_value = false);
		public string[] get_groups (string with_prefix = "");
		protected string? get_string (string group, string key);
		protected string[]? get_string_list (string group, string key);
		protected void load () throws GLib.Error;
		public void save ();
		public void set_boolean (string group, string key, bool value);
		public abstract string? filename { get; set; }
		protected abstract bool has_file { get; set; }
		protected abstract GLib.KeyFile keyfile { get; }
	}
	[CCode (cheader_filename = "libcommon.h")]
	public errordomain Error {
		INVALID,
		RESTORE_FAILED,
		START_FAILED,
		COMMAND_FAILED
	}
	[CCode (cheader_filename = "libcommon.h")]
	public delegate bool ForeachFilenameFromDirFunc (string filename) throws GLib.Error;
	[CCode (cheader_filename = "libcommon.h")]
	public delegate Archive.Result LibarchiveFunction ();
	[CCode (cheader_filename = "libcommon.h")]
	public static string canonicalize_for_search (string str);
	[CCode (cheader_filename = "libcommon.h")]
	public static void delete_file (GLib.File file) throws GLib.Error;
	[CCode (cheader_filename = "libcommon.h")]
	public static void ensure_directory (string dir);
	[CCode (cheader_filename = "libcommon.h")]
	public static async void exec (string[] argv, GLib.Cancellable? cancellable, out string? standard_output = null, out string? standard_error = null) throws GLib.Error;
	[CCode (cheader_filename = "libcommon.h")]
	public static void exec_sync (string[] argv, out string? standard_output = null, out string? standard_error = null) throws GLib.Error;
	[CCode (cheader_filename = "libcommon.h")]
	public static void execute_libarchive_function (Archive.Archive archive, Boxes.LibarchiveFunction function, uint num_retries = 1) throws GLib.IOError;
	[CCode (cheader_filename = "libcommon.h")]
	public static async void foreach_filename_from_dir (GLib.File dir, Boxes.ForeachFilenameFromDirFunc func);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_cache (string cache_name, string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_drivers_cache (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static int get_enum_value (string value_nick, GLib.Type enum_type);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_logo_cache (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_logos_db ();
	[CCode (cheader_filename = "libcommon.h")]
	public static bool get_next_header (Archive.Read archive, out unowned Archive.Entry iterator, uint num_retries = 1) throws GLib.IOError;
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_pixmap (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_pkgdata (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_pkgdata_source (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_screenshot_filename (string prefix);
	[CCode (cheader_filename = "libcommon.h")]
	public static string? get_system_drivers_cache (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string? get_system_logo_cache (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string? get_system_pkgcache (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_unattended (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_user_pkgcache (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_user_pkgconfig (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_user_pkgconfig_source (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_user_pkgdata (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_user_unattended (string? file_name = null);
	[CCode (cheader_filename = "libcommon.h")]
	public static string get_utf8_basename (string path);
	[CCode (cheader_filename = "libcommon.h")]
	public static bool has_user_pkgconfig_sources ();
	[CCode (cheader_filename = "libcommon.h")]
	public static string indent (string space, string text);
	[CCode (cheader_filename = "libcommon.h")]
	public static bool is_set (string? str);
	[CCode (cheader_filename = "libcommon.h")]
	public static bool keyfile_save (GLib.KeyFile key_file, string file_name, bool overwrite = false);
	[CCode (cheader_filename = "libcommon.h")]
	public static string make_filename (string name);
	[CCode (cheader_filename = "libcommon.h")]
	public static async void output_stream_write (GLib.OutputStream stream, uint8[] buffer) throws GLib.IOError;
	[CCode (cheader_filename = "libcommon.h")]
	public static string replace_regex (string str, string old, string replacement);
	[CCode (cheader_filename = "libcommon.h")]
	public static string yes_no (bool value);
}
