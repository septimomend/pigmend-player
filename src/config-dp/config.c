/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "config.h"
//#include "debug_log.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_HTTP_PORT 80
#define DEFAULT_HTTPS_PORT 443
#define DEFAULT_PATH PRO_FILE_PWD
#define DEFAULT_FILENAME "index.html"
#define DEFAULT_W3C_FILE "w3c.log"
#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_SSL_KEY	"ssl_cert_key/my_private_key"
#define DEFAULT_SSL_CRT "ssl_cert_key/my_cert_req"
#define EQUAL_SIGN	"="

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

struct conf_data
{
	char root_path[PATH_MAX];
	char default_file[NAME_MAX];
	char w3c_file[NAME_MAX];
	char address[INET6_ADDRSTRLEN];
	uint16_t http_port;
	uint16_t https_port;
	int chunk_encoding;
	char ssl_key[PATH_MAX];
	char ssl_crt[PATH_MAX];
	char theme_config[PATH_MAX];
	char about_config[PATH_MAX];
    char animations_config[PATH_MAX];
	int tokens_checker[NUMBER_OF_TOKENS];
};

static char *sDBXML;

static char *conf_str_token[NUMBER_OF_TOKENS] =
{
	[ROOT] = "ROOT",
	[HTTP_PORT] = "HTTP_PORT",
	[HTTPS_PORT] = "HTTPS_PORT",
	[ADDRESS] = "ADDRESS",
	[DEFAULT_FILE] = "DEFAULT_FILE",
	[DEBUG_LEVEL] = "DEBUG_LEVEL",
	[CHUNCK_ENCODING] = "CHUNCK_ENCODING",
	[W3C_FILE] = "W3C_FILE",
	[SSL_KEY] = "SSL_KEY",
	[SSL_CRT] = "SSL_CRT",
	[THEME_CONFIG] = "THEME_CONFIG",
	[ABOUT_CONFIG] = "ABOUT_CONFIG",
    [ANIMATIONS_CONFIG] = "ANIMATIONS_CONFIG",
};

static char *conf_type2str(conf_type_t conf_type)
{
	if (conf_type < NUMBER_OF_TOKENS)
		return conf_str_token[conf_type];

	return NULL;
}

static conf_type_t str2conf_type(char *str)
{
	conf_type_t conf_type;
	
	for (conf_type = 1; conf_type < NUMBER_OF_TOKENS; conf_type++)
	{
		if (!strncmp(str, conf_str_token[conf_type],
			strlen(conf_str_token[conf_type])))
		{
			return conf_type;
		}
	}
		
	return NOT_FOUND_IN_CONF;
}

static uint16_t check_port(char *port, uint16_t default_port)
{
	int value;
	
	if (!strlen(port))
		return default_port;

	for (value = 0; value < (int)strlen(port) - 1; value++)
	{
		if (!isdigit(port[value]))
		{
			fprintf(stderr, "Port field must contain only "
				"non negative digits.\n");
					
			return (uint16_t)-1;
		}
	}
	
	if ((value = (uint16_t)atoi(port)) > USHRT_MAX || !value)
	{
		fprintf(stdout, "Port value %d is out of range. Default port value is "
			"assigned.\n", value);

		return default_port;
	}
	
	return (uint16_t)value;
}

static int check_and_set_value(char *conf_data, char *value, 
		char *default_value, unsigned long max_len)
{
    if (strlen(value) > max_len)
	{
		fprintf(stderr, "The value is too long: %s\n", value);
		return -1;
	}

	if (!strlen(value))
		strncpy(conf_data, default_value, strlen(default_value));
	else
		strncpy(conf_data, value, strlen(value) - 1);

	return 0;
}

static int str2num(char *value)
{
	unsigned int num;
	
	if (!strlen(value))
		return 0;

	for (num = 0; num < strlen(value) - 1; num++)
	{
		if (!isdigit(value[num]))
		{
			fprintf(stderr, "%s value field must contain only "
				"non negative digits.\n", value);
					
			return -1;
		}
	}
	
	return atoi(value);
}

static int config_set_value(conf_type_t conf_type, conf_data_t *conf_data,
		char *value)
{
	switch (conf_type)
	{
		case ROOT:
			if (check_and_set_value(conf_data->root_path, value, DEFAULT_PATH,
				PATH_MAX))
			{
				goto Error;
			}
			break;
		case DEFAULT_FILE:
			if (check_and_set_value((conf_data->default_file), value,
				DEFAULT_FILENAME, NAME_MAX))
			{
				goto Error;
			}
			break;
		case ADDRESS:
			if (check_and_set_value((conf_data->address), value, DEFAULT_ADDRESS,
				INET6_ADDRSTRLEN))
			{
				goto Error;
			}
			break;
		case HTTP_PORT:
			if ((conf_data->http_port = check_port(value, HTTP_PORT)) == (uint16_t)-1)
				goto Error;
			break;
		case HTTPS_PORT:
			if ((conf_data->https_port = check_port(value, HTTPS_PORT)) == (uint16_t)-1)
				goto Error;
			break;
		case DEBUG_LEVEL:
			//if ((debug_lvl = str2num(value)) == -1)
			//	goto Error;
			break;
		case CHUNCK_ENCODING:
			if ((conf_data->chunk_encoding = str2num(value)) == -1)
				goto Error;
			break;
		case W3C_FILE:
			if (check_and_set_value((conf_data->w3c_file), value, DEFAULT_W3C_FILE,
				NAME_MAX))
			{
				goto Error;
			}
			break;
		case SSL_KEY:
			if (check_and_set_value(conf_data->ssl_key, value, DEFAULT_SSL_KEY,
				PATH_MAX))
			{
				goto Error;
			}
			break;
		case SSL_CRT:
			if (check_and_set_value(conf_data->ssl_crt, value, DEFAULT_SSL_CRT,
				PATH_MAX))
			{
				goto Error;
			}
			break;
		case THEME_CONFIG:
			if (check_and_set_value(conf_data->theme_config, value, NULL, PATH_MAX))
				goto Error;
			break;
		case ABOUT_CONFIG:
			if (check_and_set_value(conf_data->about_config, value, NULL, PATH_MAX))
				goto Error;
			break;
		case ANIMATIONS_CONFIG:
			if (check_and_set_value(conf_data->animations_config, value, NULL, PATH_MAX))
				goto Error;
            break;
		default:
			goto Error;
	}

	conf_data->tokens_checker[conf_type]++;
	return 0;

Error:
	return -1;
}

static int check_config_fields(conf_data_t *conf_data)
{
	conf_type_t field_num;
	
	for (field_num = 1; field_num < NUMBER_OF_TOKENS; field_num++)
	{
		if (!conf_data->tokens_checker[field_num])
		{
			fprintf(stderr, "The next configuration is ommitted: %s\n",
				conf_type2str(field_num));
			
			return -1;
		}
		else if (conf_data->tokens_checker[field_num] > 1)
		{
			fprintf(stderr, "The next configuration duplicated %d times: %s\n",
				conf_data->tokens_checker[field_num],
				conf_type2str(field_num));
			
			return -1;
		}
	}

	return 0;
}

static int parse_line(conf_data_t *conf_data, char *buffer, int line_counter)
{
	conf_type_t conf_type;
	
	if ((conf_type = str2conf_type(buffer)))
	{
		if (strncmp(buffer + strlen(conf_type2str(conf_type)), EQUAL_SIGN,
			strlen(EQUAL_SIGN)))
		{
			fprintf(stderr, "No `=` character after token\n");
			return -1;
		}

		if (config_set_value(conf_type, conf_data, buffer +
			strlen(conf_type2str(conf_type)) + 1))
		{
			return -1;
		}
	}
	else
	{
		fprintf(stderr, "Invalid token in configuration file in line %d\n",
			line_counter);

		return -1;
	}

	return 0;
}

static int read_file(const char *config_file, conf_data_t *conf_data)
{
	char *buffer;
	int line_counter = 0, rc = -1;
	size_t buff_size = 0;
	FILE *file = fopen(config_file, "r");

	if (!file)
	{
		fprintf(stderr, "Can't open the file %s\n", config_file);
		return -1;
	}

	while (getline(&buffer, &buff_size, file) != -1) 
	{
		line_counter++;

		if(parse_line(conf_data, buffer, line_counter))
			goto Exit;
	}
	
	rc = 0;

Exit:
	fclose(file);
	free(buffer);

	return rc;
}

const char *getDBXML()
{
    return sDBXML;
}

void setDBXML(const char *database)
{
    sDBXML = (char *)database;
}

conf_data_t *config_init(const char *config_file)
{
    if (!config_file) return NULL;

	conf_data_t *conf_data = calloc(1, sizeof(conf_data_t));

	if (!conf_data)
		return NULL;

	if (read_file(config_file, conf_data))
		goto Error;

	if (check_config_fields(conf_data))
		goto Error;


	return conf_data;

Error:
	free(conf_data);
	return NULL;
}

void *config_get_data(conf_type_t conf_type, conf_data_t *conf_data)
{
	switch (conf_type)
	{
		case ROOT:
			return conf_data->root_path;
		case DEFAULT_FILE:
			return conf_data->default_file;
		case ADDRESS:
			return conf_data->address;
		case HTTP_PORT:
			return &conf_data->http_port;
		case HTTPS_PORT:
			return &conf_data->https_port;
		case CHUNCK_ENCODING:
			return &conf_data->chunk_encoding;
		case W3C_FILE:
			return conf_data->w3c_file;
		case SSL_KEY:
			return conf_data->ssl_key;
		case SSL_CRT:
			return conf_data->ssl_crt;
		case THEME_CONFIG:
			return conf_data->theme_config;
		case ABOUT_CONFIG:
			return conf_data->about_config;
		case ANIMATIONS_CONFIG:
            return conf_data->animations_config;
		default:
			return NULL;
	}
}

void config_free(conf_data_t *conf_data)
{
	free(conf_data);
}
