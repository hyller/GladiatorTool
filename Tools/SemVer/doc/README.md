# SemVer

`SemVer` creates version head file, increases version and appends the version to a file name.  
The version format defined in [semver.org](http://semver.org)

## Usage

Usage: semver [option] [file]  
  
Options:  
-x,  Increase major version number.  
-y,  Increase minor version number.  
-z,  Increase patch version number.  
-v,  Print program version.  
-h,  Print this help screen.  
-s,  Process simple version string.  
-a,  Append version string to a file name.  
-i,  Initialize version. 

## Example

Create a head file version.h with initial version value 0.1.0  
'''
semver -i0.1.0 version.h
'''

Increase the version value to 0.1.1  
'''
semver -z version.h
'''

Increase the version value to 0.2.0  
'''
semver -y version.h
'''

Increase the version value to 1.0.0  
'''
semver -x version.h
'''

Append version to file target.hex to target_1.0.0.hex  
'''
semver -atarget.hex version.h
'''



