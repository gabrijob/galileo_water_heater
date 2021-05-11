TARGET=libproj.a
SRCS=water_level.c temperature.c pwm_control.c pputs.c pgets.c i2c_write_reg.c i2c_read_reg.c board_name.c
HEADERS=sensors.h pwm_control.h galileoio.h i2cutil.h jhdlcd.h

PREFIX?=$(HOME)

FLAGS=-O2 -Wall -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib
LIBS=-lgalileo -lm

CC=$(CROSS_COMPILE)gcc
CCAR=$(CROSS_COMPILE)ar
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)
CCARFLAGS=-crvs

all: $(TARGET)


$(TARGET): $(SRCS:.c=.o)
	$(CCAR) $(CCARFLAGS) $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)

install:
	install -d $(PREFIX)/lib$(BITS) $(PREFIX)/include
	install -m 644 $(TARGET) $(PREFIX)/lib$(BITS)
	(cd ../include ; install -m 644 $(HEADERS) $(PREFIX)/include)

	
uninstall:
	rm -rf $(PREFIX)/lib$(BITS)/$(TARGET)
	(cd $(PREFIX)/include ; rm -rf $(HEADERS))



