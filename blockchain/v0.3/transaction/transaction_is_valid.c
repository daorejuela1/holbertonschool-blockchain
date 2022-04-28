#include "transaction.h"

/**
 * find_unspent_output - finds a utxo in a utxo list
 * @all_unspent: list of all utxos
 * @in: transaction input used to find utxo
 * Return: pointer to utxo if found, else NULL
 **/
unspent_tx_out_t *find_unspent_output(llist_t *all_unspent, tx_in_t *in)
{
	int i, size, v1, v2;
	unspent_tx_out_t *tmp_unspent;

	for (i = 0, size = llist_size(all_unspent); i < size; i++)
	{
		tmp_unspent = llist_get_node_at(all_unspent, i);
		v1 = !memcmp(tmp_unspent->out.hash,
				in->tx_out_hash, sizeof(tmp_unspent->out.hash));
		v2 = !memcmp(tmp_unspent->block_hash,
				in->block_hash, sizeof(tmp_unspent->block_hash));
		if (v1 && v2)
			return (tmp_unspent);
	}
	return (NULL);
}

/**
 * transaction_is_valid - checks whether a transaction is valid
 * @transaction: transaction to verify
 * @all_unspent: list of all unspent transaction outputs to date
 * Return: 1 if transaction is valid | 0 otherwise
 **/
int transaction_is_valid(transaction_t *transaction, llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	int i, size;
	uint32_t unspent_total = 0, total = 0;
	unspent_tx_out_t *tmp_unspent = NULL;
	tx_in_t *tmp_input = NULL;

	if (!transaction)
		return (0);
	if (!transaction_hash(transaction, hash_buf))
		return (0);
	if (memcmp(hash_buf, transaction->id, sizeof(hash_buf)))
		return (0);
	for (i = 0, size = llist_size(transaction->inputs); i < size; i++)
	{
		tmp_input = llist_get_node_at(transaction->inputs, i);
		tmp_unspent = find_unspent_output(all_unspent, tmp_input);
		if (!tmp_unspent ||
			!ec_verify(ec_from_pub(tmp_unspent->out.pub),
				transaction->id, SHA256_DIGEST_LENGTH, &tmp_input->sig)
		)
			return (0);
		unspent_total += tmp_unspent->out.amount;
	}

	for (i = 0, size = llist_size(transaction->outputs); i < size; i++)
		total += ((tx_out_t *)(llist_get_node_at(transaction->outputs, i)))->amount;

	return (total == unspent_total);
}
