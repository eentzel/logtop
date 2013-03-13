/*
 * Copyright (c) 2010 Julien Palard.  All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FREQUENCY_H__
#define __FREQUENCY_H__

#include <time.h>
#include <uthash.h>

#include "libavl/avl.h"
#include "logtop.h"

typedef struct     s_log_line
{
    char           *string;
    char           *repr;
    unsigned int   count;
    UT_hash_handle hh;
}                  log_line_t;

typedef struct s_history_element
{
    log_line_t *log_entry;
    time_t     time;
}              history_element_t;

typedef struct        s_logtop
{
    log_line_t        *strings;
    struct avl_table  *top;
    history_element_t *history;
    unsigned int      history_start;
    unsigned int      history_size;
}                     logtop;

history_element_t *new_history(logtop *this);
void delete_history(logtop *this);
history_element_t *history_oldest_element(logtop *this);
history_element_t *history_newest_element(logtop *this);
unsigned int history_length(logtop *this);
void history_update(logtop *this, log_line_t *element);

struct avl_table *new_avl(logtop *this);
void delete_avl(logtop *this);
log_line_t *avl_get(logtop *this, char *);
void avl_increment(logtop *this, log_line_t *);
void avl_decrement(logtop *this, log_line_t *);
void avl_traverse(logtop *this, unsigned int length,
                  void (*visitor)(void *data, int index, void *user_data),
                  void *user_data);

logtop *new_logtop(size_t history_size);
void delete_logtop(logtop *this);
void logtop_feed(logtop *this, char *line);

#endif
