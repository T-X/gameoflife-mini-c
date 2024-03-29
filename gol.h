
/* FLIP_BIT turns a 0 into a 1 and a 1 into a 0
 *
 * On ARMv6 with gcc 4.6.3-14+rpi1 a '~' (bitwise complement)
 * with disabled optimizations (-O0) results in
 * 'cmp' and 'bne' instructions -
 * Too similar to 'if', let's avoid them :)
 */
#define FLIP_BIT(x) ((x + 1) & 0x1)

/* GET_BIT fetches a specific bit, starting
 * with bitnum == 0
 */
#define GET_BIT(x, bitnum) ((x >> bitnum) & 0x1)


typedef enum cell_state {
	DEAD = 0,	// don't change this value
	ALIVE,
} cell_state_t;


cell_state_t cell_next_state(int num_neigh, cell_state_t state);
