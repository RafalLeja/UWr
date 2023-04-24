```C
struct node {				
  char id[2];				
  int (*hashfn)(char *);		
  short flags;			
  union {				
    struct {			
      short n_key;		
      int n_data[2];		
      unsigned char n_type;	
    } s;
    unsigned l_value[2];		
  } u;
};
```

| fragment                  | offset | align | size |
|---------------------------|--------|-------|------|
|```char id[2]```           |     0  |  1    | 2B   |
|padding                    |       -|      -|    6B|
|```int (*hashfn)(char *)```|       8|      8|    8B|
|```short flags```          |      16|      2|    2B|
|padding                    |       -|      -|    6B|
|```union```                |      24|      -|   16B| 
|```struct```               |      24|      -|   16B|
|```short n_key```          |      24|      2|    2B|
|padding                    |       -|      -|    2B|
|```int n_data[2]```        |      28|      4|    8B|
|```unsigned char n_type``` |      36|      1|    1B|
|padding                    |       -|      -|    3B|
|```unsigned l_value[2]```  |      24|      4|    8B|
|całość                     |       -|      -|   40B|

```C
struct node {
    union {
        struct {
            int n_data[2];
            short n_key;
            unsigned char n_type;
        } s;
        unsigned l_value[2];
    } u;
    int (*hashfn)(char *);
    short flags;
    char id[2];
};
// 32B
```