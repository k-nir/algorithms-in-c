# 指定shell
SHELL = /bin/sh

# 源文件目录
srcdir = .

# 清除make默认识别的后缀(即清除默认的隐式rule)
.SUFFIXES:
# 明确定义本Makefile识别的后缀
.SUFFIXES: .c .o

# 对象文件列表
objects = 1-qfind.o \
          2-qunion.o \
		  3-w-qunion.o \
		  4-w-qunion-pc.o \
		  5-w-qunion-pc-h.o
# 源文件列表
sources = 
# 依赖文件列表
depends = 

# make的goal不是clean(即当前运行的不是make clean)时，\
include .d依赖文件
ifneq ($(MAKECMDGOALS), clean)
include $(depends)
endif
