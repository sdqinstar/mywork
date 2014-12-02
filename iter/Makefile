#Linux  操作系统相关的编译命令定义

#C++ 编译命令
CXX=g++
#C 编译命令
CCC=g++

#C++ 编译选项
CXX_OPTIONS=-Wall -w -fPIC -D_THREAD_SAFE -g
#C 编译选项
CCC_OPTIONS=-Wall -w -fPIC -D_THREAD_SAFE

#C++ 连接选项
CXX_LD_OPTIONS= -Wall -fPIC -D_THREAD_SAFE -g
#C 连接选项
CCC_LD_OPTIONS=-Wall -fPIC -D_THREAD_SAFE

#静态库命令
AR=ar
#静态库选项
AR_OPTIONS=-rv

#
SO=g++
SO_OPTIONS=-shared -o


USR_INCLUDE= -I./ \
              -I/usr/local/include/gtest/ \

 
USR_FLAGS=  -D_DEBUG

ALL_LIBS= -lgtest -lpthread

#此处理开发人员不需要修改
#.SUFFIXES: .cpp .c
#.cpp.o:
#	$(CXX)  $(CXX_OPTIONS) $(MODE_FLAG) -o $@ -c $< $(ALL_FLAGS) $(ALL_INCLUDES) $(USR_FLAGS) $(USR_INCLUDE)
#.c.o:
#	$(CCC)  $(CCC_OPTIONS) $(MODE_FLAG) -o $@ -c $< $(ALL_FLAGS) $(ALL_INCLUDES) $(USR_FLAGS) $(USR_INCLUDE)


SRCS = iterator.o 


#下面生成两种库只是为了给出一个例子，实际 zxfunc 只需要生成静态库
STATIC_LIBRARY = 

SHARE_LIBRARY =  

OUTPUT =  iter


#all 定义段
all:$(STATIC_LIBRARY) $(SHARE_LIBRARY) $(OUTPUT)

$(STATIC_LIBRARY): $(SRCS)
	$(AR) $(AR_OPTIONS) $@ $(SRCS)

$(SHARE_LIBRARY): $(SRCS)
	$(SO) $(SO_OPTIONS) $@ $(SRCS)

$(OUTPUT): $(SRCS)
	$(CXX) $(CXX_LD_OPTIONS) -o $@ $(SRCS) $(ALL_LIBS) 

#下面的 FUNC_LIB  FUNC_INC 定义在产品的 MakeCommon 文件中
install:


#CLEAN定义段
clean:
	rm -f *.o core* *.so *.a

