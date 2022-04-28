#include "blockchain.h"

/**
 * block_transactions_are_valid - checks if a block's transactions are valid
 * @block: pointer to block
 * @all_unspent: list of utxo's
 * Return: 1 if transactions are valid, 0 otherwise
 **/
static int block_transactions_are_valid(block_t const *block,
		llist_t *all_unspent)
{
	int i, size = llist_size(block->transactions);
	transaction_t *tx;

	if (!size || !block)
		return (0);

	for (i = 0; i < size; i++)
	{
		tx = llist_get_node_at(block->transactions, i);
		if (i)
		{
			if (!transaction_is_valid(tx, all_unspent))
				return (0);
		}
		else
		{
			if (!coinbase_is_valid(tx, block->info.index))
				return (0);
		}
	}

	return (1);
}

/**
 * validate_tx - validates each tx
 * @node: tx
 * @idx: index of node
 * @arg: visitor
 * Return: 0 if continue else 1
 */
int validate_tx(llist_node_t node, unsigned int idx, void *arg)
{
	transaction_t *tx = node;
	validation_vistor_t *visitor = arg;

	if (!idx)
	{
		if (!coinbase_is_valid(tx, visitor->block_index))
			visitor->valid = 0;
	}
	else if (!transaction_is_valid(tx, visitor->all_unspent))
	{
		dprintf(2, "validate_tx: invalid idx %u\n", idx);
		visitor->valid = 0;
	}
	return (0);
}

/**
 * block_is_valid - checks if this and previous block are valid
 * @block: pointer to this block in the chain
 * @prev_block: pointer to previous block in the chain or NULL
 * @all_unspent: list of all unspent txs
 * Return: 0 if valid else 1 if invalid
 */
int block_is_valid(block_t const *block, block_t const *prev_block,
	llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	block_t const _genesis = GENESIS_BLOCK;

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
		return (memcmp(block, &_genesis, sizeof(_genesis)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);
	if (llist_size(block->transactions) < 1)
		return (1);
	if (!block_transactions_are_valid(block, all_unspent))
		return (1);
	return (0);
}
