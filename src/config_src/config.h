#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdint.h>

typedef struct conf_data conf_data_t;

typedef enum
{
	ROOT = 1,
	HTTP_PORT = 2,
	ADDRESS = 3,
	DEFAULT_FILE = 4,
	DEBUG_LEVEL = 5,
	CHUNCK_ENCODING = 6,
	W3C_FILE = 7,
	HTTPS_PORT = 8,
	SSL_KEY = 9,
	SSL_CRT = 10,
	NUMBER_OF_TOKENS,
} conf_type_t;

conf_data_t *config_init(char *config_file);
void config_free(conf_data_t *conf_data);
void *config_get_data(conf_type_t conf_type, conf_data_t *cf);

#endif
