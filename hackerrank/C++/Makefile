CPP_FILES := $(wildcard *.cpp)
EXE_FILES := $(notdir $(CPP_FILES:.cpp=.x))
DBG_FILES := $(notdir $(CPP_FILES:.cpp=.dbgx))

all: ${EXE_FILES} ${DBG_FILES}

exe: ${EXE_FILES}

dbg: ${DBG_FILES}

clean:
	rm -f ${EXE_FILES} ${DBG_FILES}

%.x:%.cpp
	g++ -std=c++11 $< -o $@

%.dbgx:%.cpp
	g++ -std=c++11 -ggdb -DDBG $< -o $@
