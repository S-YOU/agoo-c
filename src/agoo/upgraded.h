// Copyright (c) 2018, Peter Ohler, All rights reserved.

#ifndef AGOO_UPGRADED_H
#define AGOO_UPGRADED_H

#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

#include "atomic.h"

struct _agooCon;
struct _agooSubject;

typedef struct _agooUpgraded {
    struct _agooUpgraded	*next;
    struct _agooUpgraded	*prev;
    struct _agooCon		*con;
    atomic_int			pending;
    atomic_int			ref_cnt;
    struct _agooSubject		*subjects;

    void			*ctx;
    void			*wrap;
    void			*env;

    bool			on_empty;
    bool			on_close;
    bool			on_shut;
    bool			on_msg;
    bool			on_error;
    void			(*on_destroy)(struct _agooUpgraded *up);
} *agooUpgraded;

extern agooUpgraded	agoo_upgraded_create(struct _agooCon *c, void * ctx, void *env);

extern void		agoo_upgraded_release(agooUpgraded up);
extern void		agoo_upgraded_release_con(agooUpgraded up);

extern void		agoo_upgraded_ref(agooUpgraded up);

extern void		agoo_upgraded_add_subject(agooUpgraded up, struct _agooSubject *subject);
extern void		agoo_upgraded_del_subject(agooUpgraded up, struct _agooSubject *subject);
extern bool		agoo_upgraded_match(agooUpgraded up, const char *subject);

extern bool		agoo_upgraded_write(agooUpgraded up, const char *message, size_t mlen, bool bin, bool inc_ref);
extern void		agoo_upgraded_subscribe(agooUpgraded up, const char *subject, int slen, bool inc_ref);
extern void		agoo_upgraded_unsubscribe(agooUpgraded up, const char *subject, int slen, bool inc_ref);
extern void		agoo_upgraded_close(agooUpgraded up, bool inc_ref);
extern int		agoo_upgraded_pending(agooUpgraded up);

#endif // AGOO_UPGRADED_H
