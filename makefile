
cc = gcc

src = $(notdir $(wildcard ./server/*.c))
hdr = $(wildcard ./server/headers/*.h)
obj = $(src:.c=.o)

compile = -g

vpath %.c server

kernel: $(obj) $(hdr)
	$(cc) $(compile) $(addprefix ./server/obj/, $(obj)) -o ./server/bin/$@.e

%.o: %.c
	$(cc) -c $(compile) $< -o ./server/obj/$@

clean-all: clean-obj clean-bin

clean-obj:
	rm -rf ./server/obj/*.o

clean-bin:
	rm -rf ./server/bin/*.e