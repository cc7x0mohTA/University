# Bartosz Bednarczyk (273 479)

Flags = -std=c++11 -Werror -Wreturn-type -pedantic -pedantic-errors -Wundef -Wall -W
CPP = g++

traceroute : Makefile traceroute.o receiver.o utils.o sender.o mypacket.o
	$(CPP) $(Flags) -o traceroute traceroute.o receiver.o utils.o sender.o mypacket.o

traceroute.o : Makefile traceroute.cpp receiver.o utils.o sender.o mypacket.o
	$(CPP) -c $(Flags) traceroute.cpp -o  traceroute.o

receiver.o : Makefile receiver.cpp receiver.h utils.o sender.o mypacket.o
	$(CPP) -c $(Flags) receiver.cpp -o receiver.o

sender.o : Makefile sender.cpp sender.h utils.o mypacket.o
	$(CPP) -c $(Flags) sender.cpp -o sender.o

mypacket.o : Makefile mypacket.cpp mypacket.h utils.o
	$(CPP) -c $(Flags) mypacket.cpp -o mypacket.o	

utils.o : Makefile utils.cpp utils.h 
	$(CPP) -c $(Flags) utils.cpp -o utils.o	

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp
