#ifndef IMP_H
#define IMP_H

#include "cache.h"

// L1 IMP
#define L1_PF_DEBUG_PRINT
#ifdef L1_PF_DEBUG_PRINT
#define L1_PF_DEBUG(x) x
#else
#define L1_PF_DEBUG(x)
#endif

#define IMP_MAX_INDIRECT_LEVELS 2
#define IMP_MAX_INDIRECT_WAYS 2
#define INDIRECT_PREFETCH_DEGREE 4
#define IMP_MAX_PREFETCH_DISTANCE 16
#define IMP_PREFETCH_DEGREE 3
#define IMP_PREFETCH_THRESHOLD 2
#define STREAM_PREFETCH_DEGREE 6
#define STREAM_THRESHOLD 3
#define NUM_BASE_ADDR_TRACKED 4
#define NUM_COEFFICIENTS 4
#define NUM_IPD_ENTRIES 4
#define NUM_PT_ENTRIES 16
#define DELTA_SIZE 8
#define BLOCKS_PER_PAGE 64
#define PREF_ERROR 0xFFFF

class INDIRECT_PATTERN_DETECTOR {
public:
	uint64_t pid,
			 idx1,
			 idx2,
			 base_addr_arr[NUM_COEFFICIENTS][NUM_BASE_ADDR_TRACKED];

	INDIRECT_PATTERN_DETECTOR() {
		pid = 0;
		idx1 = 0;
		idx2 = 0;
		for(int i=0; i<NUM_BASE_ADDR_TRACKED; i++)
			for(int j=0; j<NUM_COEFFICIENTS; j++)
				base_addr_arr[j][i] = 0;
	};
};

class PREFETCH_TABLE {
public:
	uint64_t pc,
			 addr,
			 stream_hit_cnt,
			 enable,
			 index,
			 base_addr,
			 shift,
			 indirect_hit_cnt,
			 ind_type,
			 next_way,
			 next_level,
			 prev,
			 lru,
			 exp_addr_found,
			 pref_distance;

	PREFETCH_TABLE() {
		pc = 0;
		addr = 0;
		stream_hit_cnt = 0;
		enable = 0;
		index = 0;
		base_addr = 0;
		shift = 0;
		indirect_hit_cnt = 0;
		ind_type = 0;
		next_way = 0;
		next_level = 0;
		prev = 0;
		lru = 0;
		exp_addr_found = 0;
		pref_distance = 1;
	};
};



extern INDIRECT_PATTERN_DETECTOR L1_IPD[NUM_CPUS][NUM_IPD_ENTRIES];
extern PREFETCH_TABLE L1_PT[NUM_CPUS][NUM_PT_ENTRIES];
extern int SHIFT_ARR[NUM_COEFFICIENTS] = {-2,3,-4,-3};

void L1_IPD_update(uint32_t cpu, uint64_t addr, int cache_hit, uint64_t ip, uint64_t data);
void L1_IT_update(uint32_t cpu, uint64_t pid, uint64_t index, uint64_t base_addr, uint64_t shift);
int L1_ST_update(uint32_t cpu, uint64_t ip, uint64_t addr);
void allocate_next_level(uint32_t cpu, int entry);


INDIRECT_PATTERN_DETECTOR L1_IPD[NUM_CPUS][NUM_IPD_ENTRIES];
PREFETCH_TABLE L1_PT[NUM_CPUS][NUM_PT_ENTRIES];

#endif

