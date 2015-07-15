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
COMPONENT_NAME = semver
CPPUTEST_HOME = ../../COTS/CppUTest/v2.4a

CPPUTEST_USE_EXTENSIONS = N
CPP_PLATFORM = GCC

# This line is overriding the default new macros.  This is helpful
# when using std library includes like <list> and other containers
# so that memory leak detection does not conflict with stl.
# CPPUTEST_MEMLEAK_DETECTOR_NEW_MACRO_FILE = -include ApplicationLib/ExamplesNewOverrides.h
SRC_DIRS = ../src 
TEST_SRC_DIRS = ./
INCLUDE_DIRS = ../src  $(CPPUTEST_HOME)/include  

#include 
include $(CPPUTEST_HOME)/build/MakefileWorker.mk


