CC = gcc
LDFLAGS =
EXEC = mt19937ar

# Répertoires source
SRC_DIR = .
DISPLAY_DIR = display
IMATH_DIR = imath
MT_DIR = mt
SIMULATION_DIR = simulation

# Fichiers sources
SRCS = $(wildcard $(SRC_DIR)/*.c)
DISPLAY_SRCS = $(wildcard $(DISPLAY_DIR)/*.c)
IMATH_SRCS = $(wildcard $(IMATH_DIR)/*.c)
MT_SRCS = $(wildcard $(MT_DIR)/*.c)
SIMULATION_SRCS = $(wildcard $(SIMULATION_DIR)/*.c)

# Fichiers objets
OBJS = $(SRCS:.c=.o)
DISPLAY_OBJS = $(DISPLAY_SRCS:.c=.o)
IMATH_OBJS = $(IMATH_SRCS:.c=.o)
MT_OBJS = $(MT_SRCS:.c=.o)
SIMULATION_OBJS = $(SIMULATION_SRCS:.c=.o)

# Dépendances
DEPS = $(OBJS:.o=.d)
DISPLAY_DEPS = $(DISPLAY_OBJS:.o=.d)
IMATH_DEPS = $(IMATH_OBJS:.o=.d)
MT_DEPS = $(MT_OBJS:.o=.d)
SIMULATION_DEPS = $(SIMULATION_OBJS:.o=.d)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS) $(DISPLAY_OBJS) $(IMATH_OBJS) $(MT_OBJS) $(SIMULATION_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lm

-include $(DEPS)
-include $(DISPLAY_DEPS)
-include $(IMATH_DEPS)
-include $(MT_DEPS)
-include $(SIMULATION_DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS) $(DISPLAY_OBJS) $(IMATH_OBJS) $(MT_OBJS) $(SIMULATION_OBJS) $(DEPS) $(DISPLAY_DEPS) $(IMATH_DEPS) $(MT_DEPS) $(SIMULATION_DEPS)
