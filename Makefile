# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hepple <hepple@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 12:14:51 by hepple            #+#    #+#              #
#    Updated: 2023/01/16 12:19:02 by hepple           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************* #
#   V A R I A B L E S   #
# ********************* #

NAME		:= containers

CXX			:= c++
CXXFLAGS	:= -std=c++98 -Wall -Wextra -Werror# -fsanitize=address

LDFLAGS		:= 

DEPFLAGS	 = -MMD -MP -MF $(DDIR)/$*.d

VPATH		:= ./ src/

SRCS		:= main.cpp

ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRCS:%.cpp=%.o))

DDIR		:= dep
DEPS		:= $(addprefix $(DDIR)/, $(SRCS:%.cpp=%.d))

# ********************* #
#       R U L E S       #
# ********************* #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@ 

$(ODIR)/%.o: %.cpp $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(DDIR):
	mkdir -p $(DDIR)

clean:
	$(RM) -r $(ODIR) $(DDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)
