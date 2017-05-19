OBJECTS=devmem2

all:$(OBJECTS)

PKG_NAME=devmem2

$(OBJECTS): devmem2
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	@-rm *.o $(OBJECTS)

