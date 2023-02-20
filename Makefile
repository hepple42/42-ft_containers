# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hepple <hepple@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 12:14:51 by hepple            #+#    #+#              #
#    Updated: 2023/02/20 16:06:46 by hepple           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************* #
#   V A R I A B L E S   #
# ********************* #

FT			:= test_ft
STD			:= test_std

CXX			:= c++
CXXFLAGS	:= -std=c++98 -Wall -Wextra -Werror# -fsanitize=address

LDFLAGS		:= 

DEPFLAGS_FT	 = -MT $@ -MMD -MP -MF $(DDIR_FT)/$*.d
DEPFLAGS_STD = -MT $@ -MMD -MP -MF $(DDIR_STD)/$*.d

VPATH		:= ./ src/

SRCS		:= test_containers.cpp

ODIR_FT		:= obj_ft
OBJS_FT		:= $(addprefix $(ODIR_FT)/, $(SRCS:%.cpp=%.o))
ODIR_STD	:= obj_std
OBJS_STD	:= $(addprefix $(ODIR_STD)/, $(SRCS:%.cpp=%.o))

DDIR_FT		:= dep_ft
DEPS_FT		:= $(addprefix $(DDIR_FT)/, $(SRCS:%.cpp=%.d))
DDIR_STD	:= dep_std
DEPS_STD	:= $(addprefix $(DDIR_STD)/, $(SRCS:%.cpp=%.d))

# ********************* #
#       R U L E S       #
# ********************* #

.PHONY: all clean fclean re

all: $(FT) $(STD)


$(FT): $(OBJS_FT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS_FT) -o $@

$(STD): $(OBJS_STD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS_STD) -o $@


$(ODIR_FT)/%.o: %.cpp $(DDIR_FT)/%.d | $(ODIR_FT) $(DDIR_FT)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@ -D FT

$(ODIR_STD)/%.o: %.cpp $(DDIR_STD)/%.d | $(ODIR_STD) $(DDIR_STD)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@ -D STD


$(ODIR_FT):
	mkdir -p $(ODIR_FT)

$(ODIR_STD):
	mkdir -p $(ODIR_STD)


$(DDIR_FT):
	mkdir -p $(DDIR_FT)

$(DDIR_STD):
	mkdir -p $(DDIR_STD)


clean:
	$(RM) -r $(ODIR_FT) $(DDIR_FT) $(ODIR_STD) $(DDIR_STD)


fclean: clean
	$(RM) $(NAME_FR) $(NAME_STD)


re: fclean all


$(DEPS_FT):
-include $(DEPS_FT)

$(DEPS_STD):
-include $(DEPS_STD)
