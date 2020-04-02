	.file	"MortonCurve.cpp"
# GNU C++14 (Ubuntu 9.2.1-9ubuntu2) version 9.2.1 20191008 (x86_64-linux-gnu)
#	compiled by GNU C version 9.2.1 20191008, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -I ../include -I ../include -imultiarch x86_64-linux-gnu
# -D_GNU_SOURCE MortonCurve.cpp -mtune=generic -march=x86-64 -O3 -O3 -Wall
# -Wextra -Werror -Wfatal-errors -ffast-math -fverbose-asm
# -fopt-info-vec-missed -fasynchronous-unwind-tables
# -fstack-protector-strong -Wformat-security -fstack-clash-protection
# -fcf-protection
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -falign-functions -falign-jumps -falign-labels -falign-loops
# -fassociative-math -fassume-phsa -fasynchronous-unwind-tables
# -fauto-inc-dec -fbranch-count-reg -fcaller-saves -fcode-hoisting
# -fcombine-stack-adjustments -fcommon -fcompare-elim -fcprop-registers
# -fcrossjumping -fcse-follow-jumps -fcx-limited-range -fdefer-pop
# -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -fexceptions -fexpensive-optimizations -ffinite-math-only
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
# -fgcse-after-reload -fgcse-lm -fgnu-runtime -fgnu-unique
# -fguess-branch-probability -fhoist-adjacent-loads -fident -fif-conversion
# -fif-conversion2 -findirect-inlining -finline -finline-atomics
# -finline-functions -finline-functions-called-once
# -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-cp-clone -fipa-icf
# -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
# -fipa-ra -fipa-reference -fipa-reference-addressable -fipa-sra
# -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -floop-interchange
# -floop-unroll-and-jam -flra-remat -flto-odr-type-merging
# -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
# -fomit-frame-pointer -foptimize-sibling-calls -foptimize-strlen
# -fpartial-inlining -fpeel-loops -fpeephole -fpeephole2 -fplt
# -fpredictive-commoning -fprefetch-loop-arrays -freciprocal-math -free
# -freg-struct-return -freorder-blocks -freorder-blocks-and-partition
# -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
# -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsplit-ivs-in-unroller -fsplit-loops
# -fsplit-paths -fsplit-wide-types -fssa-backprop -fssa-phiopt
# -fstack-clash-protection -fstack-protector-strong -fstdarg-opt
# -fstore-merging -fstrict-aliasing -fstrict-volatile-bitfields
# -fsync-libcalls -fthread-jumps -ftoplevel-reorder -ftree-bit-ccp
# -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
# -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
# -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-distribute-patterns
# -ftree-loop-distribution -ftree-loop-if-convert -ftree-loop-im
# -ftree-loop-ivcanon -ftree-loop-optimize -ftree-loop-vectorize
# -ftree-parallelize-loops= -ftree-partial-pre -ftree-phiprop -ftree-pre
# -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink
# -ftree-slp-vectorize -ftree-slsr -ftree-sra -ftree-switch-conversion
# -ftree-tail-merge -ftree-ter -ftree-vrp -funit-at-a-time
# -funsafe-math-optimizations -funswitch-loops -funwind-tables
# -fverbose-asm -fversion-loops-for-strides -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store
# -mfancy-math-387 -mfp-ret-in-387 -mfxsr -mglibc -mlong-double-80 -mmmx
# -mno-sse4 -mpush-args -mred-zone -msse -msse2 -mstv -mtls-direct-seg-refs
# -mvzeroupper

	.text
	.align 2
	.p2align 4
	.type	_ZN7FastBVH4impl11MortonCurveIfEclIiZ16generateMorton32PKfS5_S5_PKimEUliE_EENS0_5ArrayIjEERKNS_13ConstIterableIT_EET0_RKNS_4BBoxIfEE.isra.0.constprop.0, @function
_ZN7FastBVH4impl11MortonCurveIfEclIiZ16generateMorton32PKfS5_S5_PKimEUliE_EENS0_5ArrayIjEERKNS_13ConstIterableIT_EET0_RKNS_4BBoxIfEE.isra.0.constprop.0:
.LFB655:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r15	#
	pushq	%r14	#
	pushq	%r13	#
	pushq	%r12	#
	pushq	%rbx	#
	andq	$-64, %rsp	#,
	subq	$4096, %rsp	#,
	orq	$0, (%rsp)	#,
	subq	$192, %rsp	#,
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
# ../include/FastBVH/impl/MortonCurve.inl:45:   auto x_factor = morton_domain / domain.x;
	movss	.LC0(%rip), %xmm0	#, tmp379
# ../include/FastBVH/impl/MortonCurve.inl:49:   Array<Code> codes(primitives.size());
	movq	8(%rsi), %r12	# MEM[(long unsigned int *)primitives_9(D) + 8B], _10
# ../include/FastBVH/impl/MortonCurve.inl:45:   auto x_factor = morton_domain / domain.x;
	movaps	%xmm0, %xmm4	# tmp379, x_factor
# ../include/FastBVH/impl/MortonCurve.inl:46:   auto y_factor = morton_domain / domain.y;
	movaps	%xmm0, %xmm6	# tmp379, y_factor
# ../include/FastBVH/impl/MortonCurve.inl:45:   auto x_factor = morton_domain / domain.x;
	divss	32(%rdx), %xmm4	# MEM[(const struct BBox &)bbox_2(D) + 32], x_factor
# ../include/FastBVH/impl/MortonCurve.inl:46:   auto y_factor = morton_domain / domain.y;
	divss	36(%rdx), %xmm6	# MEM[(const struct BBox &)bbox_2(D) + 36], y_factor
# ../include/FastBVH/impl/MortonCurve.inl:47:   auto z_factor = morton_domain / domain.z;
	divss	40(%rdx), %xmm0	# MEM[(const struct BBox &)bbox_2(D) + 40], tmp379
# ../include/FastBVH/impl/MortonCurve.inl:39: typename MortonCurve<Float>::CodeArray MortonCurve<Float>::operator() (const ConstIterable<Primitive>& primitives, BoxConverter converter, const BBox<Float>& bbox) {
	movq	%rdi, 48(%rsp)	# <retval>, %sfp
	movq	%rdi, %r15	# tmp753, <retval>
	movq	%rsi, %r14	# tmp754, primitives
	movq	%rdx, %rbx	# tmp755, bbox
	movq	%rsi, 56(%rsp)	# primitives, %sfp
# ../include/FastBVH/impl/Memory.h:33:   return (T*)allocateDeviceMemory(element_count * sizeof(T));
	leaq	0(,%r12,4), %rdi	#, tmp382
# ../include/FastBVH/impl/MortonCurve.inl:39: typename MortonCurve<Float>::CodeArray MortonCurve<Float>::operator() (const ConstIterable<Primitive>& primitives, BoxConverter converter, const BBox<Float>& bbox) {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp789
	movq	%rax, 4280(%rsp)	# tmp789, D.16764
	xorl	%eax, %eax	# tmp789
# ../include/FastBVH/impl/MortonCurve.inl:45:   auto x_factor = morton_domain / domain.x;
	movss	%xmm4, 88(%rsp)	# x_factor, %sfp
# ../include/FastBVH/impl/MortonCurve.inl:46:   auto y_factor = morton_domain / domain.y;
	movss	%xmm6, 84(%rsp)	# y_factor, %sfp
# ../include/FastBVH/impl/MortonCurve.inl:47:   auto z_factor = morton_domain / domain.z;
	movss	%xmm0, 92(%rsp)	# tmp379, %sfp
# ../include/FastBVH/impl/Memory.h:15:   return std::malloc(size);
	call	malloc@PLT	#
# ../include/FastBVH/impl/Array.h:33:     count = elements ? c : 0;
	testq	%rax, %rax	# _12
# ../include/FastBVH/impl/Memory.h:15:   return std::malloc(size);
	movq	%rax, 64(%rsp)	# _12, %sfp
# ../include/FastBVH/impl/Array.h:32:     elements = allocateArray<T>(c);
	movq	%rax, (%r15)	# _12, MEM[(struct Array *)codes_1(D)].elements
# ../include/FastBVH/impl/Array.h:33:     count = elements ? c : 0;
	movl	$0, %eax	#, tmp742
	cmove	%rax, %r12	# _10,, tmp742, _10
# ../include/FastBVH/impl/Array.h:33:     count = elements ? c : 0;
	movq	%r12, 8(%r15)	# _10, MEM[(struct Array *)codes_1(D)].count
# ../include/FastBVH/impl/MortonCurve.inl:55:   auto count = primitives.size();
	movq	8(%r14), %r12	# MEM[(long unsigned int *)primitives_9(D) + 8B], _14
# ../include/FastBVH/impl/MortonCurve.inl:71:   for (decltype(count) i = 0; i < count; i += batch_size_max) {
	testq	%r12, %r12	# _14
	je	.L1	#,
	movaps	.LC1(%rip), %xmm3	#, tmp743
	movaps	.LC3(%rip), %xmm7	#, tmp745
	xorl	%edx, %edx	# ivtmp.174
# ../include/FastBVH/impl/MortonCurve.inl:71:   for (decltype(count) i = 0; i < count; i += batch_size_max) {
	xorl	%r11d, %r11d	# _16
	movdqa	.LC2(%rip), %xmm4	#, tmp744
	movaps	.LC4(%rip), %xmm6	#, tmp746
	movdqa	.LC5(%rip), %xmm13	#, tmp747
	movdqa	.LC6(%rip), %xmm12	#, tmp748
	movdqa	.LC7(%rip), %xmm11	#, tmp749
	.p2align 4,,10
	.p2align 3
.L31:
	movq	%r11, %rax	# _16, i
# ../include/FastBVH/impl/MortonCurve.inl:73:     auto batch_size = ((i + batch_size_max) < count) ? batch_size_max : (count - i);
	addq	$256, %r11	#, _16
# ../include/FastBVH/impl/MortonCurve.inl:73:     auto batch_size = ((i + batch_size_max) < count) ? batch_size_max : (count - i);
	cmpq	%r11, %r12	# _16, _14
	ja	.L33	#,
# ../include/FastBVH/impl/MortonCurve.inl:76:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	movq	%r12, %rdi	# _14, _155
	subq	%rax, %rdi	# i, _155
	je	.L1	#,
.L4:
	movq	56(%rsp), %rcx	# %sfp, primitives
	movq	16(%rbp), %r15	# converter.__vertices_x, pretmp_308
# ../include/FastBVH/impl/MortonCurve.inl:76:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	xorl	%eax, %eax	# j
	leaq	128(%rsp), %r10	#, tmp735
	movq	24(%rbp), %r14	# converter.__vertices_y, pretmp_310
	movq	32(%rbp), %r13	# converter.__vertices_z, pretmp_312
	leaq	1152(%rsp), %r8	#, tmp731
	leaq	2176(%rsp), %r9	#, tmp734
	movq	(%rcx), %rsi	# MEM[(const int * *)primitives_9(D)], tmp720
	addq	%rdx, %rsi	# ivtmp.174, tmp720
	.p2align 4,,10
	.p2align 3
.L5:
# MortonCurve.cpp:15:       vertices_x[s] - 0.5f,
	movslq	(%rsi,%rax,4), %rcx	# MEM[base: _200, index: j_162, step: 4, offset: 0], MEM[base: _200, index: j_162, step: 4, offset: 0]
# MortonCurve.cpp:16:       vertices_y[s] - 0.5f,
	movss	(%r14,%rcx,4), %xmm1	# *_102, _103
# MortonCurve.cpp:17:       vertices_z[s] - 0.5f
	movss	0(%r13,%rcx,4), %xmm0	# *_106, _107
# ../include/FastBVH/impl/MortonCurve.inl:78:       center_x[j] = pc.x;
	movss	(%r15,%rcx,4), %xmm2	# *_98, *_98
# ../include/FastBVH/impl/MortonCurve.inl:79:       center_y[j] = pc.y;
	movss	%xmm1, (%r8,%rax,4)	# _103, MEM[symbol: center_y, index: j_162, step: 4, offset: 0B]
# ../include/FastBVH/impl/MortonCurve.inl:78:       center_x[j] = pc.x;
	movss	%xmm2, (%r10,%rax,4)	# *_98, MEM[symbol: center_x, index: j_162, step: 4, offset: 0B]
# ../include/FastBVH/impl/MortonCurve.inl:80:       center_z[j] = pc.z;
	movss	%xmm0, (%r9,%rax,4)	# _107, MEM[symbol: center_z, index: j_162, step: 4, offset: 0B]
# ../include/FastBVH/impl/MortonCurve.inl:76:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	addq	$1, %rax	#, j
# ../include/FastBVH/impl/MortonCurve.inl:76:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	cmpq	%rdi, %rax	# _155, j
	jb	.L5	#,
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	(%rbx), %xmm2	# bbox_2(D)->min.x, _40
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	4(%rbx), %xmm0	# bbox_2(D)->min.y, _44
	leaq	-1(%rdi), %rax	#, tmp391
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	8(%rbx), %xmm1	# bbox_2(D)->min.z, _48
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	%xmm2, 80(%rsp)	# _40, %sfp
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	%xmm0, 76(%rsp)	# _44, %sfp
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	%xmm1, 72(%rsp)	# _48, %sfp
	cmpq	$2, %rax	#, tmp391
	jbe	.L34	#,
	movaps	%xmm2, %xmm5	# _40, vect_cst__244
	movq	%rdi, %rcx	# _155, bnd.69
	movss	84(%rsp), %xmm9	# %sfp, vect_cst__232
	xorl	%eax, %eax	# ivtmp.152
	shufps	$0, %xmm5, %xmm5	# vect_cst__244
	shrq	$2, %rcx	#, bnd.69
	movaps	%xmm0, %xmm10	# _44, vect_cst__234
	movaps	%xmm5, 96(%rsp)	# vect_cst__244, %sfp
	movss	88(%rsp), %xmm5	# %sfp, vect_cst__242
	movaps	%xmm1, %xmm8	# _48, vect_cst__224
	salq	$4, %rcx	#, _209
	leaq	3200(%rsp), %rsi	#, tmp730
	shufps	$0, %xmm10, %xmm10	# vect_cst__234
	shufps	$0, %xmm9, %xmm9	# vect_cst__232
	shufps	$0, %xmm8, %xmm8	# vect_cst__224
	shufps	$0, %xmm5, %xmm5	# vect_cst__242
	movaps	%xmm5, 112(%rsp)	# vect_cst__242, %sfp
	movss	92(%rsp), %xmm5	# %sfp, vect_cst__222
	shufps	$0, %xmm5, %xmm5	# vect_cst__222
	.p2align 4,,10
	.p2align 3
.L7:
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movaps	(%r10,%rax), %xmm2	# MEM[symbol: center_x, index: ivtmp.152_39, offset: 0B], vect__41.75
	subps	96(%rsp), %xmm2	# %sfp, vect__41.75
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	movaps	%xmm3, %xmm14	# tmp743, tmp413
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	mulps	112(%rsp), %xmm2	# %sfp, vect__42.76
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movaps	(%r8,%rax), %xmm1	# MEM[symbol: center_y, index: ivtmp.152_39, offset: 0B], vect__45.82
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movaps	(%r9,%rax), %xmm0	# MEM[symbol: center_z, index: ivtmp.152_39, offset: 0B], vect__49.89
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	subps	%xmm10, %xmm1	# vect_cst__234, vect__45.82
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	subps	%xmm8, %xmm0	# vect_cst__224, vect__49.89
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movaps	%xmm2, (%r10,%rax)	# vect__42.76, MEM[symbol: center_x, index: ivtmp.152_39, offset: 0B]
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	mulps	%xmm9, %xmm1	# vect_cst__232, vect__46.83
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	cmpleps	%xmm2, %xmm14	#, vect__42.76, tmp413
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	mulps	%xmm5, %xmm0	# vect_cst__222, vect__50.90
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	movaps	%xmm14, %xmm15	# tmp413, tmp414
	pslld	$31, %xmm14	#, tmp417
	andps	%xmm3, %xmm15	# tmp743, tmp414
	subps	%xmm15, %xmm2	# tmp414, tmp415
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movaps	%xmm1, (%r8,%rax)	# vect__46.83, MEM[symbol: center_y, index: ivtmp.152_39, offset: 0B]
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movaps	%xmm0, (%r9,%rax)	# vect__50.90, MEM[symbol: center_z, index: ivtmp.152_39, offset: 0B]
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	cvttps2dq	%xmm2, %xmm2	# tmp415, tmp418
	pxor	%xmm2, %xmm14	# tmp418, vect_x_code_51.93
# ../include/FastBVH/impl/MortonCurve.inl:94:       x_code = min(x_code, morton_domain - 1);
	movaps	%xmm3, %xmm2	# tmp743, tmp427
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movdqa	%xmm14, %xmm15	# vect_x_code_51.93, tmp420
	psrld	$16, %xmm14	#, tmp421
	cvtdq2ps	%xmm14, %xmm14	# tmp421, tmp423
	mulps	%xmm7, %xmm14	# tmp745, tmp425
	pand	%xmm4, %xmm15	# tmp744, tmp420
	cvtdq2ps	%xmm15, %xmm15	# tmp420, tmp422
	addps	%xmm15, %xmm14	# tmp422, vect__54.96
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minps	%xmm6, %xmm14	# tmp746, vect__54.96
# ../include/FastBVH/impl/MortonCurve.inl:94:       x_code = min(x_code, morton_domain - 1);
	cmpleps	%xmm14, %xmm2	#, vect__54.96, tmp427
	movaps	%xmm2, %xmm15	# tmp427, tmp428
	pslld	$31, %xmm2	#, tmp431
	andps	%xmm3, %xmm15	# tmp743, tmp428
	subps	%xmm15, %xmm14	# tmp428, tmp429
	cvttps2dq	%xmm14, %xmm14	# tmp429, tmp432
	pxor	%xmm14, %xmm2	# tmp432, vect_x_code_56.98
# ../include/FastBVH/impl/MortonCurve.inl:91:       Code y_code = Code(center_y[j]);
	movaps	%xmm3, %xmm14	# tmp743, tmp435
	cmpleps	%xmm1, %xmm14	#, vect__46.83, tmp435
	movaps	%xmm14, %xmm15	# tmp435, tmp436
	pslld	$31, %xmm14	#, tmp439
	andps	%xmm3, %xmm15	# tmp743, tmp436
	subps	%xmm15, %xmm1	# tmp436, tmp437
	cvttps2dq	%xmm1, %xmm1	# tmp437, tmp440
	pxor	%xmm1, %xmm14	# tmp440, vect_y_code_52.94
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movdqa	%xmm14, %xmm15	# vect_y_code_52.94, tmp442
	psrld	$16, %xmm14	#, tmp443
	cvtdq2ps	%xmm14, %xmm14	# tmp443, tmp445
	mulps	%xmm7, %xmm14	# tmp745, tmp447
	pand	%xmm4, %xmm15	# tmp744, tmp442
	cvtdq2ps	%xmm15, %xmm1	# tmp442, tmp444
	addps	%xmm14, %xmm1	# tmp447, vect__57.99
# ../include/FastBVH/impl/MortonCurve.inl:95:       y_code = min(y_code, morton_domain - 1);
	movaps	%xmm3, %xmm14	# tmp743, tmp449
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minps	%xmm6, %xmm1	# tmp746, vect__57.99
# ../include/FastBVH/impl/MortonCurve.inl:95:       y_code = min(y_code, morton_domain - 1);
	cmpleps	%xmm1, %xmm14	#, vect__57.99, tmp449
	movaps	%xmm14, %xmm15	# tmp449, tmp450
	pslld	$31, %xmm14	#, tmp453
	andps	%xmm3, %xmm15	# tmp743, tmp450
	subps	%xmm15, %xmm1	# tmp450, tmp451
	cvttps2dq	%xmm1, %xmm1	# tmp451, tmp454
	pxor	%xmm14, %xmm1	# tmp453, vect_y_code_59.101
# ../include/FastBVH/impl/MortonCurve.inl:92:       Code z_code = Code(center_z[j]);
	movaps	%xmm3, %xmm14	# tmp743, tmp457
	cmpleps	%xmm0, %xmm14	#, vect__50.90, tmp457
	movaps	%xmm14, %xmm15	# tmp457, tmp458
	pslld	$31, %xmm14	#, tmp461
	andps	%xmm3, %xmm15	# tmp743, tmp458
	subps	%xmm15, %xmm0	# tmp458, tmp459
	cvttps2dq	%xmm0, %xmm0	# tmp459, tmp462
	pxor	%xmm0, %xmm14	# tmp462, vect_z_code_53.95
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movdqa	%xmm14, %xmm15	# vect_z_code_53.95, tmp464
	psrld	$16, %xmm14	#, tmp465
	cvtdq2ps	%xmm14, %xmm14	# tmp465, tmp467
	mulps	%xmm7, %xmm14	# tmp745, tmp469
	pand	%xmm4, %xmm15	# tmp744, tmp464
	cvtdq2ps	%xmm15, %xmm0	# tmp464, tmp466
	addps	%xmm14, %xmm0	# tmp469, vect__60.102
# ../include/FastBVH/impl/MortonCurve.inl:96:       z_code = min(z_code, morton_domain - 1);
	movaps	%xmm3, %xmm14	# tmp743, tmp471
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minps	%xmm6, %xmm0	# tmp746, vect__60.102
# ../include/FastBVH/impl/MortonCurve.inl:96:       z_code = min(z_code, morton_domain - 1);
	cmpleps	%xmm0, %xmm14	#, vect__60.102, tmp471
	movaps	%xmm14, %xmm15	# tmp471, tmp472
	pslld	$31, %xmm14	#, tmp475
	andps	%xmm3, %xmm15	# tmp743, tmp472
	subps	%xmm15, %xmm0	# tmp472, tmp473
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movdqa	%xmm1, %xmm15	# vect_y_code_59.101, vect__128.118
	pslld	$16, %xmm15	#, vect__128.118
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	por	%xmm15, %xmm1	# vect__128.118, vect__129.119
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	pand	%xmm13, %xmm1	# tmp747, vect_n_130.120
# ../include/FastBVH/impl/MortonCurve.inl:96:       z_code = min(z_code, morton_domain - 1);
	cvttps2dq	%xmm0, %xmm0	# tmp473, tmp476
	pxor	%xmm0, %xmm14	# tmp476, vect_z_code_62.104
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movdqa	%xmm2, %xmm0	# vect_x_code_56.98, vect__115.105
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movdqa	%xmm1, %xmm15	# vect_n_130.120, vect__131.121
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	pslld	$16, %xmm0	#, vect__115.105
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	pslld	$8, %xmm15	#, vect__131.121
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	por	%xmm0, %xmm2	# vect__115.105, vect__116.106
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	por	%xmm15, %xmm1	# vect__131.121, vect__132.122
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	pand	%xmm13, %xmm2	# tmp747, vect_n_117.107
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	pand	%xmm12, %xmm1	# tmp748, vect_n_133.123
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movdqa	%xmm2, %xmm0	# vect_n_117.107, vect__118.108
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movdqa	%xmm1, %xmm15	# vect_n_133.123, vect__134.124
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	pslld	$8, %xmm0	#, vect__118.108
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	pslld	$4, %xmm15	#, vect__134.124
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	por	%xmm0, %xmm2	# vect__118.108, vect__119.109
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	por	%xmm1, %xmm15	# vect_n_133.123, vect__135.125
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movdqa	%xmm14, %xmm1	# vect_z_code_62.104, vect__142.132
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	pand	%xmm12, %xmm2	# tmp748, vect_n_120.110
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	pslld	$16, %xmm1	#, vect__142.132
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movdqa	%xmm2, %xmm0	# vect_n_120.110, vect__121.111
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	pand	%xmm11, %xmm15	# tmp749, vect_n_136.126
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	por	%xmm1, %xmm14	# vect__142.132, vect__143.133
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	pslld	$4, %xmm0	#, vect__121.111
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	pand	%xmm13, %xmm14	# tmp747, vect_n_144.134
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	por	%xmm0, %xmm2	# vect__121.111, vect__122.112
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movdqa	%xmm14, %xmm1	# vect_n_144.134, vect__145.135
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	pand	%xmm11, %xmm2	# tmp749, vect_n_123.113
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	pslld	$8, %xmm1	#, vect__145.135
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	movdqa	%xmm2, %xmm0	# vect_n_123.113, vect__124.114
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	por	%xmm1, %xmm14	# vect__145.135, vect__146.136
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	pslld	$2, %xmm0	#, vect__124.114
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	pand	%xmm12, %xmm14	# tmp748, vect_n_147.137
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	por	%xmm2, %xmm0	# vect_n_123.113, vect__125.115
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movdqa	%xmm14, %xmm1	# vect_n_147.137, vect__148.138
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	pslld	$2, %xmm0	#, vect__126.116
	pand	.LC9(%rip), %xmm0	#, vect__127.117
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	pslld	$4, %xmm1	#, vect__148.138
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	por	%xmm1, %xmm14	# vect__148.138, vect__149.139
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	movdqa	%xmm15, %xmm1	# vect_n_136.126, vect__137.127
	pslld	$2, %xmm1	#, vect__137.127
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	pand	%xmm11, %xmm14	# tmp749, vect_n_150.140
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	por	%xmm15, %xmm1	# vect_n_136.126, vect__138.128
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	pslld	$1, %xmm1	#, vect__139.129
	pand	.LC8(%rip), %xmm1	#, vect__140.130
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	por	%xmm0, %xmm1	# vect__127.117, vect__141.131
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	movdqa	%xmm14, %xmm0	# vect_n_150.140, vect__151.141
	pslld	$2, %xmm0	#, vect__151.141
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	por	%xmm0, %xmm14	# vect__151.141, vect__152.142
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	pand	.LC10(%rip), %xmm14	#, vect_n_153.143
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	por	%xmm14, %xmm1	# vect_n_153.143, vect__154.144
# ../include/FastBVH/impl/MortonCurve.inl:98:       batch_codes[j] = codec(x_code, y_code, z_code);
	movaps	%xmm1, (%rsi,%rax)	# vect__154.144, MEM[symbol: batch_codes, index: ivtmp.152_39, offset: 0B]
	addq	$16, %rax	#, ivtmp.152
	cmpq	%rax, %rcx	# ivtmp.152, _209
	jne	.L7	#,
	movq	%rdi, %rax	# _155, niters_vector_mult_vf.70
	andq	$-4, %rax	#, niters_vector_mult_vf.70
	testb	$3, %dil	#, _155
	je	.L8	#,
.L6:
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	128(%rsp,%rax,4), %xmm2	# center_x, tmp522
	movss	80(%rsp), %xmm8	# %sfp, _40
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	88(%rsp), %xmm9	# %sfp, x_factor
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	76(%rsp), %xmm10	# %sfp, _44
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	subss	%xmm8, %xmm2	# _40, tmp521
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	84(%rsp), %xmm15	# %sfp, y_factor
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	1152(%rsp,%rax,4), %xmm1	# center_y, tmp524
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	2176(%rsp,%rax,4), %xmm0	# center_z, tmp526
	movss	72(%rsp), %xmm14	# %sfp, _48
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	subss	%xmm10, %xmm1	# _44, tmp523
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movss	.LC11(%rip), %xmm5	#, tmp733
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	mulss	%xmm9, %xmm2	# x_factor, _43
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	subss	%xmm14, %xmm0	# _48, tmp525
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	mulss	92(%rsp), %xmm0	# %sfp, _53
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	mulss	%xmm15, %xmm1	# y_factor, _49
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	%xmm2, 128(%rsp,%rax,4)	# _43, center_x
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	cvttss2siq	%xmm2, %rcx	# _43, tmp528
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm2, %xmm2	# _59
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	%xmm0, 2176(%rsp,%rax,4)	# _53, center_z
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	%xmm1, 1152(%rsp,%rax,4)	# _49, center_y
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp528, x_code
	cvtsi2ssq	%rcx, %xmm2	# x_code, _59
# ../include/FastBVH/impl/MortonCurve.inl:91:       Code y_code = Code(center_y[j]);
	cvttss2siq	%xmm1, %rcx	# _49, tmp536
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm1, %xmm1	# _62
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm2	# tmp733, _59
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp536, y_code
	cvtsi2ssq	%rcx, %xmm1	# y_code, _62
# ../include/FastBVH/impl/MortonCurve.inl:92:       Code z_code = Code(center_z[j]);
	cvttss2siq	%xmm0, %rcx	# _53, tmp544
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm0, %xmm0	# _117
# ../include/FastBVH/impl/MortonCurve.inl:94:       x_code = min(x_code, morton_domain - 1);
	cvttss2siq	%xmm2, %r9	# _59, tmp534
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm1	# tmp733, _62
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp544, z_code
	cvtsi2ssq	%rcx, %xmm0	# z_code, _117
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r9d, %r13d	# tmp534, tmp551
	sall	$16, %r13d	#, tmp551
# ../include/FastBVH/impl/MortonCurve.inl:95:       y_code = min(y_code, morton_domain - 1);
	cvttss2siq	%xmm1, %r8	# _62, tmp542
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r13d, %r9d	# tmp551, tmp552
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %r9d	#, tmp552
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm0	# tmp733, _117
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r9d, %r13d	# tmp552, n
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r9d	#, tmp553
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%r13d, %r9d	# n, _123
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r8d, %r10d	# tmp542, tmp555
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %r9d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	sall	$16, %r10d	#, tmp555
# ../include/FastBVH/impl/MortonCurve.inl:96:       z_code = min(z_code, morton_domain - 1);
	cvttss2siq	%xmm0, %rcx	# _117, tmp550
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r9d, %r13d	# n, tmp554
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r10d, %r8d	# tmp555, tmp556
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	sall	$4, %r13d	#, tmp554
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r8d, %r10d	# tmp556, tmp556
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%r9d, %r13d	# n, _126
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %r10d	#, tmp556
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%r10d, %r8d	# n, tmp557
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r13d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%ecx, %r9d	# tmp550, tmp559
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r8d	#, tmp557
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	sall	$16, %r9d	#, tmp559
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%r10d, %r8d	# n, _136
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r9d, %ecx	# tmp559, tmp560
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %r8d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %ecx	#, n
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r8d, %r10d	# n, tmp558
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%ecx, %r9d	# n, tmp561
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	sall	$4, %r10d	#, tmp558
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r9d	#, tmp561
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%r10d, %r8d	# tmp558, _139
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%ecx, %r9d	# n, _150
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r8d, %r10d	# _139, _139
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%r9d, %ecx	# _150, _150
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r10d	#, _139
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %ecx	#, _150
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r10,4), %r8d	#, tmp568
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%ecx, %r9d	# n, tmp562
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%r10d, %r8d	# n, tmp569
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	sall	$4, %r9d	#, tmp562
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	addl	%r8d, %r8d	# tmp570
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%ecx, %r9d	# n, _153
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r9d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r9,4), %ecx	#, tmp563
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%ecx, %r9d	# tmp563, _254
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r13,4), %ecx	#, tmp564
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%ecx, %r13d	# tmp564, tmp565
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	leal	0(,%r13,4), %ecx	#, tmp566
	andl	$613566756, %ecx	#, tmp567
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	andl	$306783378, %r8d	#, tmp571
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	andl	$153391689, %r9d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	orl	%r8d, %ecx	# tmp571, tmp572
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	orl	%r9d, %ecx	# n, tmp574
# ../include/FastBVH/impl/MortonCurve.inl:84:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	leaq	1(%rax), %r9	#, j
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	movl	%ecx, 3200(%rsp,%rax,4)	# tmp574, batch_codes
# ../include/FastBVH/impl/MortonCurve.inl:84:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	cmpq	%rdi, %r9	# _155, j
	jnb	.L8	#,
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	128(%rsp,%r9,4), %xmm2	# center_x, tmp576
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	1152(%rsp,%r9,4), %xmm1	# center_y, tmp578
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	2176(%rsp,%r9,4), %xmm0	# center_z, tmp580
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	subss	%xmm8, %xmm2	# _40, tmp575
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	subss	%xmm10, %xmm1	# _44, tmp577
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	subss	%xmm14, %xmm0	# _48, tmp579
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	mulss	92(%rsp), %xmm0	# %sfp, _304
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	mulss	%xmm9, %xmm2	# x_factor, _26
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	mulss	%xmm15, %xmm1	# y_factor, _331
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	%xmm0, 2176(%rsp,%r9,4)	# _304, center_z
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	%xmm2, 128(%rsp,%r9,4)	# _26, center_x
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	cvttss2siq	%xmm2, %rcx	# _26, tmp582
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm2, %xmm2	# _21
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	%xmm1, 1152(%rsp,%r9,4)	# _331, center_y
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp582, x_code
	cvtsi2ssq	%rcx, %xmm2	# x_code, _21
# ../include/FastBVH/impl/MortonCurve.inl:91:       Code y_code = Code(center_y[j]);
	cvttss2siq	%xmm1, %rcx	# _331, tmp590
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm1, %xmm1	# _105
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm2	# tmp733, _21
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp590, y_code
	cvtsi2ssq	%rcx, %xmm1	# y_code, _105
# ../include/FastBVH/impl/MortonCurve.inl:94:       x_code = min(x_code, morton_domain - 1);
	cvttss2siq	%xmm2, %r10	# _21, tmp588
# ../include/FastBVH/impl/MortonCurve.inl:92:       Code z_code = Code(center_z[j]);
	cvttss2siq	%xmm0, %rcx	# _304, tmp598
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm0, %xmm0	# _336
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm1	# tmp733, _105
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r10d, %r13d	# tmp588, tmp605
	sall	$16, %r13d	#, tmp605
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp598, z_code
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r13d, %r10d	# tmp605, tmp606
# ../include/FastBVH/impl/MortonCurve.inl:95:       y_code = min(y_code, morton_domain - 1);
	cvttss2siq	%xmm1, %r8	# _105, tmp596
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %r10d	#, tmp606
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	cvtsi2ssq	%rcx, %xmm0	# z_code, _336
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r10d, %r13d	# tmp606, n
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r10d	#, tmp607
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%r13d, %r10d	# n, _342
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %r10d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r10d, %r13d	# n, tmp608
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm0	# tmp733, _336
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	sall	$4, %r13d	#, tmp608
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%r13d, %r10d	# tmp608, _345
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r8d, %r13d	# tmp596, tmp609
	sall	$16, %r13d	#, tmp609
# ../include/FastBVH/impl/MortonCurve.inl:96:       z_code = min(z_code, morton_domain - 1);
	cvttss2siq	%xmm0, %rcx	# _336, tmp604
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r10d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r13d, %r8d	# tmp609, tmp610
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %r8d	#, tmp610
	movl	%r8d, %r13d	# tmp610, n
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r8d	#, tmp611
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%r13d, %r8d	# n, _355
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %r8d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r8d, %r13d	# n, tmp612
	sall	$4, %r13d	#, tmp612
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%r13d, %r8d	# tmp612, _358
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%ecx, %r13d	# tmp604, tmp613
	sall	$16, %r13d	#, tmp613
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r8d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r13d, %ecx	# tmp613, tmp614
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %ecx	#, n
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%ecx, %r13d	# n, tmp615
	sall	$8, %r13d	#, tmp615
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%ecx, %r13d	# n, _369
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%r13d, %ecx	# _369, _369
	andl	$50393103, %ecx	#, _369
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%ecx, %r13d	# n, tmp616
	sall	$4, %r13d	#, tmp616
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%ecx, %r13d	# n, _372
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r13d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r13,4), %ecx	#, tmp617
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%ecx, %r13d	# tmp617, _375
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r10,4), %ecx	#, tmp618
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%ecx, %r10d	# tmp618, tmp619
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	leal	0(,%r10,4), %ecx	#, tmp620
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r8,4), %r10d	#, tmp622
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%r10d, %r8d	# tmp622, tmp623
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	andl	$613566756, %ecx	#, tmp621
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	addl	%r8d, %r8d	# tmp624
	andl	$306783378, %r8d	#, tmp625
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	andl	$153391689, %r13d	#, n
# ../include/FastBVH/impl/MortonCurve.inl:84:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	addq	$2, %rax	#, j
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	orl	%r8d, %ecx	# tmp625, tmp626
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	orl	%r13d, %ecx	# n, tmp628
	movl	%ecx, 3200(%rsp,%r9,4)	# tmp628, batch_codes
# ../include/FastBVH/impl/MortonCurve.inl:84:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	cmpq	%rax, %rdi	# j, _155
	jbe	.L8	#,
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	128(%rsp,%rax,4), %xmm1	# center_x, tmp630
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	1152(%rsp,%rax,4), %xmm2	# center_y, tmp632
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	2176(%rsp,%rax,4), %xmm0	# center_z, tmp634
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	subss	%xmm8, %xmm1	# _40, tmp629
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	subss	%xmm10, %xmm2	# _44, tmp631
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	subss	%xmm14, %xmm0	# _48, tmp633
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	mulss	92(%rsp), %xmm0	# %sfp, _321
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	mulss	%xmm9, %xmm1	# x_factor, _70
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	mulss	%xmm15, %xmm2	# y_factor, _325
# ../include/FastBVH/impl/MortonCurve.inl:88:       center_z[j] = (center_z[j] - bbox.min.z) * z_factor;
	movss	%xmm0, 2176(%rsp,%rax,4)	# _321, center_z
# ../include/FastBVH/impl/MortonCurve.inl:86:       center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
	movss	%xmm1, 128(%rsp,%rax,4)	# _70, center_x
# ../include/FastBVH/impl/MortonCurve.inl:90:       Code x_code = Code(center_x[j]);
	cvttss2siq	%xmm1, %rcx	# _70, tmp636
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm1, %xmm1	# _315
# ../include/FastBVH/impl/MortonCurve.inl:87:       center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
	movss	%xmm2, 1152(%rsp,%rax,4)	# _325, center_y
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp636, x_code
	cvtsi2ssq	%rcx, %xmm1	# x_code, _315
# ../include/FastBVH/impl/MortonCurve.inl:91:       Code y_code = Code(center_y[j]);
	cvttss2siq	%xmm2, %rcx	# _325, tmp644
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm1	# tmp733, _315
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp644, y_code
# ../include/FastBVH/impl/MortonCurve.inl:94:       x_code = min(x_code, morton_domain - 1);
	cvttss2siq	%xmm1, %r9	# _315, tmp642
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm1, %xmm1	# _302
	cvtsi2ssq	%rcx, %xmm1	# y_code, _302
# ../include/FastBVH/impl/MortonCurve.inl:92:       Code z_code = Code(center_z[j]);
	cvttss2siq	%xmm0, %rcx	# _321, tmp652
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	pxor	%xmm0, %xmm0	# _299
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r9d, %r10d	# tmp642, tmp659
	sall	$16, %r10d	#, tmp659
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm1	# tmp733, _302
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	movl	%ecx, %ecx	# tmp652, z_code
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r10d, %r9d	# tmp659, tmp660
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	cvtsi2ssq	%rcx, %xmm0	# z_code, _299
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r9d, %r10d	# tmp660, tmp660
	andl	$50331903, %r10d	#, tmp660
# ../include/FastBVH/impl/MortonCurve.inl:95:       y_code = min(y_code, morton_domain - 1);
	cvttss2siq	%xmm1, %r8	# _302, tmp650
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%r10d, %r9d	# n, tmp661
	sall	$8, %r9d	#, tmp661
# ../include/FastBVH/impl/MortonCurve.inl:53:   auto min = [](auto a, auto b) { return (a < b) ? a : b; };
	minss	%xmm5, %xmm0	# tmp733, _299
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%r10d, %r9d	# n, _293
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %r9d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%r8d, %r13d	# tmp650, tmp663
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r9d, %r10d	# n, tmp662
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	sall	$16, %r13d	#, tmp663
# ../include/FastBVH/impl/MortonCurve.inl:96:       z_code = min(z_code, morton_domain - 1);
	cvttss2siq	%xmm0, %rcx	# _299, tmp658
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	sall	$4, %r10d	#, tmp662
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r13d, %r8d	# tmp663, tmp664
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%r9d, %r10d	# n, _289
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %r8d	#, tmp664
	movl	%r8d, %r13d	# tmp664, n
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r8d	#, tmp665
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r10d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%r13d, %r8d	# n, _279
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	movl	%ecx, %r9d	# tmp658, tmp667
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	andl	$50393103, %r8d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	sall	$16, %r9d	#, tmp667
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%r8d, %r13d	# n, tmp666
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	orl	%r9d, %ecx	# tmp667, tmp668
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	sall	$4, %r13d	#, tmp666
# ../include/FastBVH/impl/MortonCodec.inl:14:   n = (n | (n << 16)) & 0x030000ff;
	andl	$50331903, %ecx	#, n
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%r8d, %r13d	# n, _276
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r10,4), %r8d	#, tmp676
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%ecx, %r9d	# n, tmp669
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r13d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%r10d, %r8d	# n, tmp677
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	sall	$8, %r9d	#, tmp669
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	sall	$2, %r8d	#, tmp678
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	orl	%ecx, %r9d	# n, _265
# ../include/FastBVH/impl/MortonCodec.inl:15:   n = (n | (n << 8)) & 0x0300f00f;
	movl	%r9d, %ecx	# _265, _265
	andl	$50393103, %ecx	#, _265
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	movl	%ecx, %r9d	# n, tmp670
	sall	$4, %r9d	#, tmp670
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	orl	%ecx, %r9d	# n, _262
# ../include/FastBVH/impl/MortonCodec.inl:16:   n = (n | (n << 4)) & 0x030c30c3;
	andl	$51130563, %r9d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r9,4), %ecx	#, tmp671
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%ecx, %r9d	# tmp671, _259
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	leal	0(,%r13,4), %ecx	#, tmp672
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	orl	%ecx, %r13d	# tmp672, tmp673
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	leal	(%r13,%r13), %ecx	#, tmp674
	andl	$306783378, %ecx	#, tmp675
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	andl	$613566756, %r8d	#, tmp679
# ../include/FastBVH/impl/MortonCodec.inl:17:   n = (n | (n << 2)) & 0x09249249;
	andl	$153391689, %r9d	#, n
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	orl	%r8d, %ecx	# tmp679, tmp680
# ../include/FastBVH/impl/MortonCodec.inl:10:   return (expand(x) << 2) | (expand(y) << 1) | expand(z);
	orl	%r9d, %ecx	# n, tmp682
	movl	%ecx, 3200(%rsp,%rax,4)	# tmp682, batch_codes
.L8:
	movq	64(%rsp), %rax	# %sfp, _12
	leaq	(%rax,%rdx), %rcx	#, tmp683
# ../include/FastBVH/impl/MortonCurve.inl:103:       codes[i + j] = batch_codes[j];
	leaq	0(,%rdi,4), %rax	#, tmp684
	cmpl	$8, %eax	#, tmp684
	jnb	.L27	#,
	testb	$4, %al	#, tmp684
	jne	.L49	#,
	testl	%eax, %eax	# tmp684
	je	.L28	#,
	movzbl	(%rsi), %eax	#, tmp698
	movb	%al, (%rcx)	# tmp698,
.L28:
	addq	$1024, %rdx	#, ivtmp.174
# ../include/FastBVH/impl/MortonCurve.inl:71:   for (decltype(count) i = 0; i < count; i += batch_size_max) {
	cmpq	%r11, %r12	# _16, _14
	ja	.L31	#,
	.p2align 4,,10
	.p2align 3
.L1:
# ../include/FastBVH/impl/MortonCurve.inl:108: }
	movq	4280(%rsp), %rax	# D.16764, tmp790
	xorq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp790
	jne	.L50	#,
	movq	48(%rsp), %rax	# %sfp,
	leaq	-40(%rbp), %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%r13	#
	popq	%r14	#
	popq	%r15	#
	popq	%rbp	#
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret	
	.p2align 4,,10
	.p2align 3
.L27:
	.cfi_restore_state
	movq	(%rsi), %rdi	#, tmp707
	movq	%rdi, (%rcx)	# tmp707,
	movl	%eax, %edi	# tmp684, tmp708
	movq	-8(%rsi,%rdi), %r8	#, tmp714
	movq	%r8, -8(%rcx,%rdi)	# tmp714,
	leaq	8(%rcx), %rdi	#, tmp715
	andq	$-8, %rdi	#, tmp715
	subq	%rdi, %rcx	# tmp715, tmp687
	subq	%rcx, %rsi	# tmp687, tmp688
	addl	%eax, %ecx	# tmp684, tmp686
	movl	%ecx, %eax	# tmp686, tmp686
	shrl	$3, %eax	#, tmp686
	movl	%eax, %ecx	# tmp716, tmp717
	rep movsq
	jmp	.L28	#
	.p2align 4,,10
	.p2align 3
.L33:
# ../include/FastBVH/impl/MortonCurve.inl:73:     auto batch_size = ((i + batch_size_max) < count) ? batch_size_max : (count - i);
	movl	$256, %edi	#, _155
	jmp	.L4	#
.L34:
# ../include/FastBVH/impl/MortonCurve.inl:84:     for (decltype(batch_size) j = 0; j < batch_size; j++) {
	xorl	%eax, %eax	# niters_vector_mult_vf.70
	leaq	3200(%rsp), %rsi	#, tmp730
	jmp	.L6	#
.L49:
	movl	(%rsi), %edi	#, tmp690
	movl	%eax, %eax	# tmp684, tmp691
	movl	%edi, (%rcx)	# tmp690,
	movl	-4(%rsi,%rax), %esi	#, tmp697
	movl	%esi, -4(%rcx,%rax)	# tmp697,
	jmp	.L28	#
.L50:
# ../include/FastBVH/impl/MortonCurve.inl:108: }
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE655:
	.size	_ZN7FastBVH4impl11MortonCurveIfEclIiZ16generateMorton32PKfS5_S5_PKimEUliE_EENS0_5ArrayIjEERKNS_13ConstIterableIT_EET0_RKNS_4BBoxIfEE.isra.0.constprop.0, .-_ZN7FastBVH4impl11MortonCurveIfEclIiZ16generateMorton32PKfS5_S5_PKimEUliE_EENS0_5ArrayIjEERKNS_13ConstIterableIT_EET0_RKNS_4BBoxIfEE.isra.0.constprop.0
	.p2align 4
	.globl	_Z16generateMorton32PKfS0_S0_PKim
	.type	_Z16generateMorton32PKfS0_S0_PKim, @function
_Z16generateMorton32PKfS0_S0_PKim:
.LFB618:
	.cfi_startproc
	endbr64	
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
# MortonCurve.cpp:27:   };
	movq	%rdx, %xmm1	# tmp105, tmp105
	movq	%rsi, %xmm0	# tmp104, tmp92
# MortonCurve.cpp:10:                             Size count) {
	movq	%rdi, %r12	# tmp103, <retval>
# MortonCurve.cpp:27:   };
	punpcklqdq	%xmm1, %xmm0	# tmp105, tmp92
# MortonCurve.cpp:10:                             Size count) {
	subq	$112, %rsp	#,
	.cfi_def_cfa_offset 128
# MortonCurve.cpp:10:                             Size count) {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp109
	movq	%rax, 104(%rsp)	# tmp109, D.16772
	xorl	%eax, %eax	# tmp109
# MortonCurve.cpp:45:   return curve(ConstIterable<int>(spheres, count), sphereToBox, scene_bbox);
	leaq	48(%rsp), %rdx	#, tmp99
# MortonCurve.cpp:27:   };
	movq	%rcx, 32(%rsp)	# tmp106, sphereToBox.__vertices_z
# MortonCurve.cpp:45:   return curve(ConstIterable<int>(spheres, count), sphereToBox, scene_bbox);
	movq	%rsp, %rsi	#, tmp100
# ../include/FastBVH/BBox.h:37:   inline constexpr BBox(const Vec3& min, const Vec3& max) noexcept : min(min), max(max), extent(max - min) {}
	movabsq	$-4323455638987341824, %rax	#, tmp113
# ../include/FastBVH/Iterable.h:60:   constexpr ConstIterable(const T* a, Size c) noexcept : array(a), count(c) {}
	movq	%r8, (%rsp)	# tmp107, D.16131.array
# MortonCurve.cpp:45:   return curve(ConstIterable<int>(spheres, count), sphereToBox, scene_bbox);
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 136
# ../include/FastBVH/BBox.h:37:   inline constexpr BBox(const Vec3& min, const Vec3& max) noexcept : min(min), max(max), extent(max - min) {}
	movq	%rax, 56(%rsp)	# tmp113, MEM[(struct Vector3 *)&scene_bbox]
	movabsq	$4899916395719950336, %rax	#, tmp114
	movq	%rax, 72(%rsp)	# tmp114, MEM[(struct Vector3 *)&scene_bbox + 16B]
# ../include/FastBVH/BBox.h:37:   inline constexpr BBox(const Vec3& min, const Vec3& max) noexcept : min(min), max(max), extent(max - min) {}
	movabsq	$4935945192747302912, %rax	#, tmp115
# MortonCurve.cpp:27:   };
	movaps	%xmm0, 24(%rsp)	# tmp92, MEM[(const float * *)&sphereToBox]
# ../include/FastBVH/BBox.h:37:   inline constexpr BBox(const Vec3& min, const Vec3& max) noexcept : min(min), max(max), extent(max - min) {}
	movl	$0xc4000000, 64(%rsp)	#, MEM[(struct Vector3 *)&scene_bbox + 8B]
	movl	$0x44000000, 80(%rsp)	#, MEM[(struct Vector3 *)&scene_bbox + 24B]
# ../include/FastBVH/BBox.h:37:   inline constexpr BBox(const Vec3& min, const Vec3& max) noexcept : min(min), max(max), extent(max - min) {}
	movq	%rax, 88(%rsp)	# tmp115, MEM[(struct BBox *)&scene_bbox + 32B]
	movl	$0x44800000, 96(%rsp)	#, MEM[(struct BBox *)&scene_bbox + 40B]
# ../include/FastBVH/Iterable.h:60:   constexpr ConstIterable(const T* a, Size c) noexcept : array(a), count(c) {}
	movq	%r9, 16(%rsp)	# tmp108, D.16131.count
# MortonCurve.cpp:45:   return curve(ConstIterable<int>(spheres, count), sphereToBox, scene_bbox);
	pushq	40(%rsp)	#
	.cfi_def_cfa_offset 144
	pushq	40(%rsp)	#
	.cfi_def_cfa_offset 152
	pushq	40(%rsp)	# sphereToBox
	.cfi_def_cfa_offset 160
	call	_ZN7FastBVH4impl11MortonCurveIfEclIiZ16generateMorton32PKfS5_S5_PKimEUliE_EENS0_5ArrayIjEERKNS_13ConstIterableIT_EET0_RKNS_4BBoxIfEE.isra.0.constprop.0	#
	addq	$32, %rsp	#,
	.cfi_def_cfa_offset 128
# MortonCurve.cpp:46: }
	movq	104(%rsp), %rax	# D.16772, tmp110
	xorq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp110
	jne	.L54	#,
	addq	$112, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%r12, %rax	# <retval>,
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
.L54:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE618:
	.size	_Z16generateMorton32PKfS0_S0_PKim, .-_Z16generateMorton32PKfS0_S0_PKim
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1149239296
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	1325400064
	.long	1325400064
	.long	1325400064
	.long	1325400064
	.align 16
.LC2:
	.long	65535
	.long	65535
	.long	65535
	.long	65535
	.align 16
.LC3:
	.long	1199570944
	.long	1199570944
	.long	1199570944
	.long	1199570944
	.align 16
.LC4:
	.long	1149222912
	.long	1149222912
	.long	1149222912
	.long	1149222912
	.align 16
.LC5:
	.long	50331903
	.long	50331903
	.long	50331903
	.long	50331903
	.align 16
.LC6:
	.long	50393103
	.long	50393103
	.long	50393103
	.long	50393103
	.align 16
.LC7:
	.long	51130563
	.long	51130563
	.long	51130563
	.long	51130563
	.align 16
.LC8:
	.long	306783378
	.long	306783378
	.long	306783378
	.long	306783378
	.align 16
.LC9:
	.long	613566756
	.long	613566756
	.long	613566756
	.long	613566756
	.align 16
.LC10:
	.long	153391689
	.long	153391689
	.long	153391689
	.long	153391689
	.section	.rodata.cst4
	.align 4
.LC11:
	.long	1149222912
	.ident	"GCC: (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
