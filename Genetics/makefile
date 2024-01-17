GCC = gcc 
CFLAGS = -Wall -lm -g # -Wall for warnings, -lm for math library, -g for debugging
OBJECTS = main.o DistanceFunctions.o

main: $(OBJECTS)
	@echo "Compiling main"
	$(GCC) $(OBJECTS) -o main $(CFLAGS) 

main.o: main.c 
	@echo "Compiling main.o"
	$(GCC) -c main.c  

DistanceFunctions.o: DistanceFunctions.c
	@echo "Compiling DistanceFunctions.o"
	$(GCC) -c DistanceFunctions.c 

clean:
	@echo "Cleaning"
	rm -f $(OBJECTS) main

run: main
	@echo "Running"
	./main