#  D'apres le Makefile de :
#  	Auteur : Farès BELHADJ
#  	Email  : amsi@ai.univ-paris8.fr
#  	Date   : 29/01/2017

SHELL = /bin/sh
# définition des commandes utilisées
CC = gcc
RM = rm -f
# déclaration des options du compilateur
CFLAGS = -Wall -O3
CPPFLAGS = -I.
LDFLAGS = -lm

# définition des fichiers et dossiers
PROGNAME = som_iris_data
HEADERS =  tools.h data.h network.h free.h
SOURCES =  main.c tools.c data.c network.c free.c
OBJ = $(SOURCES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(PROGNAME) $(OBJ)
