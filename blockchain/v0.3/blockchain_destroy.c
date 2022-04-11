/*
 *==========================================================================
 *
 *       Filename:  block_destroy.c
 *
 *    Description:  destroys a blockchain structure
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
 * blockchain_destroy - destroys a blockchain
 *
 * @blockchain: blockchain to destroy
 *
 * Return: Nothing
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;
	llist_destroy(blockchain->chain, 1, (void (*)(llist_node_t))block_destroy);
	llist_destroy(blockchain->unspent, 1, free);
	free(blockchain);
}
