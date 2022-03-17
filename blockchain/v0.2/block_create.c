/*
 *==========================================================================
 *
 *       Filename:  block_create.c
 *
 *    Description:  Creates a new block for a blockchain structure
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
 * block_create - creates a new block for a blockchain structure
 *
 * @prev: Previous block in the blockchain
 * @data: data to insert to the block
 * @data_len: data len
 *
 * Return: created block_t or NULL on failure
 */
block_t *block_create(block_t const *prev, int8_t const *data,
		uint32_t data_len)
{
	block_t *new_block = NULL;
	int max_data = 0;

	max_data = data_len > BLOCKCHAIN_DATA_MAX ? BLOCKCHAIN_DATA_MAX : data_len;
	new_block = calloc(1, sizeof(*new_block));
	if (!new_block)
		return (NULL);
	new_block->info.timestamp = (time(NULL));
	memcpy(&(new_block->data.buffer), data, max_data);
	new_block->data.len = max_data;
	new_block->info.index = prev->info.index + 1;
	memcpy(&(new_block->info.prev_hash), prev->hash, SHA256_DIGEST_LENGTH);

	return (new_block);
}
