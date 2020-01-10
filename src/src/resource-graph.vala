// This file is part of GNOME Boxes. License: LGPLv2+

[GtkTemplate (ui = "/org/gnome/Boxes/ui/resource-graph.ui")]
private class Boxes.ResourceGraph: Gtk.DrawingArea {
    private double[] _points;
    public double[] points { get { return _points; }
        set {
            if (value[value.length - 1] > ymax)
                ymax = value[value.length - 1];

            _points = value;
            queue_draw ();
        }
    }
    public int npoints { get; set; default = -1; }

    private double _ymax;
    public double ymax { get { return _ymax; }
        set {
            _ymax = value;
        }
    }

    public ResourceGraph (double ymax) {
        this.ymax = ymax;
        width_request = 120;
        height_request = 60;
        expand = true;
    }

    public override bool draw (Cairo.Context cr) {
        var width = get_allocated_width ();
        var height = get_allocated_height ();
        var style = get_style_context ();

        style.render_background (cr, 0, 0, width, height);

        var nstep = (npoints == -1 ? points.length : npoints) - 1;
        var dy = 0.0;
        var dx = 0.0;
        if (nstep != 0)
            dx = (double) width / nstep;
        if (ymax != 0)
            dy = (double) height / ymax;

        style.save ();
        style.set_state (Gtk.StateFlags.NORMAL);
        Gdk.cairo_set_source_rgba (cr, style.get_color (get_state_flags ()));
        style.restore ();
        var x = 0.0;
        foreach (var p in points) {
            var y = height - p * dy;
            if (x == 0.0)
                cr.move_to (x, y);
            else
                cr.line_to (x, y);
            x += dx;
        }
        cr.line_to (x - dx, height);
        cr.line_to (0, height);
        cr.fill ();

        Gdk.cairo_set_source_rgba (cr, style.get_border_color (get_state_flags ()));
        cr.set_line_width (1.0);
        x = 0.0;
        foreach (var p in points) {
            var y = height - p * dy;

            if (x == 0.0)
                cr.move_to (x, y);
            else
                cr.line_to (x, y);
            x += dx;
        }
        cr.stroke ();

        return true;
    }
}
