all:
	gcc -Wall -Wextra -Wpedantic std=c11 main.c musicdb.h musicdb.c musicdb_report

check:
	gcc -Wall -Wextra -Wpedantic std=c11 -fsanitize=address, undefined main.c musicdb.c -o musicdb_report
	./musicdb_report data 4358
	