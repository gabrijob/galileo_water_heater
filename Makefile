DIRS=lib src
PREFIX?=$(HOME)

all:
	for i in $(DIRS); do $(MAKE) -C $$i; done

clean:
	for i in $(DIRS); do $(MAKE) -C $$i clean; done
	rm -rf *~ *.bak
	
distclean:
	for i in $(DIRS); do $(MAKE) -C $$i distclean; done
	rm -rf *~ *.bak

install:
	for i in $(DIRS); do $(MAKE) -C $$i PREFIX=$(PREFIX) install; done

uninstall:
	for i in $(DIRS); do $(MAKE) -C $$i PREFIX=$(PREFIX) uninstall; done

