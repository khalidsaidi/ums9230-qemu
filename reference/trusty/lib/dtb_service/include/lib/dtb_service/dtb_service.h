/*
 * Copyright (c) 2022, Google Inc. All rights reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <lib/ktipc/ktipc.h>
#include <lk/compiler.h>

__BEGIN_CDECLS

/**
 * dtb_service_add() - Add a dtb service to the given ktipc server and
 *                     to the Binder discovery library.
 * @dtb: Pointer to the base of the dtb in memory.
 * @dtb_size: Size in bytes of the dtb.
 * @dt_port: Port name for the kernel device tree service.
 * @dtb_port: Port name for the device tree blob service.
 * @server: The ktipc server.
 *
 * Return: %NO_ERROR in case of success, error code otherwise.
 */
int dtb_service_add(const void* dtb,
                    size_t dtb_size,
                    const char* dt_port,
                    const char* dtb_port,
                    struct ktipc_server* server);

/**
 * dtb_set() - Set the dtb singleton to be provided by dtb_get().
 * @dtb: Pointer to the base of the dtb in memory.
 * @size: Size of the buffer pointer to by dtb.
 *
 * Return: %NO_ERROR if dtb is a valid device tree. %ERR_NOT_VALID otherwise.
 */
int dtb_set(const uint8_t* dtb, size_t size);

/**
 * dtb_get() - Set the dtb singleton.
 * @ptr: Output pointer for the dtb.
 * @size: Output size of the dtb.
 *
 * Return: %NO_ERROR in case of success, ptr and size are updated with the
 * location and size of the dtb.
 * %ERR_INVALID_ARGS if ptr or size is null
 * %ERR_NOT_READY if the dtb has not been set. ptr and size are set to zero
 */
int dtb_get(const uint8_t** ptr, size_t* size);

__END_CDECLS
