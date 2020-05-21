########################################
#~ définitions
########################################

# nom de l'executable
BIN=naive #boyer_moore


# liste des fichiers sources 
SRCS0=naive.cpp
#SRCS1=boyer_moore.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

%.o: %.cpp
	g++ -Wall -Iinclude -c $< -o $@

naive: $(SRCS0:%.c=%.o)
	g++ -Wall -lpthread -o $@ $+

#boyer_moore: $(SRCS1:%.c=%.o)
#	g++ -Wall -lpthread -o $@ $+

clean:
	rm -f $(BIN) *.o *~
