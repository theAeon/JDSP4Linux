Name:           JamesDSP
Version:        2.6.1
Release:        1%{?dist}
Source0:        JDSP4Linux-%{version}.tar.gz
ExclusiveArch:  x86_64
Summary:        An audio effect processor for PipeWire clients
License:        GPLv3
URL:            https://github.com/theAeon/JDSP4Linux/
BuildRequires:  libarchive-devel
BuildRequires:  (qt5-qtbase-devel >= 5.12.8 or libqt5-qtbase-devel >= 5.12.8)
BuildRequires:  (qt5-qtbase-private-devel or libqt5-qtbase-private-headers-devel)
BuildRequires:  (qt5-qtsvg-devel >= 5.12.8 or libqt5-qtsvg-devel >= 5.12.8)
BuildRequires:  gcc-c++
BuildRequires:  glibmm24-devel
BuildRequires:  glib2-devel
BuildRequires:  pipewire-devel
BuildRequires:  make
BuildRequires:  git


Requires:    pipewire >= 0.3.19


%description
James DSP for Linux

%prep
%setup -n JDSP4Linux-%{version}

%build
mkdir build
cd build
qmake-qt5 ../JDSP4Linux.pro
make

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

