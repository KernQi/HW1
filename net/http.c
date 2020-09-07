/*
 * Copyright (c) 2017, Hammurabi Mendes.
 * Licence: BSD 2-clause
 */
#include <stdio.h>
#include <string.h>

int header_complete(char *buffer, int buffer_length) {
	buffer[buffer_length] = '\0';

	if(strstr(buffer, "\r\n\r\n")) {
		return 1;
	}

	return 0;
}

int get_filename(char *buffer, int buffer_length, char *filename, int filename_length, char *protocol, int protocol_length) {
	if(!buffer || !filename || !protocol) {
		fprintf(stderr, "Please provide non-null buffer/filename/protocol\n");

		return -1;
	}

	if(buffer_length < 128 || filename_length < 128 || protocol_length < 16) {
		fprintf(stderr, "Please provide buffer/filename strings with sizes >= 128 and a protocol string with size >= 16\n");

		return -1;
	}

	buffer[buffer_length] = '\0';

	char *temporary;

	// Filename

	temporary = strcasestr(buffer, "GET /");

	if(!temporary) {
		strcpy(filename, "");
		strcpy(protocol, "");

		return -1;
	}

	char *filename_found;

	temporary += 5;
	filename_found = temporary;

	temporary = index(filename_found, ' ');

	if(!temporary) {
		strcpy(filename, "");
		strcpy(protocol, "");

		return -1;
	}

	*temporary = '\0';

	if(strcmp(filename_found, "") == 0) {
		strncpy(filename, "index.html", filename_length);
	}
	else {
		strncpy(filename, filename_found, filename_length);
	}

	// Protocol

	char *protocol_found;

	temporary++;
	protocol_found = temporary;

	temporary = index(protocol_found, '\r');

	if(!temporary) {
		strcpy(filename, "");
		strcpy(protocol, "");

		return -1;
	}

	*temporary = '\0';

	strncpy(protocol, protocol_found, protocol_length);

	return 0;
}

void get_200(char *buffer, char *filename, char *protocol, int filesize) {
	sprintf(buffer, "%s 200 OK\r\nFilename: %s\r\nContent-Length: %d\r\n\r\n", protocol, filename, filesize);
}

void get_403(char *buffer, char *filename, char *protocol) {
	sprintf(buffer, "%s 403 Forbidden\r\nFilename: %s\r\n\r\n<HTML><HEAD><TITLE>File cannot be opened</TITLE></HEAD><BODY>The file %s cannot be opened.</BODY></HTML>", protocol, filename, filename);
}

void get_404(char *buffer, char *filename, char *protocol) {
	sprintf(buffer, "%s 404 Not Found\r\nFilename: %s\r\n\r\n<HTML><HEAD><TITLE>File not found</TITLE></HEAD><BODY>The file %s was not found.</BODY></HTML>", protocol, filename, filename);
}
