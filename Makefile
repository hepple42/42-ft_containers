# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hepple <hepple@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 12:14:51 by hepple            #+#    #+#              #
#    Updated: 2023/02/22 18:39:36 by hepple           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************* #
#   V A R I A B L E S   #
# ********************* #

NAME		:= ft_containers   

FT			:= ft
STD			:= std
RBT			:= rb_tree

CXX			:= c++
CXXFLAGS	:= -std=c++98 -Wall -Wextra -Werror# -fsanitize=address

LDFLAGS		:= 

DEPFLAGS_FT	 = -MT $@ -MMD -MP -MF $(DDIR_FT)/$*.d
DEPFLAGS_STD = -MT $@ -MMD -MP -MF $(DDIR_STD)/$*.d
DEPFLAGS_RBT = -MT $@ -MMD -MP -MF $(DDIR_RBT)/$*.d

VPATH		:= ./ src/

SRCS		:= test_containers.cpp
SRCS_RBT	:= test_rb_tree.cpp

ODIR		:= obj
ODIR_FT		:= $(ODIR)/$(FT)
OBJS_FT		:= $(addprefix $(ODIR_FT)/, $(SRCS:%.cpp=%.o))
ODIR_STD	:= $(ODIR)/$(STD)
OBJS_STD	:= $(addprefix $(ODIR_STD)/, $(SRCS:%.cpp=%.o))
ODIR_RBT	:= $(ODIR)/$(RBT)
OBJS_RBT	:= $(addprefix $(ODIR_RBT)/, $(SRCS_RBT:%.cpp=%.o))

DDIR		:= dep
DDIR_FT		:= $(DDIR)/$(FT)
DEPS_FT		:= $(addprefix $(DDIR_FT)/, $(SRCS:%.cpp=%.d))
DDIR_STD	:= $(DDIR)/$(STD)
DEPS_STD	:= $(addprefix $(DDIR_STD)/, $(SRCS:%.cpp=%.d))
DDIR_RBT	:= $(DDIR)/$(RBT)
DEPS_RBT	:= $(addprefix $(DDIR_RBT)/, $(SRCS_RBT:%.cpp=%.d))

# ********************* #
#       R U L E S       #
# ********************* #

.PHONY: all clean fclean re

all: $(FT) $(STD)

$(NAME): all

$(FT): $(OBJS_FT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS_FT) -o $@

$(STD): $(OBJS_STD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS_STD) -o $@

$(RBT): $(OBJS_RBT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS_RBT) -o $@

$(ODIR_FT)/%.o: %.cpp $(DDIR_FT)/%.d | $(ODIR_FT) $(DDIR_FT)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS_FT) -c $< -o $@ -D FT

$(ODIR_STD)/%.o: %.cpp $(DDIR_STD)/%.d | $(ODIR_STD) $(DDIR_STD)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS_STD) -c $< -o $@ -D STD

$(ODIR_RBT)/%.o: %.cpp $(DDIR_RBT)/%.d | $(ODIR_RBT) $(DDIR_RBT)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS_RBT) -c $< -o $@

$(ODIR_FT):
	mkdir -p $(ODIR_FT)

$(ODIR_STD):
	mkdir -p $(ODIR_STD)

$(ODIR_RBT):
	mkdir -p $(ODIR_RBT)

$(DDIR_FT):
	mkdir -p $(DDIR_FT)

$(DDIR_STD):
	mkdir -p $(DDIR_STD)

$(DDIR_RBT):
	mkdir -p $(DDIR_RBT)

clean:
	$(RM) -r $(ODIR) $(DDIR)

fclean: clean
	$(RM) $(FT) $(STD) $(RBT)

re: fclean all

$(DEPS_FT):
-include $(DEPS_FT)

$(DEPS_STD):
-include $(DEPS_STD)

$(DEPS_RBT):
-include $(DEPS_RBT)
