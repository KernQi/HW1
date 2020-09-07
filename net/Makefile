libwildcat: http.o networking.o
	clang -fPIC -shared -o libWildcatNetworking.so networking.o http.o

http.o: http.c
	clang -c -fPIC http.c -D_GNU_SOURCE

networking.o: networking.c
	clang -c -fPIC networking.c

clean:
	rm *.o *.so