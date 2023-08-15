.ONESHELL:

.SHELLFLAGS += -e
DNF := $(shell command -v dnf 2> /dev/null)
ZYP := $(shell command -v zypper 2> /dev/null)

srpm:
ifdef DNF
	dnf -y install qt6-qtbase-devel qt6-qtbase-private-devel qt6-qtsvg-devel gcc-c++ glib2-devel glibmm24-devel \
	libarchive-devel pipewire-devel git python3-pip perl-rpm-build-perl perl-IPC-System-Simple perl-Path-Class \
	perl-Test-Pod perl-Module-Build
endif
ifdef ZYP
	zypper install -y libqt6-qtbase-devel libqt6-qtbase-private-devel libqt6-qtsvg-devel gcc-c++ glib2-devel \
	glibmm24-devel libarchive-devel pipewire-devel git python310-pip rpm-build-perl perl-IPC-System-Simple \
	perl-Path-Class perl-Test-Pod perl-Module-Build
endif
	git submodule update
	git config --global --add safe.directory "*"
	PATH=/usr/local/bin:${PATH}
	pip install --upgrade pip
	pip install git-archive-all
	git clone https://github.com/iovation/git-build-rpm.git
	cd git-build-rpm
	perl Build.PL
	./Build
	patch bin/git-build-rpm -i ../.copr/srpm.patch
	cd ..
	git-build-rpm/bin/git-build-rpm --spec-file $(spec)
	mv *.src.rpm $(outdir)
