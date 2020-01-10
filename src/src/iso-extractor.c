/* iso-extractor.c generated by valac 0.26.1, the Vala compiler
 * generated from iso-extractor.vala, do not modify */

/* This file is part of GNOME Boxes. License: LGPLv2+*/
/* Helper class to extract files from an ISO image*/

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>
#include <archive.h>


#define BOXES_TYPE_ISO_EXTRACTOR (boxes_iso_extractor_get_type ())
#define BOXES_ISO_EXTRACTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), BOXES_TYPE_ISO_EXTRACTOR, BoxesISOExtractor))
#define BOXES_ISO_EXTRACTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), BOXES_TYPE_ISO_EXTRACTOR, BoxesISOExtractorClass))
#define BOXES_IS_ISO_EXTRACTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BOXES_TYPE_ISO_EXTRACTOR))
#define BOXES_IS_ISO_EXTRACTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BOXES_TYPE_ISO_EXTRACTOR))
#define BOXES_ISO_EXTRACTOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), BOXES_TYPE_ISO_EXTRACTOR, BoxesISOExtractorClass))

typedef struct _BoxesISOExtractor BoxesISOExtractor;
typedef struct _BoxesISOExtractorClass BoxesISOExtractorClass;
typedef struct _BoxesISOExtractorPrivate BoxesISOExtractorPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define BOXES_TYPE_ARCHIVE_READER (boxes_archive_reader_get_type ())
#define BOXES_ARCHIVE_READER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), BOXES_TYPE_ARCHIVE_READER, BoxesArchiveReader))
#define BOXES_ARCHIVE_READER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), BOXES_TYPE_ARCHIVE_READER, BoxesArchiveReaderClass))
#define BOXES_IS_ARCHIVE_READER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BOXES_TYPE_ARCHIVE_READER))
#define BOXES_IS_ARCHIVE_READER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BOXES_TYPE_ARCHIVE_READER))
#define BOXES_ARCHIVE_READER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), BOXES_TYPE_ARCHIVE_READER, BoxesArchiveReaderClass))

typedef struct _BoxesArchiveReader BoxesArchiveReader;
typedef struct _BoxesArchiveReaderClass BoxesArchiveReaderClass;
typedef struct _BoxesIsoExtractorExtractData BoxesIsoExtractorExtractData;

struct _BoxesISOExtractor {
	GObject parent_instance;
	BoxesISOExtractorPrivate * priv;
};

struct _BoxesISOExtractorClass {
	GObjectClass parent_class;
};

struct _BoxesISOExtractorPrivate {
	gchar* device_file;
};

struct _BoxesIsoExtractorExtractData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	BoxesISOExtractor* self;
	gchar* path;
	gchar* output_path;
	GCancellable* cancellable;
	const gchar* _tmp0_;
	const gchar* _tmp1_;
	const gchar* _tmp2_;
	BoxesArchiveReader* reader;
	const gchar* _tmp3_;
	BoxesArchiveReader* _tmp4_;
	BoxesArchiveReader* _tmp5_;
	const gchar* _tmp6_;
	const gchar* _tmp7_;
	const gchar* _tmp8_;
	const gchar* _tmp9_;
	const gchar* _tmp10_;
	GError * _inner_error_;
};


static gpointer boxes_iso_extractor_parent_class = NULL;

GType boxes_iso_extractor_get_type (void) G_GNUC_CONST;
#define BOXES_ISO_EXTRACTOR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), BOXES_TYPE_ISO_EXTRACTOR, BoxesISOExtractorPrivate))
enum  {
	BOXES_ISO_EXTRACTOR_DUMMY_PROPERTY
};
BoxesISOExtractor* boxes_iso_extractor_new (const gchar* iso_path);
BoxesISOExtractor* boxes_iso_extractor_construct (GType object_type, const gchar* iso_path);
static void boxes_iso_extractor_extract_data_free (gpointer _data);
void boxes_iso_extractor_extract (BoxesISOExtractor* self, const gchar* path, const gchar* output_path, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
void boxes_iso_extractor_extract_finish (BoxesISOExtractor* self, GAsyncResult* _res_, GError** error);
static gboolean boxes_iso_extractor_extract_co (BoxesIsoExtractorExtractData* _data_);
GType boxes_archive_reader_get_type (void) G_GNUC_CONST;
BoxesArchiveReader* boxes_archive_reader_new (const gchar* filename, int* format, GList* filters, GError** error);
BoxesArchiveReader* boxes_archive_reader_construct (GType object_type, const gchar* filename, int* format, GList* filters, GError** error);
void boxes_archive_reader_extract_file (BoxesArchiveReader* self, const gchar* src, const gchar* dest, gboolean override_if_necessary, GError** error);
static void boxes_iso_extractor_finalize (GObject* obj);


BoxesISOExtractor* boxes_iso_extractor_construct (GType object_type, const gchar* iso_path) {
	BoxesISOExtractor * self = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
#line 7 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_return_val_if_fail (iso_path != NULL, NULL);
#line 7 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	self = (BoxesISOExtractor*) g_object_new (object_type, NULL);
#line 8 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp0_ = iso_path;
#line 8 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp1_ = g_strdup (_tmp0_);
#line 8 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_free0 (self->priv->device_file);
#line 8 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	self->priv->device_file = _tmp1_;
#line 7 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	return self;
#line 116 "iso-extractor.c"
}


BoxesISOExtractor* boxes_iso_extractor_new (const gchar* iso_path) {
#line 7 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	return boxes_iso_extractor_construct (BOXES_TYPE_ISO_EXTRACTOR, iso_path);
#line 123 "iso-extractor.c"
}


static void boxes_iso_extractor_extract_data_free (gpointer _data) {
	BoxesIsoExtractorExtractData* _data_;
	_data_ = _data;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_free0 (_data_->path);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_free0 (_data_->output_path);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_object_unref0 (_data_->cancellable);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_object_unref0 (_data_->self);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_slice_free (BoxesIsoExtractorExtractData, _data_);
#line 140 "iso-extractor.c"
}


static gpointer _g_object_ref0 (gpointer self) {
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	return self ? g_object_ref (self) : NULL;
#line 147 "iso-extractor.c"
}


void boxes_iso_extractor_extract (BoxesISOExtractor* self, const gchar* path, const gchar* output_path, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	BoxesIsoExtractorExtractData* _data_;
	BoxesISOExtractor* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	GCancellable* _tmp5_ = NULL;
	GCancellable* _tmp6_ = NULL;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_ = g_slice_new0 (BoxesIsoExtractorExtractData);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, boxes_iso_extractor_extract);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, boxes_iso_extractor_extract_data_free);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp0_ = _g_object_ref0 (self);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->self = _tmp0_;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp1_ = path;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp2_ = g_strdup (_tmp1_);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_free0 (_data_->path);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->path = _tmp2_;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp3_ = output_path;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp4_ = g_strdup (_tmp3_);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_free0 (_data_->output_path);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->output_path = _tmp4_;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp5_ = cancellable;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_tmp6_ = _g_object_ref0 (_tmp5_);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_object_unref0 (_data_->cancellable);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->cancellable = _tmp6_;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	boxes_iso_extractor_extract_co (_data_);
#line 196 "iso-extractor.c"
}


void boxes_iso_extractor_extract_finish (BoxesISOExtractor* self, GAsyncResult* _res_, GError** error) {
	BoxesIsoExtractorExtractData* _data_;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (_res_), error)) {
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		return;
#line 206 "iso-extractor.c"
	}
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
#line 210 "iso-extractor.c"
}


static gboolean boxes_iso_extractor_extract_co (BoxesIsoExtractorExtractData* _data_) {
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	switch (_data_->_state_) {
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		case 0:
#line 219 "iso-extractor.c"
		goto _state_0;
		default:
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_assert_not_reached ();
#line 224 "iso-extractor.c"
	}
	_state_0:
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp0_ = NULL;
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp0_ = _data_->path;
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp1_ = NULL;
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp1_ = _data_->self->priv->device_file;
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp2_ = NULL;
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp2_ = _data_->output_path;
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_debug ("iso-extractor.vala:12: Extracting '%s' from '%s' at path '%s'..", _data_->_tmp0_, _data_->_tmp1_, _data_->_tmp2_);
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp3_ = NULL;
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp3_ = _data_->self->priv->device_file;
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp4_ = NULL;
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp4_ = boxes_archive_reader_new (_data_->_tmp3_, NULL, NULL, &_data_->_inner_error_);
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->reader = _data_->_tmp4_;
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	if (G_UNLIKELY (_data_->_inner_error_ != NULL)) {
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_simple_async_result_set_from_error (_data_->_async_result, _data_->_inner_error_);
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_error_free (_data_->_inner_error_);
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		if (_data_->_state_ == 0) {
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
			g_simple_async_result_complete_in_idle (_data_->_async_result);
#line 261 "iso-extractor.c"
		} else {
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
			g_simple_async_result_complete (_data_->_async_result);
#line 265 "iso-extractor.c"
		}
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_object_unref (_data_->_async_result);
#line 13 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		return FALSE;
#line 271 "iso-extractor.c"
	}
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp5_ = NULL;
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp5_ = _data_->reader;
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp6_ = NULL;
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp6_ = _data_->path;
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp7_ = NULL;
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp7_ = _data_->output_path;
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	boxes_archive_reader_extract_file (_data_->_tmp5_, _data_->_tmp6_, _data_->_tmp7_, TRUE, &_data_->_inner_error_);
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	if (G_UNLIKELY (_data_->_inner_error_ != NULL)) {
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_simple_async_result_set_from_error (_data_->_async_result, _data_->_inner_error_);
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_error_free (_data_->_inner_error_);
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		_g_object_unref0 (_data_->reader);
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		if (_data_->_state_ == 0) {
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
			g_simple_async_result_complete_in_idle (_data_->_async_result);
#line 299 "iso-extractor.c"
		} else {
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
			g_simple_async_result_complete (_data_->_async_result);
#line 303 "iso-extractor.c"
		}
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_object_unref (_data_->_async_result);
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		return FALSE;
#line 309 "iso-extractor.c"
	}
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp8_ = NULL;
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp8_ = _data_->path;
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp9_ = NULL;
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp9_ = _data_->self->priv->device_file;
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp10_ = NULL;
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_data_->_tmp10_ = _data_->output_path;
#line 15 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_debug ("iso-extractor.vala:15: Extracted '%s' from '%s' at path '%s'.", _data_->_tmp8_, _data_->_tmp9_, _data_->_tmp10_);
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_object_unref0 (_data_->reader);
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	if (_data_->_state_ == 0) {
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_simple_async_result_complete_in_idle (_data_->_async_result);
#line 331 "iso-extractor.c"
	} else {
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
		g_simple_async_result_complete (_data_->_async_result);
#line 335 "iso-extractor.c"
	}
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_object_unref (_data_->_async_result);
#line 11 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	return FALSE;
#line 341 "iso-extractor.c"
}


static void boxes_iso_extractor_class_init (BoxesISOExtractorClass * klass) {
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	boxes_iso_extractor_parent_class = g_type_class_peek_parent (klass);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	g_type_class_add_private (klass, sizeof (BoxesISOExtractorPrivate));
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	G_OBJECT_CLASS (klass)->finalize = boxes_iso_extractor_finalize;
#line 352 "iso-extractor.c"
}


static void boxes_iso_extractor_instance_init (BoxesISOExtractor * self) {
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	self->priv = BOXES_ISO_EXTRACTOR_GET_PRIVATE (self);
#line 359 "iso-extractor.c"
}


static void boxes_iso_extractor_finalize (GObject* obj) {
	BoxesISOExtractor * self;
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, BOXES_TYPE_ISO_EXTRACTOR, BoxesISOExtractor);
#line 5 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	_g_free0 (self->priv->device_file);
#line 4 "/home/zeenix/checkout/gnome/gnome-boxes/src/iso-extractor.vala"
	G_OBJECT_CLASS (boxes_iso_extractor_parent_class)->finalize (obj);
#line 371 "iso-extractor.c"
}


GType boxes_iso_extractor_get_type (void) {
	static volatile gsize boxes_iso_extractor_type_id__volatile = 0;
	if (g_once_init_enter (&boxes_iso_extractor_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (BoxesISOExtractorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) boxes_iso_extractor_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (BoxesISOExtractor), 0, (GInstanceInitFunc) boxes_iso_extractor_instance_init, NULL };
		GType boxes_iso_extractor_type_id;
		boxes_iso_extractor_type_id = g_type_register_static (G_TYPE_OBJECT, "BoxesISOExtractor", &g_define_type_info, 0);
		g_once_init_leave (&boxes_iso_extractor_type_id__volatile, boxes_iso_extractor_type_id);
	}
	return boxes_iso_extractor_type_id__volatile;
}



