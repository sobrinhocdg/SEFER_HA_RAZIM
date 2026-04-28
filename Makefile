CC=gcc
CXX=g++
GO=go
CFLAGS=-O3 -fvisibility=hidden -Wall
CXXFLAGS=-O3 -fvisibility=hidden -std=c++11
LDFLAGS=-s

all: clean reaper phantom oracle shield cipher

reaper:
	@$(CC) $(CFLAGS) $(LDFLAGS) QELIPPOT_DMA/physical_reaper.c -o reaper
phantom:
	@$(CC) $(CFLAGS) $(LDFLAGS) DAAT_MEMFD/phantom_dropper.c -o phantom
oracle:
	@cd SEPHIROT_CHAIN && $(GO) build -ldflags="-s -w" -o ../oracle ethereum_oracle.go
shield:
	@$(CC) $(CFLAGS) $(LDFLAGS) AIN_SOPH_SHIELD/anti_debugger.c -o shield
cipher:
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) METATRON_CIPHER/obfuscated_core.cpp -o cipher

clean:
	@rm -f reaper phantom oracle shield cipher
