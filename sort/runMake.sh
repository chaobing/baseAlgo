g++  -lgtest -lpthread -lgtest_main -I /usr/local/include/ -L /usr/local/lib/ \
	  -o  test.bin \
		BaseAlgo.cpp Test.cpp -std=c++11
