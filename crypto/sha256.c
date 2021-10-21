/*
 * =====================================================================
 *
 *       Filename:  sha256.c
 *
 *    Description: Computes the hash of a sequence of bytes
 *
 *        Version:  1.0
 *        Created:  10/21/2021 06:08:24 AM
 *       Revision:  None
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization: Holberton
 *
 * =======================================================================
 */
#include "hblk_crypto.h"

/**
 * sha256 - computes the hash 256 of a sequence of bytes
 * @s: String to compute the hash for
 * @len: Len of s
 * @digest: Array to return the hash data
 *
 * Return: Pointer to digest
 */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	const EVP_MD *md;

	if (!s || !len)
		return (NULL);

	md = EVP_sha256();
	strncpy((char *)digest, (char *)md, len);
	return (digest);
}
