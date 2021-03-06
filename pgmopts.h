/**
 *	ratched - TLS connection router that performs a man-in-the-middle attack
 *	Copyright (C) 2017-2017 Johannes Bauer
 *
 *	This file is part of ratched.
 *
 *	ratched is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; this program is ONLY licensed under
 *	version 3 of the License, later versions are explicitly excluded.
 *
 *	ratched is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with ratched; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	Johannes Bauer <JohannesBauer@gmx.de>
**/

#ifndef __PGMOPTS_H__
#define __PGMOPTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "map.h"
#include "logging.h"

enum keytype_t {
	KEYTYPE_RSA,
	KEYTYPE_ECC,
};

struct pgmopts_t {
	char *config_dir;

	struct {
		const char *filename;
		const char *comment;
		bool use_ipv6_encapsulation;
	} pcapng;

	struct {
		enum loglvl_t level;
		const char *logfilename;
		bool flush;
		bool dump_certificates;
		bool write_memdumps_into_files;
	} log;

	struct {
		bool daemonize;
		bool singleshot;
	} operation;

	struct {
		struct {
			uint32_t ipv4_nbo;
			uint16_t port_nbo;
			unsigned int listen;
		} server_socket;
		struct {
			uint32_t ipv4_nbo;
			uint16_t port_nbo;
		} local_forwarding;
		double initial_read_timeout;
	} network;

	struct {
		const char *crl_uri, *ocsp_responder_uri;
		bool mark_forged_certificates;
		bool recalculate_key_identifiers;
	} forged_certs;

	struct intercept_config_t *default_config;
	struct map_t *custom_configs;

	struct {
		enum keytype_t keytype;
		union {
			struct {
				unsigned int modulus_length_bits;
			} rsa;
			struct {
				char *curvename;
			} ecc;
		};
	} keyspec;
};

extern const struct pgmopts_t *pgm_options;

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void show_syntax(const char *pgmbinary);
const struct intercept_config_t* pgmopts_get_intercept_config(const char *hostname);
struct certificate_runtime_parameters_t **pgmopts_get_default_client_parameters(void);
struct certificate_runtime_parameters_t **pgmopts_get_specific_client_parameters(int index);
bool parse_options(int argc, char **argv);
void free_pgm_options(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
