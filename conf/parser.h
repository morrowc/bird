/*
 *	BIRD Internet Routing Daemon -- Configuration Parser Headers
 *
 *	(c) 2018 Maria Matejka <mq@jmq.cz>
 *
 *	Can be freely distributed and used under the terms of the GNU GPL.
 */

#ifndef _BIRD_CONF_PARSER_H_
#define _BIRD_CONF_PARSER_H_

#include "conf/context.h"

/* Pools */

#define cfg_alloc(size) lp_alloc(ctx->cfg_mem, size)
#define cfg_allocu(size) lp_allocu(ctx->cfg_mem, size)
#define cfg_allocz(size) lp_allocz(ctx->cfg_mem, size)
#define cfg_strdup(str) cf_strdup(ctx, str)
#define cfg_copy_list(dest, src, node_size) cf_copy_list(ctx, dest, src, node_size)

/* Lexer */

/* Generated lexer entry point */
typedef void * yyscan_t;
union YYSTYPE;
int cfx_lex(union YYSTYPE *, yyscan_t);

/* Config context alloc and free */
struct cf_context *cf_new_context(int, struct conf_order *);
void cf_free_context(struct cf_context *);

/* Lexer state alloc and free */
struct conf_state *cf_new_state(struct cf_context *ctx, const char *name);
void cf_free_state(struct cf_context *ctx, struct conf_state *cs);

/* Init keyword hash is called once from global init */
void cf_init_kh(void);

/* Hash function is common for keywords and symbols */
uint cf_hash(byte *c);


/* Parser */

extern char *cf_text;
int cfx_parse(struct cf_context *ctx, void *yyscanner);

/* Generated error callback */
#define cfx_error(ctx, yyscanner, ...) cf_error(ctx, __VA_ARGS__)

/* Symbols */

void cf_push_scope(struct cf_context *, struct symbol *);
void cf_pop_scope(struct cf_context *);

struct symbol *cf_get_symbol(struct cf_context *ctx, byte *c);
struct symbol *cf_default_name(struct cf_context *ctx, char *template, int *counter);
struct symbol *cf_define_symbol(struct cf_context *ctx, struct symbol *symbol, int type, void *def);

#endif