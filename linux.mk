TARGET 		 = libcolors
RM 			 = rm
RMFLAGS 	 =  -f -v
EXTENSION 	 = elf
DEBUG_LINUX = -fsanitize=address

include general.mk