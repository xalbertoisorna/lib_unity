// Copyright 2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
//
// UnityTestRunner calls each test's setup, body and teardown through function
// pointers, so the XCC linker cannot work out its stack usage. UNITY_STACKFUNCTION
// gives it a fixed stack allowance with resource directives (see unity_helper.c).
#pragma once

/* Stringify helpers to force macro expansion */
#define UNITY_STRINGIFY_(x) #x
#define UNITY_STRINGIFY(x) UNITY_STRINGIFY_(x)

/* Macro to declare XMOS linker resource annotations for a function. */
#if defined(UNITY_HELPER_RV_TOOLS)
#define UNITY_STACKFUNCTION(FN, BYTES) \
    asm(".pushsection .text." #FN "_stack_allowance,\"axR\",@progbits\n" \
        ".globl " #FN "_stack_allowance\n" #FN "_stack_allowance:\n.popsection"); \
    asm(".resource_const " #FN "_stack_allowance, \"stack_frame_bytes\", " UNITY_STRINGIFY(BYTES)); \
    asm(".resource_list_empty " #FN "_stack_allowance, \"callees\""); \
    asm(".resource_list_empty " #FN "_stack_allowance, \"tail_callees\""); \
    asm(".resource_list_empty " #FN "_stack_allowance, \"parallel_callees\""); \
    asm(".resource_list_add " #FN ", \"callees\", " #FN "_stack_allowance")
#else // RV-XCC
#define UNITY_STACKFUNCTION(FN, BYTES) \
    asm(".resource_list_empty " #FN ", \"callees\""); \
    asm(".resource_list_empty " #FN ", \"tail_callees\""); \
    asm(".resource_list_empty " #FN ", \"parallel_callees\""); \
    asm(".resource_const " #FN ", \"stack_frame_bytes\", " UNITY_STRINGIFY(BYTES))
#endif // defined(UNITY_HELPER_RV_TOOLS)
