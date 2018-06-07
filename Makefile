##
## EPITECH PROJECT, 2018
## gpu-intro
## File description:
## Makefile
##

CC	=	g++

SRCDIR	=	src
OBJDIR	=	build
OUTDIR	=	bin

FILES		=	main				\
			GLError				\
			shaders/compile

SORTEDFILES	=	$(sort $(FILES))
SRCFILES	=	$(SORTEDFILES:%=$(SRCDIR)/%.c)
OBJFILES	=	$(SORTEDFILES:%=$(OBJDIR)/%.o)

FOLDERS		=	shaders

SORTEDFOLDERS	=	$(sort $(FOLDERS))
OBJFOLDERS	=	$(SORTEDFOLDERS:%=$(SRCDIR)/%)
OBJFOLDERS	=	$(SORTEDFOLDERS:%=$(OBJDIR)/%)

CMNFLAGS	=	-W -Wall -Wextra -O3 -DGLM_ENABLE_EXPERIMENTAL
CFLAGS		=	$(CMNFLAGS) -Iinclude
LDFLAGS		=	$(CMNFLAGS) -lglfw -lGLEW -lGL

REDDARK 	=       \033[31;2m
RED     	=       \033[31;1m
GREEN   	=       \033[32;1m
YEL     	=       \033[33;1m
BLUE    	=       \033[34;1m
PINK    	=       \033[35;1m
CYAN    	=       \033[36;1m
RES     	=       \033[0m

NAME		=	$(OUTDIR)/demo

all:		.SILENT

.SILENT:	$(NAME)

$(NAME):	$(OBJFOLDERS) $(OBJDIR) $(OUTDIR) $(OBJFILES)
		@echo -e "[$(RED)LINKING$(RES)] $(YEL)$(OBJDIR)/*.o$(RES) $(BLUE)=>$(RES) $(YEL)$(NAME)$(RES)"
		@$(CC) $(LDFLAGS) -o $(NAME) $(OBJFILES)

$(OBJDIR):
	@echo -e "[$(RED)MKDIR$(RES)] $(YEL)$@$(RES)"
	@mkdir -p $(OBJDIR)

$(OUTDIR):
	@echo -e "[$(RED)MKDIR$(RES)] $(YEL)$@$(RES)"
	@mkdir -p $(OUTDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	@echo -e "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%:	$(SRCDIR)/%
	@echo -e "[$(RED)MKDIR$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@mkdir -p $@
