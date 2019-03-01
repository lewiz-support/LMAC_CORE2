/*
 * TPM utility functions
 *
 *  Copyright (c) 2010 - 2015 IBM Corporation
 *  Authors:
 *    Stefan Berger <stefanb@us.ibm.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>
 */

#ifndef TPM_TPM_UTIL_H
#define TPM_TPM_UTIL_H

#include "sysemu/tpm_backend.h"

void tpm_util_write_fatal_error_response(uint8_t *out, uint32_t out_len);

bool tpm_util_is_selftest(const uint8_t *in, uint32_t in_len);

int tpm_util_test_tpmdev(int tpm_fd, TPMVersion *tpm_version);

#endif /* TPM_TPM_UTIL_H */
