CFLAGS = -Wall

SRCS = logger.c
EXES = $(SRCS:.c:)

logger: $(EXES)
