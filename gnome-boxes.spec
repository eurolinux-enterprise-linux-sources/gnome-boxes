# Since RHEL-5, QEMU is restricted to x86_64 only
# As Boxes don't really handle the !qemu case very well (untested, the 'box
# creation' UI would still be there but non-functional, ...), better to
# only build Boxes on platforms where qemu/qemu-kvm are available
%if 0%{?rhel}
ExclusiveArch: x86_64
%endif


# The following qemu_kvm_arches/with_qemu_kvm defines come from
# libvirt.spec
%if 0%{?fedora}
    %global qemu_kvm_arches %{ix86} x86_64 %{power64} s390x %{arm} aarch64
    %global distributor_name fedora
    %global distributor_version %{fedora}
%endif

%if 0%{?rhel} >= 7
    %global qemu_kvm_arches    x86_64 %{power64}
    %global distributor_name rhel
    %global distributor_version %{rhel}
%endif

%ifarch %{qemu_kvm_arches}
    %global with_qemu_kvm      1
%else
    %global with_qemu_kvm      0
%endif

%global url_ver	%%(echo %{version}|cut -d. -f1,2)

Name:		gnome-boxes
Version:	3.28.5
Release:	4%{?dist}
Summary:	A simple GNOME 3 application to access remote or virtual systems

License:	LGPLv2+
URL:		https://wiki.gnome.org/Apps/Boxes
Source0:	http://download.gnome.org/sources/%{name}/%{url_ver}/%{name}-%{version}.tar.xz

# https://gitlab.gnome.org/GNOME/gnome-boxes/issues/217
Patch0:		gnome-boxes-unbreak-the-icon-installation.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1449922
Patch1:		use-ps2-bus-by-default.patch

Patch2:		gnome-boxes-python2.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1569793
Patch3:		gnome-boxes-libgovirt-tracker.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1595754
Patch4: 	revert-use-virtio-video-adapter.patch

# https://bugzilla.redhat.com/1656448
Patch5:     gnome-boxes-hardcode-recommended-oses.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1713005
Patch6:     gnome-boxes-update-rhel-logo.patch

BuildRequires:	gettext >= 0.19.8
BuildRequires:	meson
BuildRequires:	vala >= 0.36.0
BuildRequires:	yelp-tools
BuildRequires:	pkgconfig(clutter-gtk-1.0)
BuildRequires:	pkgconfig(glib-2.0) >= 2.52
BuildRequires:	pkgconfig(gobject-introspection-1.0)
BuildRequires:	pkgconfig(govirt-1.0)
BuildRequires:	pkgconfig(gtk+-3.0) >= 3.22.20
BuildRequires:	pkgconfig(gtk-vnc-2.0)
BuildRequires:	pkgconfig(libarchive)
BuildRequires:	pkgconfig(json-glib-1.0)
BuildRequires:	pkgconfig(libsecret-1)
BuildRequires:	pkgconfig(libvirt-gobject-1.0)
BuildRequires:	pkgconfig(libvirt-gconfig-1.0)
BuildRequires:	pkgconfig(libxml-2.0)
BuildRequires:	pkgconfig(gudev-1.0)
BuildRequires:	pkgconfig(libosinfo-1.0) >= 1.1.0
BuildRequires:	pkgconfig(libsoup-2.4) >= 2.44
BuildRequires:	pkgconfig(libusb-1.0)
BuildRequires:	pkgconfig(tracker-sparql-1.0)
BuildRequires:	pkgconfig(webkit2gtk-4.0)
BuildRequires:	spice-gtk3-vala
BuildRequires:	libosinfo-vala
BuildRequires:	desktop-file-utils

# Pulls in libvirtd + KVM, but no NAT / firewall configs
%if %{with_qemu_kvm}
Requires:	libvirt-daemon-kvm
%else
Requires:	libvirt-daemon-qemu
%endif

# Pulls in the libvirtd NAT 'default' network
# Original request: https://bugzilla.redhat.com/show_bug.cgi?id=1081762
#
# However, the 'default' network does not mix well with the Fedora livecd
# when it is run inside a VM. The whole saga is documented here:
#
#   boxes: https://bugzilla.redhat.com/show_bug.cgi?id=1164492
#   libvirt: https://bugzilla.redhat.com/show_bug.cgi?id=1146232
#
# Until a workable solution has been determined and implemented, this
# dependency should stay disabled in rawhide and fedora development
# branches so it does not end up on the livecd. Once a Fedora GA is
# released, a gnome-boxes update can be pushed with this dependency
# re-enabled. crobinso will handle this process, see:
#
#    https://bugzilla.redhat.com/show_bug.cgi?id=1164492#c71
Requires:	libvirt-daemon-config-network

# Needed for unattended installations
Requires:	mtools
Requires:	genisoimage

Requires:	adwaita-icon-theme

%description
gnome-boxes lets you easily create, setup, access, and use:
  * remote machines
  * remote virtual machines
  * local virtual machines
  * When technology permits, set up access for applications on
    local virtual machines

%prep
%setup -q
%patch0 -p1
%patch1 -p1 -b .use-ps2-bus-by-default
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1

%build
%meson \
%if %{?distributor_name:1}%{!?distributor_name:0}
    -D distributor_name=%{distributor_name} \
%endif
%if 0%{?distributor_version}
    -D distributor_version=%{distributor_version} \
%endif

%meson_build

%install
%meson_install
%find_lang %{name} --with-gnome

%check
desktop-file-validate %{buildroot}%{_datadir}/applications/org.gnome.Boxes.desktop

%post
update-desktop-database &> /dev/null || :
touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :

%postun
update-desktop-database &> /dev/null || :
if [ $1 -eq 0 ] ; then
    touch --no-create %{_datadir}/icons/hicolor &>/dev/null
    gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
    glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :
fi

%posttrans
gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :

%files -f %{name}.lang
%license COPYING
%doc AUTHORS README NEWS TODO
%{_bindir}/%{name}
%{_datadir}/%{name}/
%{_datadir}/applications/org.gnome.Boxes.desktop
%{_datadir}/glib-2.0/schemas/org.gnome.boxes.gschema.xml
%{_datadir}/icons/hicolor/*/apps/org.gnome.Boxes.png
%{_datadir}/icons/hicolor/symbolic/apps/org.gnome.Boxes-symbolic.svg
%{_libexecdir}/gnome-boxes-search-provider
%{_datadir}/dbus-1/services/org.gnome.Boxes.SearchProvider.service
%{_datadir}/dbus-1/services/org.gnome.Boxes.service
%dir %{_datadir}/gnome-shell
%dir %{_datadir}/gnome-shell/search-providers
%{_datadir}/gnome-shell/search-providers/gnome-boxes-search-provider.ini
%{_datadir}/metainfo/org.gnome.Boxes.appdata.xml

%changelog
* Wed May 22 2019 Fabiano Fidêncio <fidencio@redhat.com> - 3.28.5-4
- Add rhel-8 logo & update rhel logo
- Resolves: #1713005

* Wed Dec 05 2018 Felipe Borges <feborges@redhat.com> - 3.28.5-3
- Pick our recommended downloads
- Related #1656448

* Mon Jul 16 2018 Felipe Borges <feborges@redhat.com> - 3.28.5-2
- Revert using VIRTIO video adapter by default for new VMs
- Resolves: #1595754

* Fri Jun 08 2018 Debarshi Ray <rishi@fedoraproject.org> - 3.28.5-1
- Update to 3.28.5
- Fix the libgovirt requirement
- Revert to using Python 2 and Tracker 1.0
- Resolves: #1567399

* Thu Jun 08 2017 Felipe Borges <feborges@redhat.com> - 3.22.4-4
- Use PS2 bus by default
- Related: #1449922

* Wed May 24 2017 Felipe Borges <feborges@redhat.com> - 3.22.4-3
- Run "make vala-clean" before make install
- Related: #1435336

* Wed Mar 15 2017 Kalev Lember <klember@redhat.com> - 3.22.4-2
- Rebuilt for spice-gtk3 soname bump
- Related: #1402474

* Mon Feb 06 2017 Kalev Lember <klember@redhat.com> - 3.22.4-1
- Update to 3.22.4
- Resolves: #1386879

* Fri Jul  1 2016 Matthias Clasen <mclasen@redat.com> - 3.14.3.1-10
- Update translations
  Resolves: #1304291

* Tue May 17 2016 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-9
- Avoid characters in hostname, not accepted by Windows. (related: #1336055).

* Tue May 10 2016 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-8
- Private SPICE connection. (related: #1043950).

* Wed Aug 19 2015 Matthias Clasen <mclasen@redhat.com> - 3.14.3.1-7
- Make window less tall
  Resolves: #1250270

* Wed Jul 29 2015 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-6
- Wait machine to start before connecting to it. (related: #1034354).

* Wed Jul 22 2015 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-5
- Fix import of system VMs. (related: #1201255).

* Fri Jul 17 2015 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-4
- More reliable test for raw images (related: #1211198).

* Wed Jul 15 2015 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-3
- More reliable storage pool setup (related: #1238719).

* Fri May 22 2015 Zeeshan Ali <zeenix@redhat.com> - 3.14.3.1-2
- Look for bridge.conf in qemu-kvm dir too (related: #1214294).

* Thu Mar 19 2015 Richard Hughes <rhughes@redhat.com> - 3.14.3.1-1
- Update to 3.14.3.1.

* Mon Oct 13 2014 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-11
- Don't hang on failure to handle a URL (related: #1046251).
- Handle paths as well (related: #1046251).
- Handle local paths to remote files (related: #1046251).

* Thu Oct  9 2014 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-10
- Set volume capacity in correct units (related: #1049316).
- Refresh volume info after resize (related: #1049316).

* Thu Jul 24 2014 Marc-Andre Lureau <marcandre.lureau@redhat.com> - 3.8.3-9
- Rebuild to pick new libgovirt
  Resolves: #1117928

* Mon Mar 17 2014 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-8
- Don't register for 'x-content/bootable-media' (related: #1072611).
- Ignore CDROM devices (related: #1072611).
- Ignore non-readable devices (related: #1043892)

* Wed Mar 12 2014 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-7
- Fix a crash in get_decoded_udev_property (related: #1061216).

* Fri Feb 28 2014 Matthias Clasen <mclasen@redhat.com> - 3.8.3-6
- Rebuild
Resolves: #1070807

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 3.8.3-5
- Mass rebuild 2013-12-27

* Tue Dec 17 2013 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-4
- Remove media from correct box (related: #846408).
- Remove existing transition before adding new one (related: #1015079).

* Wed Dec  4 2013 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-3
- Complete translations (related: #1030336).

* Fri Nov  8 2013 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-2
- Fix rhbz#968285

* Tue May 28 2013 Zeeshan Ali <zeenix@redhat.com> - 3.8.3-1
- Update to 3.8.3.

* Mon May 27 2013 Kalev Lember <kalevlember@gmail.com> 3.8.2-5
- Only pull in qemu on non-kvm arches

* Fri May 24 2013 Christophe Fergeau <cfergeau@redhat.com> 3.8.2-4
- ... and remove again the ExclusiveArch on fedora. If libvirt-daemon-qemu
  is available, this means we can create (very slow) x86 boxes regardless
  of the arch

* Thu May 23 2013 Christophe Fergeau <cfergeau@redhat.com> 3.8.2-3
- Readd ExclusiveArch as Boxes is not really functional on non-x86
  arch even if it can be built. Also, libvirt-daemon-kvm is not
  available on every arch, causing rhbz#962325

* Thu May 16 2013 Christophe Fergeau <cfergeau@redhat.com> 3.8.2-2
- Add upstream patch for rhbz#963464

* Tue May 14 2013 Zeeshan Ali <zeenix@redhat.com> - 3.8.2-1
- Update to 3.8.2.

* Thu Apr 18 2013 Christophe Fergeau <cfergeau@redhat.com> 3.8.1.2-1
- Update to 3.8.1.2

* Tue Apr 16 2013 Richard Hughes <rhughes@redhat.com> - 3.8.1-1
- Update to 3.8.1

* Tue Mar 26 2013 Richard Hughes <rhughes@redhat.com> - 3.8.0-1
- Update to 3.8.0

* Wed Mar 20 2013 Richard Hughes <rhughes@redhat.com> - 3.7.92-1
- Update to 3.7.92

* Fri Mar  8 2013 Matthias Clasen <mclasen@redhat.com> - 3.7.91-1
- Update to 3.7.91

* Thu Feb 21 2013 Kalev Lember <kalevlember@gmail.com> - 3.7.90-2
- Rebuilt for cogl soname bump

* Thu Feb 21 2013 Christophe Fergeau <cfergeau@redhat.com> 3.7.90-1
- Update do 3.7.90

* Wed Feb 06 2013 Richard Hughes <rhughes@redhat.com> - 3.7.5-1
- Update to 3.7.5

* Sun Jan 27 2013 Kalev Lember <kalevlember@gmail.com> - 3.7.4-3
- Rebuilt for tracker 0.16 ABI

* Fri Jan 25 2013 Peter Robinson <pbrobinson@fedoraproject.org> 3.7.4-2
- Rebuild for new cogl

* Tue Jan 15 2013 Zeeshan Ali <zeenix@redhat.com> - 3.7.4-1
- Update to 3.7.4.

* Thu Dec 20 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.7.3-1
- Update to 3.7.3

* Tue Nov 20 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.7.2-2
- Reenable USB redirection (it's disabled by default, packagers must
  enable it if appropriate)

* Tue Nov 20 2012 Zeeshan Ali <zeenix@redhat.com> - 3.7.2-1
- Update to 3.7.2.

* Tue Nov 13 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.6.2-2
- Update to 3.6.2

* Tue Oct 16 2012 Zeeshan Ali <zeenix@redhat.com> - 3.6.1.1-2
- Enable USB redirection in new domains.

* Tue Oct 16 2012 Zeeshan Ali <zeenix@redhat.com> - 3.6.1.1-1
- Update to 3.6.1.1

* Mon Oct 15 2012 Zeeshan Ali <zeenix@redhat.com> - 3.6.1-1
- Update to 3.6.1

* Tue Sep 25 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.6.0-1
- Update to 3.6.0

* Wed Sep 19 2012 Richard Hughes <hughsient@gmail.com> - 3.5.92-1
- Update to 3.5.92

* Thu Sep  6 2012 Matthias Clasen <mclasen@redhat.com> - 3.5.91-2
- Rebuild against new spice

* Tue Sep 04 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.5.91-1
- Update do 3.5.91

* Wed Aug 22 2012 Richard Hughes <hughsient@gmail.com> - 3.5.90-1
- Update to 3.5.90

* Tue Aug 07 2012 Richard Hughes <hughsient@gmail.com> - 3.5.5-1
- Update to 3.5.5

* Thu Jul 19 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 3.5.4.1-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Mon Jul 16 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.5.4.1-1
- Update to 3.5.4.1

* Mon Jul 16 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.5.4-1
- Update to 3.5.4
- Update some BuildRequires min version

* Tue Jun 26 2012 Richard Hughes <hughsient@gmail.com> - 3.5.3-1
- Update to 3.5.3

* Thu Jun 07 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.5.2-2
- enable logos after getting confirmation this has been approved by
  fedora-legal and the Fedora board

* Thu Jun 07 2012 Richard Hughes <hughsient@gmail.com> - 3.5.2-1
- Update to 3.5.2

* Wed May 16 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.4.2-2
- Remove ExclusiveArch now that spice-gtk is built on all arch

* Tue May 15 2012 Zeeshan Ali <zeenix@redhat.com> - 3.4.2-1
- Update to 3.4.2

* Thu Apr 26 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.4.1-2
- Backport a few upstream patches:
  - asynchronously fetch domain information from libvirt, this makes Boxes
    much more responsive
  - make the file chooser dialog modal
  - fix f17 unattended installation

* Tue Apr 17 2012 Richard Hughes <hughsient@gmail.com> - 3.4.1-1
- Update to 3.4.1

* Sat Mar 31 2012 Daniel P. Berrange <berrange@redhat.com> - 3.4.0.1-2
- Only pull in libvirtd + KVM drivers, without default configs (bug 802475)

* Sat Mar 31 2012 Zeeshan Ali <zeenix@redhat.com> - 3.4.0.1-1
- Update to 3.4.0.1

* Mon Mar 26 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.4.0-1
- Update to 3.4.0

* Mon Mar 26 2012 Dan Horák <dan[at]danny.cz> - 3.3.92-2
- set ExclusiveArch equal to spice-gtk

* Tue Mar 20 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.92-1
- Update to 3.3.92

* Tue Mar  6 2012 Matthias Clasen <mclasen@redhat.com> - 3.3.91-1
- Update to 3.3.91

* Sun Feb 26 2012 Matthias Clasen <mclasen@redhat.com> - 3.3.90-1
- Update to 3.3.90

* Wed Feb 08 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.5.1-1
- Update to 3.3.5.1

* Wed Jan 25 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.4.1-1
- Update to minor 3.3.4.1 release

* Fri Jan 20 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.4-4
- call desktop-file-validate in %%install. gnome-boxes upstream installs
  a .desktop file on its own so desktop-file-validate is enough, no need
  to call desktop-file-install.

* Fri Jan 20 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.4-3
- Fix %%global use (%%url_ver got expanded to 3.3.4 instead of 3.3 in
  -2)

* Tue Jan 17 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.4-2
- Remove use of BuildRoot
- Remove use of defattr
- Use %%global instead of %%define

* Tue Jan 17 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.4-1
- Update to 3.3.4 release

* Thu Jan 05 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.3-3
- Escape %%{buildroot} in changelog
- Remove empty %%pre section

* Wed Jan 04 2012 Christophe Fergeau <cfergeau@redhat.com> - 3.3.3-2
- Use %%{buildroot} instead of $RPM_BUILD_ROOT
- Remove unneeded patch
- Add missing dependency on fuseiso

* Fri Dec 23 2011 Christophe Fergeau <cfergeau@redhat.com> - 3.3.3-1
- Initial import

