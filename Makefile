CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = cc3k
OBJECTS = main.o game.o floor.o item.o gold.o hppotion.o dragonhoard.o temppotion.o nullpotion.o decorator.o atkpotion.o defpotion.o player.o shade.o drow.o vampire.o troll.o goblin.o enemy.o human.o dwarf.o elf.o orc.o merchant.o dragon.o halfling.o shop.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
