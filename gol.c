/**
 * Game of Life - with extra challenges!
 * 
 * The following concepts are dissallowed:
 * - No 'if', 'else', 'elseif', 'switch' etc.
 * - No 'while', 'for', 'foreach' etc.
 * - No '&&', '||', '!'
 * - No guards
 * - No 'goto'
 * - No external API
 *
 * Goal: Proving that C still is turing complete :)
 */

#include "gol.h"
#include "gol_test.h"

/**
 * cell_next_state - determine whether a cell dies or gets born
 * @num_neigh: number of living neighbors the provided (dead or alive) cell has
 * @state: initial state of the cell to check (e.g. DEAD or ALIVE)
 *
 * This function applies the Game-Of-Life rules to a given cell and
 * its according numeber of neighbors and calculates its new state:
 * 
 * - Given dead cell: Gets born if 3 living neighbors
 * - Given alive cell: Dies if less than 2 or more than 3 neighbors
 *
 * Return: The new state of a cell (e.g. DEAD or ALIVE)
 */
cell_state_t cell_next_state(int num_neigh, cell_state_t state)
{
	return	(GET_BIT(num_neigh, 0) | state) &
		GET_BIT(num_neigh, 1) &
		FLIP_BIT(GET_BIT(num_neigh, 2)) &
		FLIP_BIT(GET_BIT(num_neigh, 3));
}

int main()
{
	return test_cell_next_state();
}
