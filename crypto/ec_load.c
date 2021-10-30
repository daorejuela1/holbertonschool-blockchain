/*
 * ========================================================================
 *
 *       Filename:  ec_load.c
 *
 *    Description: Loads an encrypted file for the required folder
 *
 *        Version:  1.0
 *        Created:  10/30/2021 03:45:47 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:  Holberton
 *
 * =======================================================================
 */

#include "hblk_crypto.h"

EC_KEY *ec_load(char const *folder)
{
	char *priv_path = NULL, *pub_path = NULL;
	FILE *priv_fd = NULL, *pub_fd = NULL;
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	priv_path = calloc(strlen(folder) + strlen(PRIV_NAME) + 1, 1);
	if (!priv_path)
		return (NULL);
	pub_path = calloc(strlen(folder) + strlen(PUB_NAME) + 1, 1);
	if (!pub_path)
	{
		free(priv_path);
		return (NULL);
	}
	strcpy(priv_path, folder), strcat(priv_path, PRIV_NAME);
	priv_fd = fopen(priv_path, "r");
	strcpy(pub_path, folder), strcat(pub_path, PUB_NAME);
	pub_fd = fopen(pub_path, "r");
	free(priv_path), free(pub_path);
	if (!priv_fd || !pub_fd)
		return (NULL);
	if (!PEM_read_EC_PUBKEY(pub_fd, &key, NULL, NULL))
	{
		fclose(pub_fd);
		return (NULL);
	}
	fclose(pub_fd);
	if (!PEM_read_ECPrivateKey(priv_fd, &key, NULL, NULL))
	{
		fclose(priv_fd);
		return (NULL);
	}
	fclose(priv_fd);
	return (key);
}
