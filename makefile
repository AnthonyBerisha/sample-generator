.PHONY: clean

SRCS		=	$(wildcard srcs/*.c)
INC_PATHS	=	/usr/include/x86_64-linux-gnu/
LDFLAGS		=	-lavformat -lavutil
LD_PATH		=	-L/usr/lib/x86_64-linux-gnu/
INC			=	-I${INC_PATHS}libavformat -I${INC_PATHS}libavutil -I/includes/
OBJS		=	$(SRCS: .c=.o)
CC			=	gcc
RM			=	rm -f
EXEC		=	sample-generator

all:	${EXEC}

${EXEC}:${OBJS}
		@echo "Building EXEC"
		${CC} -o $@ $^ ${INC} ${LDFLAGS} ${LD_PATH}

%.o: %.c
		@echo "Creating objects"
		${CC} -o $@ -c 

clean:
		${RM} *.o
	