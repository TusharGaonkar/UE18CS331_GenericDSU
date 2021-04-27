a.out: src/dsu.h src/dsu.cpp main.cpp
	@g++ -std=c++2a -pedantic -Wall -Wshadow -Wextra -o main main.cpp -g -D_GLIBCXX_DEBUG_PEDANTIC && rm -r main.dSYM && ./main && rm ./main