/*
 * ===========================================================================
 *
 *       Filename:  ec_sign.c
 *
 *    Description: Signs a set of bytes
 *
 *        Version:  1.0
 *        Created:  10/30/2021 04:53:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:  Holberton
 *
 * ===========================================================================
 */
#include "hblk_crypto.h"

/**
 * ec_sign - signs a message with private key
 * @key: pointer to struct containing key pair
 * @msg: the message to sign
 * @msglen: length of message
 * @sig: address to store signature
 * Return: pointer to signed buffer or NULL
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t *sig)
{
	unsigned int len;

	if (!key || !msglen ||  !msg || !sig)
		return (NULL);
	len = sig->len;
	if (ECDSA_sign(0, msg, msglen, sig->sig, &len, (EC_KEY *)key) != 1)
		return (NULL);
	sig->len = len;
	return (sig->sig);
}

