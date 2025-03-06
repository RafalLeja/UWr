// Rafał Leja 06.03.2025

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv) {
		if (argc != 2) {
				printf("Usage: %s <hostname>\n", argv[0]);
				exit(1);
		}

		printf("Traceroute to %s\n", argv[1]);
		return 0;
}
