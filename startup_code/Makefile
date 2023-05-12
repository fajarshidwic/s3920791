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
	./ppd ./input/printcoinstest/stock.dat ./input/printcoinstest/coins.dat < ./input/printcoinstest/input.txt > ./output/test/output.txt

testAll: ppd
	./ppd ./output/final/stock.dat ./output/final/coins.dat < ./input/printcoinstest/input.txt < ./input/printstockstest/input.txt > ./output/final/output.txt

