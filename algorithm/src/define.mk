#############################################################################
#
# Generic defination for Makefile
#
# Author:  yun63<thewardsthe@mail.com> 
#
#############################################################################

## 源文件类型
SRCEXTS := .c .cc .cpp .cxx

## 指定C/C++编译器
CC := gcc
CXX := g++
LINK := g++
AR := ar
RANLIB := ranlib

## 编译器选项
CXXFLAGS := --std=c++11 -Wall -fPIC
MYCFLAGS := -DDEBUG
ARFLAGS := rcs

