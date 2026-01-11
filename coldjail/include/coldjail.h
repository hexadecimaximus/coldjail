/*
 * Coldjail - Minimalist Linux sandbox
 * Copyright (c) 2026 Rodrigo de Freitas
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef COLDJAIL_H
#define COLDJAIL_H

// Opaque type: definition hidden in jail.c
typedef struct coldjail ColdJail;

// Constructor and destructor
ColdJail *coldjail_new(const char *rootfs);
void coldjail_free(ColdJail *cj);

// Configuration control
void coldjail_set_net_none(ColdJail *cj, int enabled);
const char *coldjail_get_hostname(const ColdJail *cj);

// Main execution
int coldjail_run(ColdJail *cj);

#endif
