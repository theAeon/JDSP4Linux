Name:           JamesDSP
Version:        2.7.0
Release:        1%{?dist}
Source0:        JDSP4Linux-%{version}.tar.gz
ExclusiveArch:  x86_64
Summary:        An audio effect processor for PipeWire clients
License:        GPLv3
URL:            https://github.com/theAeon/JDSP4Linux/
BuildRequires:  libarchive-devel
BuildRequires:  (qt6-qtbase-devel or libqt6-qtbase-devel)
BuildRequires:  (qt6-qtbase-private-devel or libqt6-qtbase-private-headers-devel)
BuildRequires:  (qt6-qtsvg-devel or libqt6-qtsvg-devel)
BuildRequires:  gcc-c++
BuildRequires:  glibmm24-devel
BuildRequires:  glib2-devel
BuildRequires:  pipewire-devel
BuildRequires:  make
BuildRequires:  git
BuildRequires:  libxkbcommon-devel

Requires:    pipewire >= 0.3.19


%description
James DSP for Linux

%prep
%setup -n JDSP4Linux-%{version}
%global _qt6_build_tool make

%build
%qmake_qt6 JDSP4Linux.pro
%make_build

%install
install -D -m 755 build/src/jamesdsp %{buildroot}/%{_bindir}/jamesdsp
install -D -m 644 resources/icons/icon.png %{buildroot}/%{_datadir}/pixmaps/jamesdsp.png
install -D -m 644 resources/icons/icon.svg %{buildroot}/%{_datadir}/hicolor/scalable/apps/jamesdsp.svg
install -D -m 755 meta/jamesdsp.desktop %{buildroot}/%{_datadir}/applications/jamesdsp.desktop

%files
%license LICENSE
%{_bindir}/jamesdsp
%{_datadir}/pixmaps/jamesdsp.png
%{_datadir}/hicolor/scalable/apps/jamesdsp.svg
%{_datadir}/applications/jamesdsp.desktop

%changelog

