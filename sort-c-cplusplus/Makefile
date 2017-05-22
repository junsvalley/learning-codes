CC          = gcc
TARGET      = sort
SRC         = $(wildcard *.c)
CFLAGS      = -g -O0 -fPIC -I"." -D__EXCHANGE_VAL__

.PHONY: all
all:clean $(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) $<

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $@ -lm

clean:
	@rm -rf $(TARGET) core*
