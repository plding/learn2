include ../Make.defines

PROGS = daytimetcpcli

all: ${PROGS}

daytimetcpcli: daytimetcpcli.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
