LDFLAGS+= -lsqlite3
ifneq ('y${NAS_LIB_PATH}','y')
  LDFLAGS += -O2
endif
all: test

test: main.c
	gcc -o exe main.c ${LDFLAGS} 
