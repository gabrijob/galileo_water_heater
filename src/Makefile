TARGET=main
SRCS=$(TARGET).c

# Using hardware trigger
FLAGS=-Wall -g -MMD

# Using software trigger
#FLAGS=-Wall -g -MMD -DTRIG_SYSFS

INCLUDE=-I. -I$(HOME)/include
LIBDIR=-L$(HOME)/lib
LIBS=-lproj -lgalileo

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
