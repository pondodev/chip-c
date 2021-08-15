executable_name = output

full: build run

fullclean: clean build run

fullmemleaktest: clean build memleaktest

build:
		gcc -o $(executable_name) *.c

run:
		./$(executable_name) trip8.ch8

clean:
		rm -f ./$(executable_name)

memleaktest:
		valgrind --tool=memcheck ./$(executable_name)
