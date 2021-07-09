#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"

//#define DEBUG_ON 
#define ADDRESS_LENGTH 64//代表64位地址

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;//代表内存地址

/* Type: Cache line
   LRU is a counter used to implement LRU replacement policy  */
typedef struct cache_line {
    char valid;
    mem_addr_t tag;
    unsigned long long int lru;
} cache_line_t;

typedef cache_line_t* cache_set_t;//将每行串联在一起，形成一组？
typedef cache_set_t* cache_t;//将每组串联在一起，形成cache?

//cache_line_t代表行 cache_set_t代表组 cache_t代表cache

/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char* trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;//时间戳，用来记录当前行的上一次使用是在什么时间，通过比较大小来判断替换哪个

/* The cache we are simulating */
cache_t cache;  //定义了初始的全局变量cache 后面可以直接用 typedef cache_set_t* cache_t typedef cache_line_t* cache_set_t
mem_addr_t set_index_mask;

/* 
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 * also computes the set_index_mask
 */
void initCache()//初始化cache,为cache分配空间
{
	//cache t cache  
	//typedef cache_set_t* cache_t 
	//typedef cache_line_t* cache_set_t
	cache = malloc(S*sizeof(cache_set_t));//先分配S个指针，这些指针用来指向每一组
	for(int i = 0; i < S ;i++){
		cache[i] = malloc(E*sizeof(cache_line_t));
		//申请出每组的空间，空间大小为行数E*行的大小，让之前申请的每个指针指向每一组
		for(int j = 0 ; j < E ; j++){
			cache[i][j].valid = '0';
            cache[i][j].tag = 0;
            cache[i][j].lru = 0;
		}//对每行中的内容进行初始化
	}
	
}


/* 
 * freeCache - free allocated memory
 */
void freeCache()
{
    //如果要释放cache占据的内存，可以先把每行占据的释放掉
    for (int i = 0; i < S; i++) {
        free(cache[i]);//这里是将每组占据的空间释放了
    }
    //还要释放掉最开始申请的指向每组的那S个指针的空间
    free(cache);
}


/* 
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr)
{
    //怎么取？？？
    //首先应该获取组索引和标记
    //对于字地址，t位作为标记，s位作为组索引,b位作为块索引
    int t = 64 - s - b;//这里的t位表示标记，64位地址
    unsigned long long int zu_index = (addr << t) >> (b + t);//获取组索引
    unsigned long long int tag = addr >> (s + b);//获取标记
    
    for (int i = 0; i < E; i++) {
        if (cache[zu_index][i].tag == tag && cache[zu_index][i].valid == '1') {
            //如果该行有匹配的标记而且行有效(valid = 1),则命中
            hit_count++;
            lru_counter++;
            cache[zu_index][i].lru = lru_counter;
            return;
        }
        
    }
    //不命中的情况:1、有空行的话直接用空行
    for (int i = 0; i < E; i++) {
        if (cache[zu_index][i].valid == '0') {
            cache[zu_index][i].valid = '1';
            cache[zu_index][i].tag = tag;
            lru_counter++;
            cache[zu_index][i].lru = lru_counter;
            miss_count++;
            return;
        }
    }

    miss_count++;
    eviction_count++;
    //2、没空行的话需要替换当前组里lru最小的那个，说明它已经很久没有被操作过了
    int min_lru_index = 0;
    unsigned long long int min_lru = cache[zu_index][0].lru;
    for (int i = 1; i < E; i++) {
        if (cache[zu_index][i].lru < min_lru) {
            min_lru = cache[zu_index][i].lru;
            min_lru_index = i;
        }//如果遇到更小的lru
    }
    //到这里就找到了用最小lru的行的下标，为min_lru_index，只要替换它即可
    cache[zu_index][min_lru_index].tag = tag;
    lru_counter++;
    cache[zu_index][min_lru_index].lru = lru_counter;
    return;
    
}


/*
 * replayTrace - replays the given trace file against the cache 
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t addr=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");

    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while( fgets(buf, 1000, trace_fp) != NULL) {
        if(buf[1]=='S' || buf[1]=='L' || buf[1]=='M') {
            sscanf(buf+3, "%llx,%u", &addr, &len);
      
            if(verbosity)
                printf("%c %llx,%u ", buf[1], addr, len);

            accessData(addr);

            /* If the instruction is R/W then access again */
            if(buf[1]=='M')
                accessData(addr);
            
            if (verbosity)
                printf("\n");
        }
    }

    fclose(trace_fp);
}

/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine 
 */
int main(int argc, char* argv[])
{
    char c;

    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    /* Compute S, E and B from command line args */
    S = 1 << s;
    B = 1 << b;
 
    /* Initialize cache */
    initCache();

#ifdef DEBUG_ON
    printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
    printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif
 
    replayTrace(trace_file);

    /* Free allocated memory */
    freeCache();

    /* Output the hit and miss statistics for the autograder */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

