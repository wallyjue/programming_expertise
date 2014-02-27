JSON_C_DIR=/usr/local
CFLAGS += -I$(JSON_C_DIR)/include/
LDFLAGS+= -L$(JSON_C_DIR)/lib -loauth

all: test

test: main.c
	gcc -o test_oauth main.c ${CFLAGS} ${LDFLAGS} 
