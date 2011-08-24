#include "m_pd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json/json.h>

#define MAX_ARRAY_SIZE 128
#define MAX_STRING_SIZE 512

typedef struct couchdb {
	t_object x_ob;
	int out_count;
	char *couch_url;
	t_atom out[MAX_ARRAY_SIZE];
} t_couchdb;

typedef struct json_encode{
	t_object x_ob;
	char data[MAX_ARRAY_SIZE][MAX_STRING_SIZE];
	int data_count;
} t_json_encode;
 
typedef struct memory_struct {
  char *memory;
  size_t size;
} t_memory_struct;

/* couchdb */
t_class *couchdb_class;
void setup_couchdb(void);
void *couchdb_new(t_symbol *selector, int argcount, t_atom *argvec);

void couchdb_command(t_couchdb *x, t_symbol *selector, int argcount, t_atom *argvec); 
void couchdb_oauth(t_couchdb *x, t_symbol *selector, int argcount, t_atom *argvec);
void couchdb_url(t_couchdb *x, t_symbol *selector, int argcount, t_atom *argvec);

static size_t write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data);
void test_connection(char *couch_url);
void execute_couchdb(char *couch_url, char *request_type, char *data, char **additional_parameters);

/* json-encode */
t_class *json_encode_class;
void setup_json_encode(void);
void *json_encode_new(t_symbol *selector, int argcount, t_atom *argvec);

void json_encode_bang(t_json_encode *x);
void json_encode_add(t_json_encode *x, t_symbol *selector, int argcount, t_atom *argvec);
void json_encode_clear(t_json_encode *x, t_symbol *selector, int argcount, t_atom *argvec);

/* general */ 
void couchpdb_setup(void);