CC := gcc

PACKAGES := \
	drmollineda.so \
	proc_osliani.so

%.so: proc_%.c
	$(CC) -shared -fpic -o $@ $^

all: ${PACKAGES}

clean:
	rm -rf *.o *.so
