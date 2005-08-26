default: all

all:
	doxygen doc/Doxyfile

clean:
	\rm -fr doc/html
