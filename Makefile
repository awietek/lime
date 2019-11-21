arch = flatiron_linux

include options.mk
include sources.mk

objects = $(subst .cpp,.o,$(sources))
depends = $(subst .cpp,.d,$(sources))
depflags = -MT $@ -MMD -MP -MF $*.d

testobjects = $(subst .cpp,.o,$(testsources))
testdepends = $(subst .cpp,.d,$(testsources))

.PHONY: all 
all:  $(objects) lib

test:  $(objects) $(testobjects) lib 
	$(cc) $(ccopt) $(ccarch) $(objects) $(testobjects) $(includes) $(libraries) -o test/tests 

$(depends):
include $(depends)

$(testdepends):
include $(testdepends)

lib: $(objects)
	ar rcs lib/liblime.a $(objects)

.PHONY: clean
clean:
	$(rm) -r $(objects) $(depends) 
	$(rm) -r $(testobjects) $(testdepends) 

.PHONY: rebuild
rebuild: clean all lib


%.o: %.cpp %.d
%.o: %.cpp 
	$(cc) $(ccopt) $(ccarch) $(depflags) -c $< -o $@ $(includes)
