#include "gol.h"

/**
 * struct cell_state_trans - a legal state transition of a cell
 * @old: initial state (e.g. DEAD or ALIVE)
 * @num_neigh: number of living neighbors
 * @new: expected state for the given cells next generation
 *
 * Expecting: (old -> num_neigh) -> new
 */
typedef struct cell_state_trans {
	cell_state_t old;
	int num_neigh;
	cell_state_t new;
} cell_state_trans_t;

#define __FIN_BIT 4
#define __FIN_STATE_TRANS_TABLE { DEAD, 1 << __FIN_BIT, DEAD }

/**
 * test_cell_state_table - expected result matrix for state transitions
 */
cell_state_trans_t test_cell_state_table[] = {
	{ DEAD, 0, DEAD},
	{ DEAD, 1, DEAD},
	{ DEAD, 2, DEAD},
	{ DEAD, 3, ALIVE},
	{ DEAD, 4, DEAD},
	{ DEAD, 5, DEAD},
	{ DEAD, 6, DEAD},
	{ DEAD, 7, DEAD},
	{ DEAD, 8, DEAD},

	{ ALIVE, 0, DEAD},
	{ ALIVE, 1, DEAD},
	{ ALIVE, 2, ALIVE},
	{ ALIVE, 3, ALIVE},
	{ ALIVE, 4, DEAD},
	{ ALIVE, 5, DEAD},
	{ ALIVE, 6, DEAD},
	{ ALIVE, 7, DEAD},
	{ ALIVE, 8, DEAD},

	__FIN_STATE_TRANS_TABLE,
};

/**
 * trans_is_last - check whether state transition is the last one
 * @trans: the cell state transition to check
 *
 * Return: 1 if there are no follow-up states to test, 0 otherwise.
 */
static int trans_is_last(cell_state_trans_t *trans)
{
	return GET_BIT((trans + 1)->num_neigh, __FIN_BIT);

}

static int test_expected_states(cell_state_trans_t *trans);

/**
 * func_fin - abort loop, return success
 * @trans: unused
 *
 * Return: Always 0
 */
static int func_fin(cell_state_trans_t *trans)
{
	return 0;
}

/**
 * func_err - abort loop, return error
 * @trans: unused
 *
 * Return: Always 1
 */
static int func_err(cell_state_trans_t *trans)
{
	return 1;
}

/**
 * func_ok - maybe test next state transition
 * @trans: state transition that was previously and successfully tested
 *
 * This function evaluates whether the given state transition was the last
 * one to test. If not advances to and checks the next transition in the
 * transition matrix.
 *
 * Return: 0 if all state transitions were successfully tested, 1 otherwise.
 */
static int func_ok(cell_state_trans_t *trans)
{
	long maybe_apply_fin_offset = func_fin - test_expected_states;

	maybe_apply_fin_offset *= trans_is_last(trans);
	return (*(test_expected_states + maybe_apply_fin_offset))(trans + 1);
}

/**
 * test_expected_states - test the pending variations for cell_next_state()
 * @trans: The current cell state transition to test
 *
 * Note: 'trans' needs to be a pointer in an array which ends with a
 * __FIN_STATE_TRANS_TABLE.
 *
 * Return: 0 on success, 1 otherwise.
 */
static int test_expected_states(cell_state_trans_t *trans)
{
	/* functions have addresses, addresses are numbers -
	   we can perform arithmetic operations with these! */
	long maybe_apply_err_offset = func_err - func_ok;


	cell_state_t res = cell_next_state(trans->num_neigh, trans->old);
	maybe_apply_err_offset *= (res & FLIP_BIT(trans->new)) | (FLIP_BIT(res) & trans->new);

	return (*(func_ok + maybe_apply_err_offset))(trans);
}

/**
 * test_cell_next_state - test the cell_next_state function
 *
 * Tests the given cell_next_state function for all the combinations
 * legal in a two dimensional Game-Of-Life. That is for all combinations
 * of initially dead and alive cells and 0 to 8 neighbors.
 *
 * Return: 0 on success, 1 otherwise.
 */
int test_cell_next_state()
{
	return test_expected_states(&test_cell_state_table[0]);
}
