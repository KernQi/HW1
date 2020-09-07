PROGRAM = webserver
OBJECTS = main.o clients_common.o server_fork.o

webserver-clean: clean libwildcat webserver

libwildcat:
	(cd net; make libwildcat)

webserver: $(OBJECTS)
	clang -g -o $(PROGRAM) $(OBJECTS) -I. -Inet -Lnet -lWildcatNetworking

%.o: %.c
	clang -g -c -o $@ -I. -Inet $<

clean:
	rm -f *.o webserver
