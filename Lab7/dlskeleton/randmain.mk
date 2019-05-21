randmain : randmain.o randcpuid.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$$PWD $^ -o $@
randlibhw.so : randlibhw.c
	$(CC) $(CFLAGS) $< -fPIC -shared -o $@
randlibsw.so : randlibsw.c
	$(CC) $(CFLAGS) $< -fPIC -shared -o $@
