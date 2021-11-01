/*
 *==========================================================================
 *
 *       Filename:  block_hash.c
 *
 *    Description:  Construct the block hash
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
 * block_hash - Computes the block hash
 *
 * @block: block in the blockchain to destroy
 * @hash_buf: buffer to store the new hash
 * Return: pointer to the hash_buf
 */
uint8_t *block_hash(block_t const *block,
		uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len =  sizeof(block->info) + block->data.len;

	if (!block || !hash_buf)
		return (NULL);
	return (sha256((int8_t const *)block, len, hash_buf));
}
