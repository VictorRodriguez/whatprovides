# whatprovides

whatprovides is a tool to find what package and bundle provide a binary in Clear Linux OS

## Getting Started

Usually as Clear Linux user is handy to have a tool that tell us what package (rpm) provides a binary or a library that we are using. With whatprovides this is possible with one single command line. Download the latest release uncompress and with autotools you can easily build the project

### Prerequisites

Autotools and GCC

```
autoreconf -i
make
```

### Installing

whatprovides uses tha basic autotools system

```
cd whatprovides
autoreconf -i
./configure
make
make install
```

Then put your dnf.conf in /etc

The dnf.conf from Clear Linux can be downloaded from: 

https://raw.githubusercontent.com/clearlinux/common/master/conf/dnf.conf


## Running the tests

If we want to search what pkg provides the ls cmd

```
$ whatprovides /usr/bin/ls
Last metadata expiration check: 13:37:08 ago on Sat 20 Oct 2018 04:06:27 AM UTC.
coreutils-bin-8.30-48.x86_64 : bin components for the coreutils package.
Repo        : clear
Matched from:
Filename    : /usr/bin/ls
```

Or the GCC compiler

```

$ whatprovides /usr/bin/gcc
Last metadata expiration check: 13:37:22 ago on Sat 20 Oct 2018 04:06:27 AM UTC.
gcc-8.2.0-177.x86_64 : GNU cc and gcc C compilers
Repo        : clear
Matched from:
Filename    : /usr/bin/gcc
```

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/VictorRodriguez/whatprovides/tags). 

## Authors

* **Victor Rodriguez** - *Initial work* - [PurpleBooth](https://github.com/VictorRodriguez)

## License

This project is licensed under the Apache License - see the [LICENSE.md](LICENSE.md) file for details

