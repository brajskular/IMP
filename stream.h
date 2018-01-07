#ifndef IMP_H
#define IMP_H

#include "cache.h"

// L1 Stream
// #define L1_PF_DEBUG_PRINT
#ifdef L1_PF_DEBUG_PRINT
#define L1_PF_DEBUG(x) x
#else
#define L1_PF_DEBUG(x)
#endif

#define STREAM_PREFETCH_DEGREE 6
#define STREAM_THRESHOLD 3
#define NUM_ST_ENTRIES 16
#define PREF_ERROR 0xFFFF


class STREAM_TABLE {
public:
	uint64_t pc,
			 addr,
			 stream_hit_cnt,
			 lru;

	STREAM_TABLE() {
		pc = 0;
		addr = 0;
		stream_hit_cnt = 0;
		lru = 0;
	};
};


extern STREAM_TABLE L1_ST[NUM_CPUS][NUM_ST_ENTRIES];

int L1_ST_update(uint32_t cpu, uint64_t ip, uint64_t addr);


STREAM_TABLE L1_ST[NUM_CPUS][NUM_ST_ENTRIES];

#endif

