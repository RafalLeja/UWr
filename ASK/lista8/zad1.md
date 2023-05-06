```C
extern int printf(const char *, ...);   //ref printf ext
extern long buf[];                      //ref buf ext
 
long *bufp0 = &buf[0];                  //def bufp0 .data global, ref buf
static double sum = 0.0;                //def sum .text local

static void incr() {                    //def incr .text local
  static int count = 0;                 //def count .bss local
  count++;                              //ref count
  sum += 3.14;                          //ref sum
  printf("sum = %f\n", sum);            //ref print, sum
}

void swap(int i) {                      //def swap .text global
  incr();                               //ref incr
  long temp = *bufp0;                   //def temp .bss local, ref bufp0
  *bufp0 = buf[i];                      //ref bufp0, buf
  buf[i] = temp;                        //ref buf, temp
}
```