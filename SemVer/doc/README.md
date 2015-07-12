## version-increment ##
---


`version-increment` is a small utility written in c that allows for automation of increasing version numbers.
`version-increment` works with <a href="http://www.semver.org">semantic version</a> valid version strings.


**Syntax:**

  `version-increment` [version] [index to increment] [increment by] - increments the specified field by specified amount.<br>
  - major is index 0
  - minor is index 1
  - patch is index 2


`version-increment` [version] [increment by]: increments patch level by specified number
`version-increment` [version]: increments the patch level by 1
Specifying the version number as "-" will cause `version-increment` to read the version number from STDIN.


**Some examples:**

  - `version-increment 1.0.0` outputs `1.0.1`
  - `version-increment 2.0.0 0 1` outputs `3.0.0`
  - `printf "1.2.3" | version-increment -` outputs `1.2.4`

`version-increment` also supports reading and writing to files.

**Examples:**
  - `version-increment` test.txt
	if test.txt contains "1.2.0", the new contents of test.txt will be "1.2.1".
	`version-increment` will also output the new version number to stdout.

---

### Getting started ###

#### New Installation Method ####
  After cloning the repository or downloading a release, open a terminal in the project directory.
  Simply run `make` to compile the project -- the resulting binaries will be located in the ./build directory.
  `make install` will attempt to install the binaries into `~/scripts` *(this can be modified in the Makefile)*

#### Old Installation Method ####

_Once in the project folder, run `./build.sh` to compile the project._  
_The compiled binary will be in `./build`._
_You can also run `./build.sh install` and the script will attempt to install the binary into `/usr/bin`._
_Finally, you can run `./build.sh archive` and the script will generate an archive ready for release in the `./build/` folder._


---


### Example Usage ###
An example of using this utility would be automatically increasing a version number on every build.

**Sample Makefile**
*If version-increment has never been build or installed before, this will default the version to `0.1.0`.*

```Makefile
all: init myproject
	@echo "\n* Compiled all targets for $(THISPROJECT) project."
	@version-increment myproject-version.txt
	@exit 0

myproject:
	@gcc -O1 $(SRCDIR)/$@.c -o $(BUILDDIR)/$@.c
	@echo "* built '$@'."
	@exit 0

init:
	@if [ ! -f myproject-version.txt ]; then printf "0.1.0" > myproject-version.txt; fi
	@if [ -f `which version-increment` ]; then version-increment myproject-version.txt; fi
	@printf "#define VERSION = %s\n" `cat myproject-version.txt` > version.h	
	@exit 0

```

Here, each time `make` or `make all` is run, the various programs will be built, and then the version number will be increased.

Assuming `version.h` is included in myproject.c, the version for myproject would be automatically updated upon every build.

---

### License ###

`version-increment` is available under the <a href="LICENSE">MIT license</a>.