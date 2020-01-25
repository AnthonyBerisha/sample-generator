.PHONY: clean

SRCS		=	srcs/main.c
OBJS		=	$(SRCS: .c=.o)
CC			=	gcc
RM			=	rm -f
EXEC		=	sample-generator

all:	${EXEC}

test:	all
		./sample-generator trip.wav

${EXEC}:${OBJS}
		@echo "Building EXEC"
		${CC} -o $@ $^ -lsndfile

%.o: %.c
		@echo "Creating objects"
		${CC} -o $@ -c 

clean:
		${RM} *.o

rem:
		${RM} output_*
	