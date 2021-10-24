/*
 * ===========================================================================
 *
 *       Filename:  ec_save.c
 *
 *    Description: Saves the public key in a file
 *
 *        Version:  1.0
 *        Created:  10/24/2021 05:53:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:  Holberton
 *
 * ===========================================================================
 */

#include "hblk_crypto.h"
#define PRIV_NAME "/key.pem"
#define PUB_NAME "/key_pub.pem"
/**
 * ec_save - saves the priv and pub key in the selected folder
 * @key: Crypt structure
 * @folder: Path to save
 *
 * Return: 1 if successful 0 if error happened
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char *priv_path = NULL, *pub_path = NULL;
	FILE *priv_fd, *pub_fd;

	if (!key || !folder)
		return (0);

	mkdir(folder, 0777);
	priv_path = calloc(strlen(folder) + strlen(PRIV_NAME) + 1, 1);
	if (!priv_path)
		return (0);
	pub_path = calloc(strlen(folder) + strlen(PUB_NAME) + 1, 1);
	if (!pub_path)
	{
		free(priv_path);
		return (0);
	}
	strcpy(priv_path, folder);
	strcat(priv_path, PRIV_NAME);
	priv_fd = fopen(priv_path, "w+");
	if (!PEM_write_ECPrivateKey(priv_fd, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(priv_fd);
		free(priv_path);
		return (0);
	}
	fclose(priv_fd);
	free(priv_path);
	strcpy(pub_path, folder);
	strcat(pub_path, PUB_NAME);
	pub_fd = fopen(pub_path, "w+");
	if (!PEM_write_EC_PUBKEY(pub_fd, key))
	{
		fclose(pub_fd);
		free(pub_path);
		return (0);
	}
	fclose(pub_fd);
	free(pub_path);
	return (1);
}
