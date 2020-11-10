main: a.cpp b.cpp c.cpp
	g++ -Wall -o a a.cpp -lzmq
	g++ -Wall -o b b.cpp -lzmq
	g++ -Wall -o c c.cpp -lzmq

clean:
	rm -rf ./a ./b ./c