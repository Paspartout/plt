include config.mk

SRC    = plt.c
OBJ    = ${SRC:.c=.o}

all: options plt

options:
	@echo plt build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

plt: ${OBJ}
	@echo LD $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

pbm: plt
	./plt > /tmp/o.pbm

clean:
	@echo cleaning
	@rm -f plt ${OBJ} ${LIBOBJ} plt-${VERSION}.tar.gz
	@rm -f *.pbm

dist: clean
	@echo creating dist tarball
	@mkdir -p plt-${VERSION}
	@cp -R LICENSE Makefile config.mk ${SRC} plt-${VERSION}
	@tar -cf plt-${VERSION}.tar plt-${VERSION}
	@gzip plt-${VERSION}.tar
	@rm -rf plt-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f plt ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/plt

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/plt

.PHONY: all options clean dist install uninstall
