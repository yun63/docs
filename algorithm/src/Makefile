#############################################################################
#
# Generic Makefile for C/C++ Program
#
# Author:  yun63<thewardsthe@mail.com>
#
#############################################################################

include define.mk

ROOT=$(shell pwd)

## DEBUG开关选项
DEBUG	:= 1

## 头文件搜索路径 
INCPATH ?= -I. -I$(GTEST_DIR)/include -I../protobuf/include

## 源代码子目录
SRCDIRS := tinyxml utils 

## 生成目标目录
OBJ_DIR = object.dir

## 可执行程序目录
BIN = bin

## 测试代码目录
TEST_DIR = tests

## GTest测试框架目录
GTEST_DIR := ../3rd/gtest-1.7.0
GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h 
GTEST_SRCS_ := $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

## 可执行目标程序
TARGETS :=

## 可执行测试程序
TTEST := Test.unittest

CPPFLAGS += -isystem $(GTEST_DIR)/include

SOURCES := \
	$(foreach e, $(addprefix *, $(SRCEXTS)), $(wildcard $(e))) \
	$(foreach d, $(SRCDIRS), $(wildcard $(addprefix $(d)/*, $(SRCEXTS)))) 

TESTS_CXX := $(foreach e, $(addprefix *, $(SRCEXTS)), $(wildcard $(TEST_DIR)/$(e)))

ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -O2
endif

OBJECTS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

PROTO_INC := $(patsubst %.proto, %.pb.h,  $(wildcard pb/*.proto))
PROTO_CXX := $(patsubst %.proto, %.pb.cc, $(wildcard pb/*.proto))
PROTO_OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(PROTO_CXX))))

TESTS_OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(TESTS_CXX))))

#$(warning $(SOURCES))
#$(warning $(OBJECTS))

## 库文件
LIBS = -L/usr/local/lib \
	   -L../lib -lgtest_main -lgtest \
	   -L../protobuf/lib -lprotobuf \
	   -lpthread -lz -lm

.PHONY: clean 
.SUFFIXES:

all: $(TARGETS)

## 生成所有(.o)文件规则.
#----------------------------------------
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

$(OBJ_DIR)/%.o:%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

$(OBJ_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

$(OBJ_DIR)/%.o:%.cxx
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

%.o:%.c
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

%.o:%.cpp 
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

%.o:%.cc
	$(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c $< -o $@

%.pb.cc: %.proto
	../protobuf/bin/protoc -I=pb/ --cpp_out=pb/ $<

libcommon.a : $(PROTO_CXX) $(PROTO_OBJS) $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(PROTO_OBJS) $(OBJECTS)
	$(RANLIB) $@

libcommon.so : $(PROTO_OBJS) $(OBJECTS) | $(PROTO_CXX)
	$(LINK) -fPIC --shared $(PROTO_OBJS) $(OBJECTS) -o $@ $(INCPATH) $(LIBS)

$(TTEST): $(TESTS_OBJS) | libcommon.a
	$(LINK) -o $@ $^ $(LIBS) -L. -lcommon
	./$(TTEST)

#-------------------------------------
clean:
	-rm -f *~ core *.core
	-rm -rf $(OBJ_DIR) 
	-rm -f $(TARGETS)
	-rm -f $(TTEST)

install:
	-cp -f $(TARGETS) ../lib

#############################################################################
