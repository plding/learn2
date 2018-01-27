include ../Make.defines

PROGS = daytimetcpcli \
		daytimetcpsrv \
		daytimetcpcliv6

all: ${PROGS}

daytimetcpcli: daytimetcpcli.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli.o ${LIBS}

daytimetcpsrv: daytimetcpsrv.o
	${CC} ${CFLAGS} -o $@ daytimetcpsrv.o ${LIBS}

daytimetcpcliv6: daytimetcpcliv6.o
	${CC} ${CFLAGS} -o $@ daytimetcpcliv6.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
