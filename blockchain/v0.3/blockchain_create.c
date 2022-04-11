/*
 * =======================================================================
 *
 *       Filename:  blockchain_create.c
 *
 *    Description:  Creates the genesis block of a blockchain structure
 *
 *        Version:  1.0
 *        Created:  11/01/2021 08:30:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:  Holberton
 *
 * ===================================================================
 */

#include "blockchain.h"

/**
 * blockchain_create - Creates a new blockchain structure
 *
 * Return: The blockchain structure with the genesis block
 */
blockchain_t *blockchain_create(void)
{
	block_t *block = NULL;
	blockchain_t *blockchain = NULL;
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	block_t const _genesis = {
		{ /* info */
			0 /* index */,
			0, /* difficulty */
			1537578000, /* timestamp */
			0, /* nonce */
			{0} /* prev_hash */
		},
		{ /* data */
			"Holberton School", /* buffer */
			16 /* len */
		},
		"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"
			"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
			/* hash */
			/*c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803*/
	};
	block = calloc(1, sizeof(*block));
	blockchain = calloc(1, sizeof(*blockchain));
	if (!blockchain || !block || !list)
	{
		free(blockchain), free(block), llist_destroy(list, 1, NULL);
		return (NULL);
	}
	block->info.timestamp = _genesis.info.timestamp;
	memcpy(&(block->data.buffer), _genesis.data.buffer, _genesis.data.len);
	block->data.len = _genesis.data.len;
	memcpy(&(block->hash), _genesis.hash, SHA256_DIGEST_LENGTH);
	if (llist_add_node(list, block, ADD_NODE_FRONT))
	{
		free(blockchain), free(block), llist_destroy(list, 1, NULL);
		return (NULL);
	}
	blockchain->chain = list;
	return (blockchain);
}
