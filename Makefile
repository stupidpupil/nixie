test: build/catch_tests
	./build/catch_tests

build/catch_main.o: test/catch/*
	g++ -std=c++11 test/catch/catch_main.cpp -c -o build/catch_main.o

build/mock_arduino.o: test/mock/Arduino*
	g++ -std=c++11 -I test/mock test/mock/Arduino.cpp -c -o build/mock_arduino.o

build/mock_wire.o: test/mock/Wire*
	g++ -std=c++11 -I test/mock test/mock/Wire.cpp -c -o build/mock_wire.o

build/mock_serial.o: test/mock/Serial*
	g++ -std=c++11 -I test/mock test/mock/Serial.cpp -c -o build/mock_serial.o

build/mock_string.o: test/mock/MockString*
	g++ -std=c++11 -I test/mock test/mock/MockString.cpp -c -o build/mock_string.o

build/catch_tests: build/catch_main.o build/mock_arduino.o build/mock_wire.o build/mock_serial.o build/mock_string.o test/* *.cpp *.h
	g++ -std=c++11 -I test/mock \
		build/catch_main.o build/mock_arduino.o build/mock_wire.o build/mock_serial.o build/mock_string.o \
		test/dim_strategy_breathe_tests.cpp dim_strategy_breathe.cpp \
		test/smart_nixie_tests.cpp smart_nixie.cpp \
		-o build/catch_tests

clean:
	rm build/*