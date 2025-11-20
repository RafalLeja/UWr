
INC	:= -I$(CUDA_HOME)/include -I. -I../headers
LIB	:= -L$(CUDA_HOME)/lib64 -lcudart

# NVCCFLAGS	:= -lineinfo -arch=native -ptx --ptxas-options=-v --use_fast_math
NVCCFLAGS	:= -lineinfo -arch=native --ptxas-options=-v --use_fast_math

all:	prac1a prac1b prac1c hello addmat

prac1a:	prac1a.cu Makefile
	nvcc prac1a.cu -o prac1a $(INC) $(NVCCFLAGS) $(LIB)

prac1b:	prac1b.cu Makefile
	nvcc prac1b.cu -o prac1b $(INC) $(NVCCFLAGS) $(LIB)

prac1c:	prac1c.cu Makefile
	nvcc prac1c.cu -o prac1c $(INC) $(NVCCFLAGS) $(LIB)

hello:	hello.cu Makefile
	nvcc hello.cu -o hello $(INC) $(NVCCFLAGS) $(LIB)

addmat:	addmat.cu Makefile
	nvcc addmat.cu -o addmat $(INC) $(NVCCFLAGS) $(LIB)

clean:
	rm -f prac1a prac1b prac1c hello addmat
