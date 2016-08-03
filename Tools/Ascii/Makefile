#---------
#
# CppUTest Examples Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = Ascii_u
CPPUTEST_HOME = ../../COTS/CppUTest/2.4

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = GCC

# This line is overriding the default new macros.  This is helpful
# when using std library includes like <list> and other containers
# so that memory leak detection does not conflict with stl.
# CPPUTEST_MEMLEAK_DETECTOR_NEW_MACRO_FILE = -include ApplicationLib/ExamplesNewOverrides.h
SRC_DIRS = \
	Src/

TEST_SRC_DIRS = \
	Test/

INCLUDE_DIRS =\
  Test\
  Src\
  $(CPPUTEST_HOME)/include\
  

include $(CPPUTEST_HOME)/build/MakefileWorker.mk


