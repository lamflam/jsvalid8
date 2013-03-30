

INCLUDEV8 = -Idep/v8/include
LIBV8 = dep/v8/out/native/obj.target/tools/gyp/*.a

CC = g++
FLAGS = -lpthread

%:src/%.cpp 
	$(CC) $(INCLUDEV8) $< -o out/$@ $(LIBV8) $(FLAGS)

