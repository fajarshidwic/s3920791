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
	./ppd ./output/final/stock.dat ./output/final/coins.dat < ./input/resetcointest/input.txt > ./output/final/output.txt 

purchasetest: ppd
	./ppd ./input/purchasetest/stock.dat ./input/purchasetest/coins.dat < ./input/purchasetest/purchasetest1/input.txt > ./output/purchasetest/output1.txt
	./ppd ./input/purchasetest/stock.dat ./input/purchasetest/coins.dat < ./input/purchasetest/purchasetest2/input.txt > ./output/purchasetest/output2.txt
	./ppd ./input/purchasetest/stock.dat ./input/purchasetest/coins.dat < ./input/purchasetest/purchasetest3/input.txt > ./output/purchasetest/output3.txt
	./ppd ./input/purchasetest/stock.dat ./input/purchasetest/coins.dat < ./input/purchasetest/purchasetest4/input.txt > ./output/purchasetest/output4.txt
	./ppd ./input/purchasetest/stock.dat ./input/purchasetest/coins.dat < ./input/purchasetest/purchasetest5/input.txt > ./output/purchasetest/output5.txt

testAll: ppd
	cat ./input/printcoinstest/input.txt ./input/printstockstest/input.txt ./input/resetcointest/input.txt ./input/resetstocktest/input.txt | ./ppd ./output/final/stock.dat ./output/final/coins.dat > ./output/final/output.txt