objects =	fractal.o\
			fractal_generate.o\
			main.o\
			fractal_worker.o\
			fractal_delegator.o\
			fractal_widget.o\
			fractal_widget_ui.o\
			fractal_animator.o\
			animator_ui.o

tgt = fractal

fluid_code = fractal_widget_ui.cpp animator_ui.cpp

CC = g++
DEBUG = #-g
OPTIMIZE = -O3
PROFILE = #-pg
CFLAGS = ${DEBUG} -Wall ${PROFILE} ${OPTIMIZE} -I/usr/local/boost_1_37_0/
LDFLAGS = ${PROFILE} -L/usr/local/lib/ 
AS = as

LIBS = -lfltk -lboost_thread-gcc41-mt -lX11

all: ${tgt}

fl: ${fluid_code}

${tgt}: ${objects}
	${CC} ${CFLAGS} -o fractal ${objects} ${LDFLAGS} ${LIBS}

fractal_delegator.o: fractal_delegator.cpp
	${CC} ${CFLAGS} -c -o fractal_delegator.o fractal_delegator.cpp

fractal_worker.o: fractal_worker.cpp
	${CC} ${CFLAGS} -c -o fractal_worker.o fractal_worker.cpp

fractal.o: fractal.cpp
	${CC} ${CFLAGS} -c -o fractal.o fractal.cpp

fractal_generate.o: fractal_generate.s
	${CC} ${CFLAGS} -c -o fractal_generate.o fractal_generate.s

fractal_generate.s: fractal_generate.cpp
	${CC} ${CFLAGS} -S -o fractal_generate.s fractal_generate.cpp

fractal_widget.o: fractal_widget.cpp
	${CC} ${CFLAGS} -c -o fractal_widget.o fractal_widget.cpp

fractal_widget_ui.o: fractal_widget_ui.cpp
	${CC} ${CFLAGS} -c -o fractal_widget_ui.o fractal_widget_ui.cpp

animator_ui.o: animator_ui.cpp
	${CC} ${CFLAGS} -c -o animator_ui.o animator_ui.cpp

fractal_widget_ui.cpp: fractal_widget_ui.fl
	fluid -c fractal_widget_ui.fl

animator_ui.cpp: animator_ui.fl
	fluid -c animator_ui.fl

fractal_animator.o: fractal_animator.cpp
	${CC} ${CFLAGS} -c -o fractal_animator.o fractal_animator.cpp

#fractal_generate.o: fractal_generate.s
#	as -c fractal_generate.o fractal_generate.s

main.o: main.cpp
	${CC} ${CFLAGS} -c -o main.o main.cpp

.PHONY: clean
clean:
	-rm ${tgt} ${objects} fractal_generate.s

fclean:
	rm animator_ui.cpp animator_ui.hpp fractal_widget_ui.cpp fractal_widget_ui.hpp


