/* wizard-sidebar.c generated by valac 0.26.1, the Vala compiler
 * generated from wizard-sidebar.vala, do not modify */

/* This file is part of GNOME Boxes. License: LGPLv2+*/

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>


#define BOXES_TYPE_WIZARD_SIDEBAR (boxes_wizard_sidebar_get_type ())
#define BOXES_WIZARD_SIDEBAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), BOXES_TYPE_WIZARD_SIDEBAR, BoxesWizardSidebar))
#define BOXES_WIZARD_SIDEBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), BOXES_TYPE_WIZARD_SIDEBAR, BoxesWizardSidebarClass))
#define BOXES_IS_WIZARD_SIDEBAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BOXES_TYPE_WIZARD_SIDEBAR))
#define BOXES_IS_WIZARD_SIDEBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BOXES_TYPE_WIZARD_SIDEBAR))
#define BOXES_WIZARD_SIDEBAR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), BOXES_TYPE_WIZARD_SIDEBAR, BoxesWizardSidebarClass))

typedef struct _BoxesWizardSidebar BoxesWizardSidebar;
typedef struct _BoxesWizardSidebarClass BoxesWizardSidebarClass;
typedef struct _BoxesWizardSidebarPrivate BoxesWizardSidebarPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define BOXES_TYPE_WIZARD_PAGE (boxes_wizard_page_get_type ())
#define _g_list_free0(var) ((var == NULL) ? NULL : (var = (g_list_free (var), NULL)))

struct _BoxesWizardSidebar {
	GtkBox parent_instance;
	BoxesWizardSidebarPrivate * priv;
};

struct _BoxesWizardSidebarClass {
	GtkBoxClass parent_class;
};

struct _BoxesWizardSidebarPrivate {
	GtkLabel* intro_label;
	GtkLabel* source_label;
	GtkLabel* preparation_label;
	GtkLabel* setup_label;
	GtkLabel* review_label;
};

typedef enum  {
	BOXES_WIZARD_PAGE_INTRODUCTION,
	BOXES_WIZARD_PAGE_SOURCE,
	BOXES_WIZARD_PAGE_PREPARATION,
	BOXES_WIZARD_PAGE_SETUP,
	BOXES_WIZARD_PAGE_REVIEW,
	BOXES_WIZARD_PAGE_LAST
} BoxesWizardPage;


static gpointer boxes_wizard_sidebar_parent_class = NULL;

GType boxes_wizard_sidebar_get_type (void) G_GNUC_CONST;
#define BOXES_WIZARD_SIDEBAR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), BOXES_TYPE_WIZARD_SIDEBAR, BoxesWizardSidebarPrivate))
enum  {
	BOXES_WIZARD_SIDEBAR_DUMMY_PROPERTY
};
GType boxes_wizard_page_get_type (void) G_GNUC_CONST;
void boxes_wizard_sidebar_set_page (BoxesWizardSidebar* self, BoxesWizardPage wizard_page);
BoxesWizardSidebar* boxes_wizard_sidebar_new (void);
BoxesWizardSidebar* boxes_wizard_sidebar_construct (GType object_type);
static void boxes_wizard_sidebar_finalize (GObject* obj);


static gpointer _g_object_ref0 (gpointer self) {
#line 25 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	return self ? g_object_ref (self) : NULL;
#line 71 "wizard-sidebar.c"
}


void boxes_wizard_sidebar_set_page (BoxesWizardSidebar* self, BoxesWizardPage wizard_page) {
	GList* _tmp0_ = NULL;
	GtkLabel* current_label = NULL;
	BoxesWizardPage _tmp3_ = 0;
	GtkLabel* _tmp14_ = NULL;
	GtkStyleContext* _tmp15_ = NULL;
#line 18 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	g_return_if_fail (self != NULL);
#line 19 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_tmp0_ = gtk_container_get_children ((GtkContainer*) self);
#line 85 "wizard-sidebar.c"
	{
		GList* label_collection = NULL;
		GList* label_it = NULL;
#line 19 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		label_collection = _tmp0_;
#line 19 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		for (label_it = label_collection; label_it != NULL; label_it = label_it->next) {
#line 93 "wizard-sidebar.c"
			GtkWidget* label = NULL;
#line 19 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			label = (GtkWidget*) label_it->data;
#line 97 "wizard-sidebar.c"
			{
				GtkWidget* _tmp1_ = NULL;
				GtkStyleContext* _tmp2_ = NULL;
#line 20 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
				_tmp1_ = label;
#line 20 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
				_tmp2_ = gtk_widget_get_style_context (_tmp1_);
#line 20 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
				gtk_style_context_remove_class (_tmp2_, "boxes-wizard-current-page-label");
#line 107 "wizard-sidebar.c"
			}
		}
#line 19 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		_g_list_free0 (label_collection);
#line 112 "wizard-sidebar.c"
	}
#line 22 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	current_label = NULL;
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_tmp3_ = wizard_page;
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	switch ((gint) _tmp3_) {
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		case BOXES_WIZARD_PAGE_INTRODUCTION:
#line 122 "wizard-sidebar.c"
		{
			GtkLabel* _tmp4_ = NULL;
			GtkLabel* _tmp5_ = NULL;
#line 25 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp4_ = self->priv->intro_label;
#line 25 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp5_ = _g_object_ref0 (_tmp4_);
#line 25 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_g_object_unref0 (current_label);
#line 25 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			current_label = _tmp5_;
#line 26 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			break;
#line 136 "wizard-sidebar.c"
		}
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		case BOXES_WIZARD_PAGE_SOURCE:
#line 140 "wizard-sidebar.c"
		{
			GtkLabel* _tmp6_ = NULL;
			GtkLabel* _tmp7_ = NULL;
#line 28 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp6_ = self->priv->source_label;
#line 28 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp7_ = _g_object_ref0 (_tmp6_);
#line 28 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_g_object_unref0 (current_label);
#line 28 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			current_label = _tmp7_;
#line 29 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			break;
#line 154 "wizard-sidebar.c"
		}
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		case BOXES_WIZARD_PAGE_PREPARATION:
#line 158 "wizard-sidebar.c"
		{
			GtkLabel* _tmp8_ = NULL;
			GtkLabel* _tmp9_ = NULL;
#line 31 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp8_ = self->priv->preparation_label;
#line 31 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp9_ = _g_object_ref0 (_tmp8_);
#line 31 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_g_object_unref0 (current_label);
#line 31 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			current_label = _tmp9_;
#line 32 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			break;
#line 172 "wizard-sidebar.c"
		}
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		case BOXES_WIZARD_PAGE_SETUP:
#line 176 "wizard-sidebar.c"
		{
			GtkLabel* _tmp10_ = NULL;
			GtkLabel* _tmp11_ = NULL;
#line 34 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp10_ = self->priv->setup_label;
#line 34 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp11_ = _g_object_ref0 (_tmp10_);
#line 34 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_g_object_unref0 (current_label);
#line 34 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			current_label = _tmp11_;
#line 35 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			break;
#line 190 "wizard-sidebar.c"
		}
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		case BOXES_WIZARD_PAGE_REVIEW:
#line 194 "wizard-sidebar.c"
		{
			GtkLabel* _tmp12_ = NULL;
			GtkLabel* _tmp13_ = NULL;
#line 37 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp12_ = self->priv->review_label;
#line 37 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_tmp13_ = _g_object_ref0 (_tmp12_);
#line 37 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			_g_object_unref0 (current_label);
#line 37 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			current_label = _tmp13_;
#line 38 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
			break;
#line 208 "wizard-sidebar.c"
		}
		default:
#line 23 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
		break;
#line 213 "wizard-sidebar.c"
	}
#line 40 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_tmp14_ = current_label;
#line 40 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_tmp15_ = gtk_widget_get_style_context ((GtkWidget*) _tmp14_);
#line 40 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_style_context_add_class (_tmp15_, "boxes-wizard-current-page-label");
#line 18 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_g_object_unref0 (current_label);
#line 223 "wizard-sidebar.c"
}


BoxesWizardSidebar* boxes_wizard_sidebar_construct (GType object_type) {
	BoxesWizardSidebar * self = NULL;
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	self = (BoxesWizardSidebar*) g_object_new (object_type, NULL);
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	return self;
#line 233 "wizard-sidebar.c"
}


BoxesWizardSidebar* boxes_wizard_sidebar_new (void) {
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	return boxes_wizard_sidebar_construct (BOXES_TYPE_WIZARD_SIDEBAR);
#line 240 "wizard-sidebar.c"
}


static void boxes_wizard_sidebar_class_init (BoxesWizardSidebarClass * klass) {
	gint BoxesWizardSidebar_private_offset;
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	boxes_wizard_sidebar_parent_class = g_type_class_peek_parent (klass);
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	g_type_class_add_private (klass, sizeof (BoxesWizardSidebarPrivate));
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	G_OBJECT_CLASS (klass)->finalize = boxes_wizard_sidebar_finalize;
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	BoxesWizardSidebar_private_offset = g_type_class_get_instance_private_offset (klass);
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass), "/org/gnome/Boxes/ui/wizard-sidebar.ui");
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "intro_label", FALSE, BoxesWizardSidebar_private_offset + G_STRUCT_OFFSET (BoxesWizardSidebarPrivate, intro_label));
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "source_label", FALSE, BoxesWizardSidebar_private_offset + G_STRUCT_OFFSET (BoxesWizardSidebarPrivate, source_label));
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "preparation_label", FALSE, BoxesWizardSidebar_private_offset + G_STRUCT_OFFSET (BoxesWizardSidebarPrivate, preparation_label));
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "setup_label", FALSE, BoxesWizardSidebar_private_offset + G_STRUCT_OFFSET (BoxesWizardSidebarPrivate, setup_label));
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "review_label", FALSE, BoxesWizardSidebar_private_offset + G_STRUCT_OFFSET (BoxesWizardSidebarPrivate, review_label));
#line 266 "wizard-sidebar.c"
}


static void boxes_wizard_sidebar_instance_init (BoxesWizardSidebar * self) {
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	self->priv = BOXES_WIZARD_SIDEBAR_GET_PRIVATE (self);
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	gtk_widget_init_template (GTK_WIDGET (self));
#line 275 "wizard-sidebar.c"
}


static void boxes_wizard_sidebar_finalize (GObject* obj) {
	BoxesWizardSidebar * self;
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, BOXES_TYPE_WIZARD_SIDEBAR, BoxesWizardSidebar);
#line 8 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_g_object_unref0 (self->priv->intro_label);
#line 10 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_g_object_unref0 (self->priv->source_label);
#line 12 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_g_object_unref0 (self->priv->preparation_label);
#line 14 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_g_object_unref0 (self->priv->setup_label);
#line 16 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	_g_object_unref0 (self->priv->review_label);
#line 6 "/home/zeenix/checkout/gnome/gnome-boxes/src/wizard-sidebar.vala"
	G_OBJECT_CLASS (boxes_wizard_sidebar_parent_class)->finalize (obj);
#line 295 "wizard-sidebar.c"
}


GType boxes_wizard_sidebar_get_type (void) {
	static volatile gsize boxes_wizard_sidebar_type_id__volatile = 0;
	if (g_once_init_enter (&boxes_wizard_sidebar_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (BoxesWizardSidebarClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) boxes_wizard_sidebar_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (BoxesWizardSidebar), 0, (GInstanceInitFunc) boxes_wizard_sidebar_instance_init, NULL };
		GType boxes_wizard_sidebar_type_id;
		boxes_wizard_sidebar_type_id = g_type_register_static (gtk_box_get_type (), "BoxesWizardSidebar", &g_define_type_info, 0);
		g_once_init_leave (&boxes_wizard_sidebar_type_id__volatile, boxes_wizard_sidebar_type_id);
	}
	return boxes_wizard_sidebar_type_id__volatile;
}



