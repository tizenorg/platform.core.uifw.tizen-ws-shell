# to build examples
%define enable_examples 0

Name:           tzsh
Version:        0.1.0
Release:        0
Summary:        Tizen Window System Shell
License:        MIT
Group:          Graphics & UI Framework/Wayland Window System
Url:            http://www.samsung.com
Source0:        %name-%version.tar.gz
Source1001:     %name.manifest
BuildRequires:  pkgconfig(wayland-client)
BuildRequires:  pkgconfig(capi-base-common)

# requires to build examples
%if "%{enable_examples}" == "1"
BuildRequires:  pkgconfig(evas)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(efl-extension)
%endif

%description
Description: %{summary}

%package devel
Summary: Development files for package %{name}
Group:   Graphics & UI Framework/Development
Requires: %{name} = %{version}-%{release}
Requires: pkgconfig(capi-base-common)

%description devel
This package provides header files and other developer releated files
for package %{name}.

%prep
%setup -q
cp %{SOURCE1001} .

%build
export CFLAGS+=" -fvisibility=hidden -fPIC -Werror-implicit-function-declaration "
export LDFLAGS+=" -fvisibility=hidden -Wl,--hash-style=both -Wl,--as-needed"

%if "%{enable_examples}" == "1"
%autogen --enable-build-examples
%else
%autogen
%endif
make %{?jobs:-j%jobs}

%install
%make_install

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%defattr(-,root,root)
%{_libdir}/*.so.*
%if "%{enable_examples}" == "1"
%{_bindir}/*
%endif

%files devel
%manifest %{name}.manifest
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc
%{_includedir}/%{name}/*
%{_datadir}/%{name}/*
