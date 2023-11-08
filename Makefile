# Definizione dei nomi dei file sorgente da compilare DEVO RIAGGIUNGERE comanda.cpp
SRC_FILES := main.cpp user.cpp tavolo.cpp prodotto.cpp pietanza_griglie.cpp pietanza_cucina.cpp bevanda.cpp menu.cpp comanda.cpp jsonFileManager.cpp pathManager.cpp

# Nome dell'eseguibile
TARGET := main

# Comando di compilazione
CXX := g++
CXXFLAGS := -std=c++11 -Wall -g -ljsoncpp

# Regola per compilare il programma
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES)

# Regola per la pulizia (rimuove l'eseguibile)
clean:
	rm -f $(TARGET)
