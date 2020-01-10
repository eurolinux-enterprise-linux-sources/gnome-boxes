// This file is part of GNOME Boxes. License: LGPLv2+

private interface Boxes.ICollectionView: Gtk.Widget {
    public abstract CollectionFilter filter { get; protected set; }

    public abstract void add_item (CollectionItem item);
    public abstract void remove_item (CollectionItem item);
    public abstract List<CollectionItem> get_selected_items ();
    public abstract void activate_first_item ();
    public abstract void select_by_criteria (SelectionCriteria criteria);
}
