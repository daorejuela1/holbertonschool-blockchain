/*
 *==========================================================================
 *
 *       Filename:  block_destroy.c
 *
 *    Description:  Destroy a block for a blockchain structure
 *
 *        Version:  1.0
 *        Created:  11/01/2021 09:11:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:  Holberton
 *
 *=========================================================================
 */
#include "blockchain.h"

/**
 * block_destroy - destroys a block for a blockchain structure
 *
 * @block: block in the blockchain to destroy
 *
 * Return: Nothing
 */
void block_destroy(block_t *block)
{
	if (!block)
		return;
	llist_destroy(block->transactions, 1, (node_dtor_t)transaction_destroy);
	free(block);
}
