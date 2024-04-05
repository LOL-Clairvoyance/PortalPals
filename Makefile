ifeq ($(OS),Windows_NT)
	NAME = PortalPals.exe
else
	NAME = PortalPals
endif

SRC = src

all: $(NAME)

init:
	mkdir build

$(NAME):
	odin build $(SRC) -out:build/$(NAME) -debug

clean:
	rm build/$(NAME)

re: clean all
