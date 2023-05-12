.default: all

all: ppd

clean:
	rm -rf ppd *.o *.dSYM

ppd: Coin.o Node.o LinkedList.o ppd.o helper.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

run: ppd
	./ppd stock.dat coins.dat

test: ppd
	./ppd ./input/test1_copy_4/stock.dat ./input/test1_copy_4/coins.dat < ./input/test1_copy_4/input.txt > ./output/test/output.txt

testAll: ppd
	./ppd 
