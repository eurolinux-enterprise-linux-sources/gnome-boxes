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
    %if 0%{?fedora} >= 18
        %define qemu_kvm_arches %{ix86} x86_64 ppc64 s390x
    %endif
    %if 0%{?fedora} >= 20
        %define qemu_kvm_arches %{ix86} x86_64 %{power64} s390x %{arm} aarch64
    %endif
%endif

%if 0%{?rhel} >= 7
    %define qemu_kvm_arches    x86_64
%endif

%ifarch %{qemu_kvm_arches}
    %define with_qemu_kvm      1
%else
    %define with_qemu_kvm      0
%endif


#based on openSUSE spec file from dimstar, and on the Mageia .spec from bkor
%global url_ver	%%(echo %{version}|cut -d. -f1,2)

Name:		gnome-boxes
Version:	3.14.3.1
Release:	10%{?dist}
Summary:	A simple GNOME 3 application to access remote or virtual systems

Group:		Applications/Emulators
License:	LGPLv2+
URL:		https://live.gnome.org/Boxes
Source0:	http://download.gnome.org/sources/%{name}/%{url_ver}/%{name}-%{version}.tar.xz

BuildRequires:  libgovirt-devel >= 0.3.0
BuildRequires:	intltool
BuildRequires:	vala-devel >= 0.21.1
BuildRequires:	vala-tools >= 0.21.1
BuildRequires:	yelp-tools
BuildRequires:	pkgconfig(clutter-gtk-1.0) >= 1.3.2
BuildRequires:	pkgconfig(glib-2.0) => 2.32
BuildRequires:	pkgconfig(gobject-introspection-1.0) >= 0.9.6
BuildRequires:	pkgconfig(gtk+-3.0) >= 3.9
BuildRequires:	pkgconfig(gtk-vnc-2.0) >= 0.4.4
BuildRequires:	pkgconfig(libarchive)
BuildRequires:	pkgconfig(libvirt-gobject-1.0) >= 0.1.5
BuildRequires:	pkgconfig(libvirt-gconfig-1.0) >= 0.1.5
BuildRequires:	pkgconfig(libxml-2.0) >= 2.7.8
BuildRequires:	pkgconfig(gudev-1.0) >= 167
BuildRequires:	pkgconfig(libosinfo-1.0) >= 0.2.3
BuildRequires:	pkgconfig(libsoup-2.4) >= 2.38
BuildRequires:	spice-gtk3-vala >= 0.9
BuildRequires:	libosinfo-vala >= 0.0.4
BuildRequires:	desktop-file-utils
BuildRequires:	tracker-devel
BuildRequires:	libuuid-devel
#BuildRequires: autoconf automake libtool

# Pulls in libvirtd + KVM, but no NAT / firewall configs
%if %{with_qemu_kvm}
Requires:	libvirt-daemon-kvm
%else
Requires:	libvirt-daemon-qemu
%endif

# Pulls in libvirtd NAT based networking
# https://bugzilla.redhat.com/show_bug.cgi?id=1081762
Requires:	libvirt-daemon-config-network

# Needed for unattended installations
Requires:	mtools
Requires:	genisoimage

# gnome-boxes uses a dark theme
Requires:	adwaita-icon-theme
Requires:	gnome-themes-standard
Requires:	dconf

# https://bugzilla.gnome.org/show_bug.cgi?id=1072611
# Should not propose to install/boot from CD/DVD in RHEL7
Patch0: ignore-CDROM-devices.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1214294
# session networking limited to user interfaces only
Patch1: look-for-bridge.conf-in-qemu-kvm-dir-too.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1238719
# cannot start gnome boxes anymore
Patch2: more-reliable-storage-pool-setup.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1211198
# unattended installation of Fedora 20 doesn't work
Patch3: unattended-file-More-reliable-test-for-raw-images.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1201255
# Import from system broker fails for boxes with device nodes as main disks
Patch4: fix-import-of-system-libvirt-VMs.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1034354
# Cannot start non-running oVirt VM and then connect to it
Patch5: ovirt-Wait-machine-to-start-before-connecting-to-it.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1250270
# the intro label was forcing the window to be too tall
Patch6: deep-intro.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1043950
# gnome-boxes: local users can use SPICE connections to access other user's boxes
Patch7: private-SPICE-connection.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1336055
# Fix hostnames for win8.1 and beyond
Patch8: unattended-Avoid-invalid-chars-on-hostname.patch

# https://bugzilla.redhat.com/show_bug.cgi?id=1304291
# translation updates
Patch9: translations.patch

%description
gnome-boxes lets you easily create, setup, access, and use:
  * remote machines
  * remote virtual machines
  * local virtual machines
  * When technology permits, set up access for applications on
    local virtual machines


%prep
%setup -q

%patch0 -p1 -b .ignore-CDROM-devices
%patch1 -p1 -b .look-for-bridge.conf-in-qemu-kvm-dir-too
%patch2 -p1 -b .more-reliable-storage-pool-setup
%patch3 -p1 -b .unattended-file-More-reliable-test-for-raw-images
%patch4 -p1 -b .fix-import-of-system-libvirt-VMs
%patch5 -p1 -b .ovirt-Wait-machine-to-start-before-connecting-to-it
%patch6 -p1 -b .deep-intro
%patch7 -p1 -b .private-SPICE-connection
%patch8 -p1 -b .unattended-Avoid-invalid-chars-on-hostname
%patch9 -p1 -b .translations

%build
#fedora-legal and the fedora board permit logos to be enabled
#http://lists.fedoraproject.org/pipermail/advisory-board/2012-February/011360.html
%configure --enable-logos --enable-vala --enable-usbredir --enable-smartcard
make %{?_smp_mflags} V=1


%install
make install DESTDIR=%{buildroot}
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
%doc AUTHORS COPYING README NEWS TODO
%{_bindir}/%{name}
%{_datadir}/%{name}/
%{_datadir}/appdata/org.gnome.Boxes.appdata.xml
%{_datadir}/applications/org.gnome.Boxes.desktop
%{_datadir}/glib-2.0/schemas/org.gnome.boxes.gschema.xml
%{_datadir}/icons/hicolor/*/apps/gnome-boxes.*
%{_libexecdir}/gnome-boxes-search-provider
%{_datadir}/dbus-1/services/org.gnome.Boxes.SearchProvider.service
%{_datadir}/dbus-1/services/org.gnome.Boxes.service
%dir %{_datadir}/gnome-shell
%dir %{_datadir}/gnome-shell/search-providers
%{_datadir}/gnome-shell/search-providers/gnome-boxes-search-provider.ini

%changelog
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

