/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct conf_data conf_data_t;

typedef enum
{
	NOT_FOUND_IN_CONF = 0,
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
	THEME_CONFIG = 11,
	ABOUT_CONFIG = 12,
	NUMBER_OF_TOKENS,
} conf_type_t;

conf_data_t *config_init(const char *config_file);
void config_free(conf_data_t *conf_data);
void *config_get_data(conf_type_t conf_type, conf_data_t *cf);

#ifdef __cplusplus
}
#endif

#endif
