# Objetivo predeterminado (no se necesita especificarlo al invocar `make`).
all: principal

# Objetivos que no son archivos.
.PHONY: all clean

# Directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

MODULOS = Categoria ControladorPartidas ControladorUsuarios ControladorVideojuegos Desarrollador DtCategoria DtDesarrollador DtEstadistica DtFechaHora DtJugador DtPartida DtPartidaIndividual DtPartidaMultijugador DtSuscripcionVideojuego DtUsuario DtVideojuegoAMostrar DtVideojuegoAPublicar DtVideojuegoAPuntuar Fabrica FechaHoraSistema Genero Individual Jugador Multijugador Otros Partida PartidaInfo Plataforma Puntua RegistroSuscripcion Suscripcion Temporal TotalHorasJugadas TotalJugadores Usuario Videojuego Vitalicia

# lista de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.cpp)
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal

LIB=../p4-lab.a 

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -Werror -I$(HDIR) -DNDEBUG -g
# se debe remover o agregar la directiva -DNDEBUG para que las llamadas a 
# `assert' tengan  efecto o no.

$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# cada .o depende de su .cpp
# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/%.o: $(CPPDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

$(LIB):$(ODIR)/$(PRINCIPAL).o $(OS)
	ar -qc $@ $^

biblioteca:$(LIB)

# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE): $(ODIR)/$(PRINCIPAL).o $(OS)
	$(CC) $(CCFLAGS) $^ -o $@

# borra binarios
clean:
	rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS) $(LIB)
