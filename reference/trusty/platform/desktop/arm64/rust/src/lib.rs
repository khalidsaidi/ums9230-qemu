/*
 * Copyright (c) 2025 Google Inc. All rights reserved
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

//! This library provides and registers a little kernel pre threading init function to map desktop
//! specific reserved memory nodes from the device tree into the gsc_svc trusted app.

#![no_std]

use core::ffi::{c_uint, CStr};
use core::slice::from_raw_parts;
use dtb_service::sys::{dtb_get, NO_ERROR};
use libfdt::FdtNode;
use rust_support::{
    init::lk_init_level,
    ipc::IPC_PORT_ALLOW_TA_CONNECT,
    ktipc::{ktipc_port_acl, uuid},
    LK_INIT_HOOK,
};

/// UUID of the gsc_svc app.
const GSC_SVC_UUID: uuid = uuid {
    time_low: 0x77026d06,
    time_mid: 0xbe0f,
    time_hi_and_version: 0x4604,
    clock_seq_and_node: [0xa6, 0xd5, 0xf7, 0x29, 0x38, 0x8a, 0x44, 0x5b],
};
const UUIDS: [*const uuid; 1] = [&GSC_SVC_UUID as *const uuid];
const KTIPC_PORT_ACL: ktipc_port_acl = ktipc_port_acl {
    flags: IPC_PORT_ALLOW_TA_CONNECT,
    uuid_num: UUIDS.len() as u32,
    uuids: (&UUIDS).as_ptr(),
    extra_data: core::ptr::null(),
};

fn share_reserved_memory(reserved_mem: &FdtNode, name: &'static CStr) {
    let node = reserved_mem
        .next_compatible(name)
        .expect("Could not get boot param node")
        .expect("Could not get boot param node");
    let mut reg_itr =
        node.reg().expect("Could not get reg address").expect("Could not get reg address");
    let reg = reg_itr.next().expect("Could not get reg address");
    vmm_obj_service_rust::share_sized_buffer(
        reg.addr as *const u8,
        reg.size.unwrap_or(0) as usize,
        0,
        name,
        &KTIPC_PORT_ACL,
    )
    .expect("Could not share boot params");
    if reg_itr.next().is_some() {
        log::warn!("Found unexpected address is reg node. Ignoring.");
    }
}

extern "C" fn platform_dtb_init_func(_level: c_uint) {
    let mut fdt_ptr: *const u8 = core::ptr::null_mut();
    let mut fdt_size = 0usize;
    // SAFETY: Neither pointer is retained by dtb_get. dbt_get does not read from *fdt_ptr.
    let rc = unsafe { dtb_get(&mut fdt_ptr as *mut *const u8, &mut fdt_size) };
    if rc != NO_ERROR as i32 || fdt_ptr.is_null() {
        log::error!("Failed to get device tree (rc: {rc}, ptr: {fdt_ptr:p}, size: {fdt_size}).");
        return;
    }
    // SAFETY: Outputs from dtb_get are defined to be static, read only, and span the size returned.
    // fdt_ptr has already been checked for null.
    let fdt = unsafe { from_raw_parts(fdt_ptr, fdt_size) };

    let fdt = libfdt::Fdt::from_slice(fdt).expect("Device tree should be valid");
    let reserved_mem = fdt
        .node(c"/reserved-memory")
        .expect("Could not get reserved memory node")
        .expect("Could not get reserved memory node");

    let boot_params = [
        c"google,open-dice",
        c"google,session-key-seed",
        c"google,early-entropy",
        c"google,auth-token-key-seed",
    ];

    for param in boot_params {
        share_reserved_memory(&reserved_mem, param);
    }
}

LK_INIT_HOOK!(platform_dtb_init, platform_dtb_init_func, lk_init_level::LK_INIT_LEVEL_THREADING);
