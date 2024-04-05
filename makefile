all:client server test
client:client.cpp
	g++ -o client client.cpp
server:server.cpp
	g++ -o server server.cpp
test:test.cpp
	g++ -o test test.cpp
clean:
	rm -f client server test
