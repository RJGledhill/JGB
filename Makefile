CC=gcc
CFLAGS=-I. -I/usr/include/python2.7/ -I/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include/
DEPS = DataVector.h RPN.h stack.h operators.h pythonInterface.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

JGB: DataVector.o RPN.o stack.o operators.o pythonInterface.o
	$(CC) -shared -lpython2.7 -o JGB.so DataVector.o RPN.o stack.o operators.o pythonInterface.o -I. -I/usr/include/python2.7/




