PROJNAME = im
LIBNAME = im_fftw3
OPT = YES

DEF_FILE = im_fftw.def

RDFT_CODELETS_R2R = e01_8.c e10_8.c rrcodlist.c
RDFT_CODELETS_R2R := $(addprefix r2r/, $(RDFT_CODELETS_R2R))

R2HC = r2hc_2.c r2hc_3.c r2hc_4.c r2hc_5.c r2hc_6.c r2hc_7.c r2hc_8.c	\
  r2hc_9.c r2hc_10.c r2hc_11.c r2hc_12.c r2hc_13.c r2hc_14.c r2hc_15.c	\
  r2hc_16.c r2hc_32.c 
MR2HC = mr2hc_32.c mr2hc_64.c mr2hc_128.c
HF = hf_2.c hf_3.c hf_4.c hf_5.c hf_6.c hf_7.c hf_8.c hf_9.c	\
  hf_10.c hf_12.c hf_15.c hf_16.c hf_32.c hf_64.c
HF2 = hf2_4.c hf2_8.c hf2_16.c hf2_32.c hf2_64.c
R2HCII = r2hcII_2.c r2hcII_3.c r2hcII_4.c r2hcII_5.c r2hcII_6.c		\
  r2hcII_7.c r2hcII_8.c r2hcII_9.c r2hcII_10.c r2hcII_12.c r2hcII_15.c	\
  r2hcII_16.c r2hcII_32.c
MR2HCII =  mr2hcII_32.c mr2hcII_64.c
RDFT_CODELETS_R2HC = $(R2HC) $(MR2HC) $(HF) $(HF2) $(R2HCII) $(MR2HCII) rhcodlist.c 
RDFT_CODELETS_R2HC := $(addprefix r2hc/, $(RDFT_CODELETS_R2HC))

HC2R = hc2r_3.c hc2r_4.c hc2r_5.c hc2r_6.c hc2r_7.c hc2r_8.c hc2r_9.c	\
  hc2r_10.c hc2r_11.c hc2r_12.c hc2r_13.c hc2r_14.c hc2r_15.c hc2r_16.c	\
  hc2r_32.c
MHC2R = mhc2r_32.c mhc2r_64.c mhc2r_128.c
HB = hb_2.c hb_3.c hb_4.c hb_5.c hb_6.c hb_7.c hb_8.c hb_9.c	\
  hb_10.c hb_12.c hb_15.c hb_16.c hb_32.c hb_64.c
HB2 = hb2_4.c hb2_8.c hb2_16.c hb2_32.c hb2_64.c
HC2RIII = hc2rIII_2.c hc2rIII_3.c hc2rIII_4.c hc2rIII_5.c hc2rIII_6.c	\
  hc2rIII_7.c hc2rIII_8.c hc2rIII_9.c hc2rIII_10.c hc2rIII_12.c		\
  hc2rIII_15.c hc2rIII_16.c hc2rIII_32.c
MHC2RIII = mhc2rIII_32.c mhc2rIII_64.c
RDFT_CODELETS_HC2R = $(HC2R) $(MHC2R) $(HB) $(HC2RIII) $(MHC2RIII) hcodlist.c
RDFT_CODELETS_HC2R := $(addprefix hc2r/, $(RDFT_CODELETS_HC2R))

RDFT_CODELETS = hc2r.c hfb.c	\
  r2hc.c r2r.c $(RDFT_CODELETS_R2R) $(RDFT_CODELETS_HC2R) $(RDFT_CODELETS_R2HC)
RDFT_CODELETS := $(addprefix codelets/, $(RDFT_CODELETS))

RDFT2 = buffered2.c direct2.c nop2.c rank0-rdft2.c rank-geq2-rdft2.c	\
  plan2.c problem2.c solve2.c vrank-geq1-rdft2.c rdft2-radix2.c		\
  rdft2-tensor-max-index.c rdft2-inplace-strides.c rdft2-strides.c
RDFT = dft-r2hc.c dht-r2hc.c dht-rader.c rbuffered.c	\
  rconf.c rdirect.c rgeneric.c khc2hc-dif.c khc2hc-dit.c	\
  khc2r.c kr2hc.c kr2r.c hc2hc.c hc2hc-dif.c hc2hc-dit.c		\
  hc2hc-buf.c rindirect.c rnop.c rplan.c rproblem.c rader-hc2hc.c rrank0.c	\
  rrank-geq2.c rdft-dht.c rsolve.c rvrank-geq1.c $(RDFT2) $(RDFT_CODELETS)
RDFT  := $(addprefix rdft/, $(RDFT))

N1 = n1_2.c n1_3.c n1_4.c n1_5.c n1_6.c n1_7.c n1_8.c n1_9.c n1_10.c	\
  n1_11.c n1_12.c n1_13.c n1_14.c n1_15.c n1_16.c
M1 = m1_16.c m1_32.c m1_64.c
T1 = t1_2.c t1_3.c t1_4.c t1_5.c t1_6.c t1_7.c t1_8.c t1_9.c	\
  t1_10.c t1_12.c t1_15.c t1_16.c t1_32.c t1_64.c
T2 = t2_4.c t2_8.c t2_16.c t2_32.c t2_64.c
DFT_CODELETS_STANDARD = $(N1) $(M1) $(T1) $(T2) scodlist.c
DFT_CODELETS_STANDARD  := $(addprefix standard/, $(DFT_CODELETS_STANDARD))

DFT_CODELETS_INPLACE = q1_2.c q1_4.c q1_8.c  q1_3.c q1_5.c q1_6.c icodlist.c
DFT_CODELETS_INPLACE := $(addprefix inplace/, $(DFT_CODELETS_INPLACE))

DFT_CODELETS = n.c t.c $(DFT_CODELETS_INPLACE) $(DFT_CODELETS_STANDARD)
DFT_CODELETS := $(addprefix codelets/, $(DFT_CODELETS))

DFT = buffered.c conf.c ct-dif.c ct-dit.c ct-ditbuf.c	\
  ct-ditf.c ct.c direct.c generic.c indirect.c kdft-dif.c kdft-difsq.c	\
  kdft-dit.c kdft.c nop.c plan.c problem.c rader.c rader-omega.c		\
  rank-geq2.c rank0.c solve.c vrank-geq1.c vrank2-transpose.c		\
  vrank3-transpose.c zero.c $(DFT_CODELETS)
DFT := $(addprefix dft/, $(DFT))

REODFT = reoconf.c reodft010e-r2hc.c	\
  reodft11e-radix2.c reodft11e-r2hc-odd.c redft00e-r2hc-pad.c	\
  rodft00e-r2hc-pad.c
REODFT := $(addprefix reodft/, $(REODFT))

KERNEL = align.c alloc.c assert.c awake.c kbuffered.c	\
  kct.c debug.c hash.c iabs.c md5.c md5-1.c minmax.c ops.c pickdim.c	\
  kplan.c planner.c primes.c print.c kproblem.c krader.c scan.c solver.c	\
  solvtab.c square.c stride.c tensor.c tensor1.c tensor2.c tensor4.c	\
  tensor5.c tensor7.c tensor8.c tensor9.c timer.c transpose.c trig.c	\
  trig1.c twiddle.c
KERNEL := $(addprefix kernel/, $(KERNEL))

API = apiplan.c configure.c execute.c execute-dft.c	\
  execute-dft-c2r.c execute-dft-r2c.c execute-r2r.c			\
  export-wisdom-to-file.c export-wisdom-to-string.c export-wisdom.c	\
  extract-reim.c flops.c forget-wisdom.c import-system-wisdom.c		\
  import-wisdom-from-file.c import-wisdom-from-string.c import-wisdom.c	\
  mapflags.c mkprinter-file.c mktensor-iodims.c mktensor-rowmajor.c	\
  plan-dft-1d.c plan-dft-2d.c plan-dft-3d.c plan-dft.c plan-guru-dft.c	\
  plan-many-dft.c plan-many-dft-c2r.c plan-dft-c2r.c plan-dft-c2r-1d.c	\
  plan-dft-c2r-2d.c plan-dft-c2r-3d.c plan-many-dft-r2c.c plan-dft-r2c.c	\
  plan-dft-r2c-1d.c plan-dft-r2c-2d.c plan-dft-r2c-3d.c			\
  plan-guru-dft-c2r.c plan-guru-dft-r2c.c map-r2r-kind.c plan-many-r2r.c	\
  plan-r2r-1d.c plan-r2r-2d.c plan-r2r-3d.c plan-r2r.c plan-guru-r2r.c	\
  print-plan.c the-planner.c rdft2-pad.c version.c \
  execute-split-dft-c2r.c execute-split-dft-r2c.c execute-split-dft.c	\
  plan-guru-split-dft-c2r.c plan-guru-split-dft-r2c.c	\
  plan-guru-split-dft.c f77api.c
API := $(addprefix api/, $(API))
	
SRC = $(API) $(REODFT) $(RDFT) $(DFT) $(KERNEL)
SRC := $(addprefix fftw3/, $(SRC))

SRC := process/im_fft.cpp $(SRC)

INCLUDES := ../include fftw3/kernel fftw3/dft fftw3/rdft fftw3/api \
  fftw3/reodft fftw3/rdft/codelets fftw3/dft/codelets

DEFINES = USE_FFTW3

USE_IM = Yes
IM = ..
LIBS = im_process


ifneq ($(findstring Win, $(TEC_SYSNAME)), )
  ifneq ($(findstring gcc, $(TEC_UNAME)), )
    DEFINES += HAVE_UINTPTR_T
  endif
  ifneq ($(findstring ow, $(TEC_UNAME)), )
    DEFINES += IM_DEFMATHFLOAT
  endif         
  ifneq ($(findstring bc, $(TEC_UNAME)), )
    DEFINES += IM_DEFMATHFLOAT
  endif
else
  ifneq ($(findstring IRIX, $(TEC_UNAME)), )
    DEFINES += HAVE_UINTPTR_T
  endif
  ifneq ($(findstring Darwin, $(TEC_UNAME)), )
    DEFINES += HAVE_UINTPTR_T
  endif
  ifneq ($(findstring FreeBSD, $(TEC_UNAME)), )
    DEFINES += HAVE_UINTPTR_T
  endif
  ifneq ($(findstring AIX, $(TEC_UNAME)), )
    DEFINES += IM_DEFMATHFLOAT HAVE_UINTPTR_T
  endif
  ifneq ($(findstring SunOS, $(TEC_UNAME)), )
    DEFINES += IM_DEFMATHFLOAT
  endif
endif

# Duplicated files: buffered.c conf.c direct.c indirect.c generic.c 
#                   nop.c plan.c problem.c rader.c rank0.c rank-geq2.c
#                   vrank-geq1.c solve.c ct.c codlist.c
# These were renamed to "r*" when in the rdft folder, and to "k*" when in the kernel folder.
