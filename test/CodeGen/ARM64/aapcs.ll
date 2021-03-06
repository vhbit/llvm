; RUN: llc -mtriple=arm64-linux-gnu -enable-misched=false < %s | FileCheck %s

@var = global i32 0, align 4

define i128 @test_i128_align(i32, i128 %arg, i32 %after) {
  store i32 %after, i32* @var, align 4
; CHECK: str w4, [{{x[0-9]+}}, :lo12:var]

  ret i128 %arg
; CHECK: mov x0, x2
; CHECK: mov x1, x3
}

@var64 = global i64 0, align 8

  ; Check stack slots are 64-bit at all times.
define void @test_stack_slots([8 x i32], i1 %bool, i8 %char, i16 %short,
                                i32 %int, i64 %long) {
  ; Part of last store. Blasted scheduler.
; CHECK: ldr [[LONG:x[0-9]+]], [sp, #32]

  %ext_bool = zext i1 %bool to i64
  store volatile i64 %ext_bool, i64* @var64, align 8
; CHECK: ldr w[[EXT:[0-9]+]], [sp]
; CHECK: and x[[EXTED:[0-9]+]], x[[EXT]], #0x1
; CHECK: str x[[EXTED]], [{{x[0-9]+}}, :lo12:var64]

  %ext_char = zext i8 %char to i64
  store volatile i64 %ext_char, i64* @var64, align 8
; CHECK: ldrb w[[EXT:[0-9]+]], [sp, #8]
; CHECK: str x[[EXT]], [{{x[0-9]+}}, :lo12:var64]

  %ext_short = zext i16 %short to i64
  store volatile i64 %ext_short, i64* @var64, align 8
; CHECK: ldrh w[[EXT:[0-9]+]], [sp, #16]
; CHECK: str x[[EXT]], [{{x[0-9]+}}, :lo12:var64]

  %ext_int = zext i32 %int to i64
  store volatile i64 %ext_int, i64* @var64, align 8
; CHECK: ldr w[[EXT:[0-9]+]], [sp, #24]
; CHECK: str x[[EXT]], [{{x[0-9]+}}, :lo12:var64]

  store volatile i64 %long, i64* @var64, align 8
; CHECK: str [[LONG]], [{{x[0-9]+}}, :lo12:var64]

  ret void
}

; Make sure the callee does extensions (in the absence of zext/sext
; keyword on args) while we're here.

define void @test_extension(i1 %bool, i8 %char, i16 %short, i32 %int) {
  %ext_bool = zext i1 %bool to i64
  store volatile i64 %ext_bool, i64* @var64
; CHECK: and [[EXT:x[0-9]+]], x0, #0x1
; CHECK: str [[EXT]], [{{x[0-9]+}}, :lo12:var64]

  %ext_char = sext i8 %char to i64
  store volatile i64 %ext_char, i64* @var64
; CHECK: sxtb [[EXT:x[0-9]+]], x1
; CHECK: str [[EXT]], [{{x[0-9]+}}, :lo12:var64]

  %ext_short = zext i16 %short to i64
  store volatile i64 %ext_short, i64* @var64
; CHECK: and [[EXT:x[0-9]+]], x2, #0xffff
; CHECK: str [[EXT]], [{{x[0-9]+}}, :lo12:var64]

  %ext_int = zext i32 %int to i64
  store volatile i64 %ext_int, i64* @var64
; CHECK: uxtw [[EXT:x[0-9]+]], x3
; CHECK: str [[EXT]], [{{x[0-9]+}}, :lo12:var64]

  ret void
}

declare void @variadic(i32 %a, ...)

  ; Under AAPCS variadic functions have the same calling convention as
  ; others. The extra arguments should go in registers rather than on the stack.
define void @test_variadic() {
  call void(i32, ...)* @variadic(i32 0, i64 1, double 2.0)
; CHECK: fmov d0, #2.0
; CHECK: orr x1, xzr, #0x1
; CHECK: bl variadic
  ret void
}
