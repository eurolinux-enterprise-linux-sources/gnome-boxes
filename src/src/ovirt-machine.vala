// This file is part of GNOME Boxes. License: LGPLv2+
using Ovirt;
using Gtk;

private class Boxes.OvirtMachine: Boxes.Machine {
    public override bool can_restart { get { return false; } }
    public override bool can_clone { get { return false; } }

    private Ovirt.Vm vm;
    private Ovirt.Proxy proxy;

    public OvirtMachine (CollectionSource source,
                         Ovirt.Proxy proxy,
                         Ovirt.Vm vm) throws GLib.Error {
        base (source, vm.name, vm.guid);

        debug ("new ovirt machine: " + name);
        this.proxy = proxy;
        this.vm = vm;

        this.update_state ();

        load_screenshot ();
        set_screenshot_enable (true);
        update_info ();

        source.notify["uri"].connect (update_info);
    }

    public override async void connect_display (Machine.ConnectFlags flags) throws GLib.Error {
        if (display != null)
            return;

        connecting_cancellable.reset ();

        if (state == MachineState.STOPPED)
            try {
                yield vm.start_async (proxy, connecting_cancellable);
                this.update_state ();
            } catch (IOError.CANCELLED error) {
                debug ("connection to %s was cancelled", name);

                return;
            } catch (GLib.Error error) {
                throw new Boxes.Error.INVALID ("Couldn't start oVirt VM '%s': %s", vm.name, error.message);
            }

        if (state != MachineState.RUNNING)
            throw new Boxes.Error.INVALID ("oVirt VM '%s' is not RUNNING", vm.name);

        try {
            display = create_display_connection ();
            if (vm.display.type == Ovirt.VmDisplayType.SPICE) {
                yield vm.get_ticket_async (proxy, connecting_cancellable);
                display.password = vm.display.ticket;
            }

            display.connect_it ();
        } catch (IOError.CANCELLED error) {
            debug ("connection to %s was cancelled", name);
        } catch (GLib.Error e) {
            throw new Boxes.Error.INVALID ("Error opening display: %s", e.message);
        }
    }

    public override List<Boxes.Property> get_properties (Boxes.PropertiesPage page) {
        var list = new List<Boxes.Property> ();

        switch (page) {
        case PropertiesPage.GENERAL:
            add_string_property (ref list, _("Broker"), source.name);
            add_string_property (ref list, _("Protocol"), display.protocol);
            add_string_property (ref list, _("URL"), display.uri);
            break;
        }

        list.concat (display.get_properties (page));

        return list;
    }

    public override void restart () {} // See FIXME on RemoteMachine.restart
    public override async void clone () {}

    private void update_info () {
        var uri = Xml.URI.parse (source.uri);

        info = _("host: %s").printf (uri.server);
    }

    private Display create_display_connection () throws GLib.Error {
        if (vm.display.address == null || vm.display.address == "")
            throw new Boxes.Error.INVALID ("empty display address for %s", vm.name);

        switch (vm.display.type) {
        case Ovirt.VmDisplayType.SPICE:
            var display = new SpiceDisplay (this,
                                            config,
                                            vm.display.address,
                                            (int) vm.display.port,
                                            (int) vm.display.secure_port,
                                            vm.display.host_subject);
            display.ca_cert = proxy.ca_cert;
            return display;

        case Ovirt.VmDisplayType.VNC:
            return new VncDisplay (config, vm.display.address, (int) vm.display.port);

        default:
            warning ("unsupported display of type %d", vm.display.type);
            throw new Boxes.Error.INVALID ("unsupported display type %d for %s", vm.display.type, vm.name);
        }
    }
    private void update_state () {
        switch (vm.state) {
            case VmState.UP:
                state = MachineState.RUNNING;
                break;
            case VmState.DOWN:
                state = MachineState.STOPPED;
                break;
            default:
                state = MachineState.UNKNOWN;
                break;
        }
    }

}
