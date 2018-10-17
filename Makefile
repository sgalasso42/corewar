NAME = Corewar

all	: $(NAME)

assm :
	make -C assembleur/

virtual : assm
	make -C vm/

$(NAME)	: virtual
	cp assembleur/asm .
	cp vm/corewar .

clean	: 
	make clean -C vm/
	make clean -C assembleur/

re	: fclean $(NAME)

fclean	: clean
	make fclean -C vm/
	make fclean -C assembleur/
	rm -f corewar
	rm -f asm
