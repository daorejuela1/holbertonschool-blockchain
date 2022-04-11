#include "transaction.h"

/**
 * tx_out_create - creates a new transaction output structure
 * @amount: the transaction amount
 * @pub: public key of receiver
 * Return: pointer to new structure or NULL
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *trx = calloc(1, sizeof(*trx));

	if (!trx)
		return (NULL);
	trx->amount = amount;
	memcpy(trx->pub, pub, sizeof(trx->pub));
	if (!sha256((int8_t const *)trx, sizeof(trx->amount) + sizeof(trx->pub), trx->hash))
    {
        free(trx);
        return (NULL);
    }
	return (trx);
}
