####################
## Premier Makefile, merci de ne pas rigoler :-)
####################

CC=g++
CFLAGS= -pipe -Wall -O2
LDFLAGS=-L/usr/local/lib -I"common" -lpthread
RM=/bin/rm

####################

DIST=build
COMMON=common/util.cpp common/cause.cpp common/socket.cpp common/grid.cpp
SRC_SERVER=server/server.cpp $(COMMON) 
SRC_CLIENT=client/client.cpp $(COMMON) 

OBJ_SERVER=$(subst .cpp,.o,$(SRC_SERVER))
OBJ_CLIENT=$(subst .cpp,.o,$(SRC_CLIENT))

####################

all: server client

server: $(OBJ_SERVER)
	@mkdir -p $(DIST)
	$(CC) -o $(DIST)/$@ $(LDFLAGS) $^

client: $(OBJ_CLIENT)
	@mkdir -p $(DIST)
	$(CC) -o $(DIST)/$@ $(LDFLAGS) $^

%.c: %.o
	$(CC) -c $(CFLAGS) $<

clean:
	$(RM) -fr $(DIST)
	$(RM) -f $(OBJ_SERVER)
	$(RM) -f $(OBJ_CLIENT)