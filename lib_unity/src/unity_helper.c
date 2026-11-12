// Copyright 2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#if defined(__riscv_xxcore) && defined(LIB_UNITY_USE_FIXTURE)

#include "unity_helper.h"

// Stack allowance for running one test (setup, body and teardown). Override with
// -DUNITY_TEST_RUNNER_STACK_SIZE=<bytes> if a test needs more.
#ifndef UNITY_TEST_RUNNER_STACK_SIZE
#define UNITY_TEST_RUNNER_STACK_SIZE 1024
#endif

UNITY_STACKFUNCTION(UnityTestRunner, UNITY_TEST_RUNNER_STACK_SIZE);

#endif // defined(__riscv_xxcore) && defined(LIB_UNITY_USE_FIXTURE)
