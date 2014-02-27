JSON_C_DIR=/usr/local
CFLAGS += -I$(JSON_C_DIR)/include/json-c -g -O2
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

all: test test_arr

test: main.c
	gcc -o test_json-c main.c ${CFLAGS} ${LDFLAGS} 

test_arr: arr.c
	gcc -o qarr arr.c ${CFLAGS} ${LDFLAGS} 
