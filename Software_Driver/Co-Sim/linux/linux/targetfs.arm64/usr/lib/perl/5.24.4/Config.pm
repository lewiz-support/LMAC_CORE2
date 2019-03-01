# This file was created by configpm when Perl was built. Any changes
# made to this file will be lost the next time perl is built.

# for a description of the variables, please have a look at the
# Glossary file, as written in the Porting folder, or use the url:
# http://perl5.git.perl.org/perl.git/blob/HEAD:/Porting/Glossary

package Config;
use strict;
use warnings;
use vars '%Config', '$VERSION';

$VERSION = "5.024004";

# Skip @Config::EXPORT because it only contains %Config, which we special
# case below as it's not a function. @Config::EXPORT won't change in the
# lifetime of Perl 5.
my %Export_Cache = (myconfig => 1, config_sh => 1, config_vars => 1,
		    config_re => 1, compile_date => 1, local_patches => 1,
		    bincompat_options => 1, non_bincompat_options => 1,
		    header_files => 1);

@Config::EXPORT = qw(%Config);
@Config::EXPORT_OK = keys %Export_Cache;

# Need to stub all the functions to make code such as print Config::config_sh
# keep working

sub bincompat_options;
sub compile_date;
sub config_re;
sub config_sh;
sub config_vars;
sub header_files;
sub local_patches;
sub myconfig;
sub non_bincompat_options;

# Define our own import method to avoid pulling in the full Exporter:
sub import {
    shift;
    @_ = @Config::EXPORT unless @_;

    my @funcs = grep $_ ne '%Config', @_;
    my $export_Config = @funcs < @_ ? 1 : 0;

    no strict 'refs';
    my $callpkg = caller(0);
    foreach my $func (@funcs) {
	die qq{"$func" is not exported by the Config module\n}
	    unless $Export_Cache{$func};
	*{$callpkg.'::'.$func} = \&{$func};
    }

    *{"$callpkg\::Config"} = \%Config if $export_Config;
    return;
}

die "$0: Perl lib version (5.24.4) doesn't match executable '$^X' version ($])"
    unless $^V;

$^V eq 5.24.4
    or die sprintf "%s: Perl lib version (5.24.4) doesn't match executable '$^X' version (%vd)", $0, $^V;


sub FETCH {
    my($self, $key) = @_;

    # check for cached value (which may be undef so we use exists not defined)
    return exists $self->{$key} ? $self->{$key} : $self->fetch_string($key);
}

sub TIEHASH {
    bless $_[1], $_[0];
}

sub DESTROY { }

sub AUTOLOAD {
    require 'Config_heavy.pl';
    goto \&launcher unless $Config::AUTOLOAD =~ /launcher$/;
    die "&Config::AUTOLOAD failed on $Config::AUTOLOAD";
}

# tie returns the object, so the value returned to require will be true.
tie %Config, 'Config', {
    ar => 'aarch64-poky-linux-ar',
    archlibexp => '/usr/lib/perl/5.24.4/',
    archname => 'aarch64-linux',
    cc => 'aarch64-poky-linux-gcc  -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security ',
    cccdlflags => '-fPIC',
    ccdlflags => '-Wl,-E -Wl,-rpath,/usr/lib/perl/5.24.4//CORE',
    d_flexfnam => 'define',
    d_link => 'define',
    d_readlink => 'define',
    d_symlink => 'define',
    dlext => 'so',
    dlsrc => 'dl_dlopen.xs',
    dont_use_nlink => undef,
    eunicefix => ':',
    exe_ext => '',
    full_ar => 'aarch64-poky-linux/aarch64-poky-linux-ar',
    inc_version_list => ' ',
    installman1dir => '',
    installman3dir => '',
    installprivlib => '/usr/lib/perl/5.24.4',
    installscript => '/usr/bin',
    installsitearch => '/usr/lib/perl/site_perl/5.24.4/',
    installsitebin => '/usr/bin',
    installsiteman1dir => '',
    installsiteman3dir => '',
    installvendorman1dir => '',
    installvendorman3dir => '',
    intsize => '4',
    ld => 'aarch64-poky-linux-gcc  -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security ',
    lddlflags => '-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -fstack-protector-strong -Wl,-z,relro,-z,now -fstack-protector -shared',
    ldflags => '-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -fstack-protector-strong -Wl,-z,relro,-z,now -fstack-protector',
    ldlibpthname => 'LD_LIBRARY_PATH',
    lib_ext => '.a',
    libc => 'libc-2.21.so',
    libpth => '/usr/lib /lib',
    obj_ext => '.o',
    osname => 'linux',
    osvers => '3.19.5-yocto-standard',
    path_sep => ':',
    privlibexp => '/usr/lib/perl/5.24.4',
    ranlib => ':',
    scriptdir => '/usr/bin',
    sitearchexp => '/usr/lib/perl/site_perl/5.24.4/',
    sitelibexp => '/usr/lib/perl/site_perl/5.24.4',
    so => 'so',
    useithreads => 'define',
    usevendorprefix => 'define',
    vendorarchexp => '/usr/lib/perl/vendor_perl/5.24.4/',
    vendorlibexp => '/usr/lib/perl/vendor_perl/5.24.4',
    version => '5.24.4',
};
