all: 401 402 404 410 416 421 423

401: 401.cpp
	g++ -o 401 401.cpp
402: 402.cpp
	g++ -o 402 402.cpp
404: 404.cpp
	g++ -o 404 404.cpp
410: 410.cpp
	g++ -o 410 410.cpp
416: 416.cpp
	g++ -o 416 416.cpp
421: 421.cpp
	g++ -o 421 421.cpp
423: 423.cpp
	g++ -o 423 423.cpp

clean:
	rm -rf 401 402 404 410 416 421 423

