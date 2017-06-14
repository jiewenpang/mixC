CPP = g++ -std=c++11
CPPFLAG = -g  -pthread

BIN = ./
TARGET= tprodconsu tjni tlibevent tlog server client tpoll test tboost 
INCLS = -I../inc -I/home/pjw/jdk1.7.0_67/include -I/home/pjw/jdk1.7.0_67/include/linux
LIBS  = -L/home/pjw/bin/log4cplus/lib -llog4cplus 

all: $(TARGET) 
server : server.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS)
	rm $^
	@echo "[1;33m$@[m"

client: client.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS)
	rm $^
	@echo "[1;33m$@[m"

tpoll: tpoll.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS)
	rm $^
	@echo "[1;33m$@[m"

test: test.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS)
	rm $^
	@echo "[1;33m$@[m"

tboost: tboost.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS) -L/home/pjw/bin/boost/lib -lboost_serialization
	rm $^
	@echo "[1;33m$@[m"

tlog: tlog.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS) 
	rm $^
	@echo "[1;33m$@[m"

tlibevent: tlibevent.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS) -L/home/pjw/bin/libevent/lib -levent
	rm $^
	@echo "[1;33m$@[m"

tjni: tjni.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS) -L/home/pjw/jdk1.7.0_67/jre/lib/amd64/server -ljvm
	rm $^
	@echo "[1;33m$@[m"

tprodconsu: tprodconsu.o
	$(CPP) $(CPPFLAG) -o $(BIN)/$@ $^ $(LIBS) 
	rm $^
	@echo "[1;33m$@[m"

clean:
	rm -f *.o core $(TARGET) 
	@echo "[1;33mclean done[m"
    

.SUFFIXES: .o .cpp 
.cpp.o:
	$(CPP) $(CPPFLAG) $(INCLS)  -c $<

