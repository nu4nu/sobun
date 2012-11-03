CC = gcc
CFLAGS = -ggdb -Wall -Wextra -O2
CPPFLAGS = -I/home/nu/work/gmp5 -I/usr/local/include
LDFLAGS = /home/nu/work/gmp5/libgmp.a -L/usr/local/lib

BINS = cn
TARGETLIB = libcn.a
OBJS = cn_set_str.o cn_out_str.o cn_add_factor.o cn_eval.o cn_poly.o cn_algebraic.o aur_factor.o aur_poly.o pow_list.o
HDRS = cn.h

all: $(BINS)

$(TARGETLIB): $(OBJS)
	rm -f $(TARGETLIB)
	ar r $(TARGETLIB) $(OBJS)
	ranlib $(TARGETLIB)

.c.o: $(HDRS)
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS)

cn: cn_main.o $(TARGETLIB) $(HDRS)
	$(CC) $(CFLAGS) -o $@ cn_main.o $(TARGETLIB) $(LDFLAGS)

clean:
	rm -f $(BINS) cn_main.o $(TARGETLIB) $(OBJS)

.PHONY: all clean

