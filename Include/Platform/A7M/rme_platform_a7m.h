/******************************************************************************
Filename    : rme_platform_a7m.h
Author      : pry
Date        : 01/04/2017
Licence     : The Unlicense; see LICENSE for details.
Description : The header of "rme_platform_a7m.c".
******************************************************************************/

/* Defines *******************************************************************/
#ifdef __HDR_DEFS__
#ifndef __RME_PLATFORM_A7M_H_DEFS__
#define __RME_PLATFORM_A7M_H_DEFS__
/*****************************************************************************/
/* Basic Types ***************************************************************/
#ifndef __RME_S32_T__
#define __RME_S32_T__
typedef signed int rme_s32_t;
#endif

#ifndef __RME_S16_T__
#define __RME_S16_T__
typedef signed short rme_s16_t;
#endif

#ifndef __RME_S8_T__
#define __RME_S8_T__
typedef signed char rme_s8_t;
#endif

#ifndef __RME_U32_T__
#define __RME_U32_T__
typedef unsigned int rme_u32_t;
#endif

#ifndef __RME_U16_T__
#define __RME_U16_T__
typedef unsigned short rme_u16_t;
#endif

#ifndef __RME_U8_T__
#define __RME_U8_T__
typedef unsigned char rme_u8_t;
#endif
/* End Basic Types ***********************************************************/

/* Begin Extended Types ******************************************************/
#ifndef __RME_TID_T__
#define __RME_TID_T__
/* The typedef for the Thread ID */
typedef rme_s32_t rme_tid_t;
#endif

#ifndef __RME_PTR_T__
#define __RME_PTR_T__
/* The typedef for the pointers - This is the raw style. Pointers must be unsigned */
typedef rme_u32_t rme_ptr_t;
#endif

#ifndef __RME_CNT_T__
#define __RME_CNT_T__
/* The typedef for the count variables */
typedef rme_s32_t rme_cnt_t;
#endif

#ifndef __RME_CID_T__
#define __RME_CID_T__
/* The typedef for capability ID */
typedef rme_s32_t rme_cid_t;
#endif

#ifndef __RME_RET_T__
#define __RME_RET_T__
/* The type for process return value */
typedef rme_s32_t rme_ret_t;
#endif
/* End Extended Types ********************************************************/

/* System macros *************************************************************/
/* Compiler "extern" keyword setting */
#define EXTERN                          extern
/* Compiler "inline" keyword setting */
#define INLINE                          inline
/* Compiler likely & unlikely setting */
#ifdef likely
#define RME_LIKELY(X)                   (likely(X))
#else
#define RME_LIKELY(X)                   (X)
#endif
#ifdef unlikely
#define RME_UNLIKELY(X)                 (unlikely(X))
#else
#define RME_UNLIKELY(X)                 (X)
#endif
/* CPU-local data structure location macro */
#define RME_CPU_LOCAL()                 (&RME_A7M_Local)
/* The order of bits in one CPU machine word */
#define RME_WORD_ORDER                  5
/* Forcing VA=PA in user memory segments */
#define RME_VA_EQU_PA                   (1U)
/* Quiescence timeslice value */
#define RME_QUIE_TIME                   0
/* Captbl size limit - not restricted */
#define RME_CAPTBL_LIMIT                0
/* Normal page directory size calculation macro */
#define RME_PGTBL_SIZE_NOM(NUM_ORDER)   ((1<<(NUM_ORDER))*sizeof(rme_ptr_t)+sizeof(struct __RME_A7M_Pgtbl_Meta))
/* Top-level page directory size calculation macro */
#define RME_PGTBL_SIZE_TOP(NUM_ORDER)   (RME_PGTBL_SIZE_NOM(NUM_ORDER)+sizeof(struct __RME_A7M_MPU_Data))
/* The kernel object allocation table address - original */
#define RME_KOTBL                       RME_Kotbl
/* Compare-and-Swap(CAS) */
#define RME_COMP_SWAP(PTR,OLD,NEW)      __RME_A7M_Comp_Swap(PTR,OLD,NEW)
/* Fetch-and-Add(FAA) */
#define RME_FETCH_ADD(PTR,ADDEND)       __RME_A7M_Fetch_Add(PTR,ADDEND)
/* Fetch-and-And(FAND) */
#define RME_FETCH_AND(PTR,OPERAND)      __RME_A7M_Fetch_And(PTR,OPERAND)
/* Get most significant bit */
#define RME_MSB_GET(VAL)                __RME_A7M_MSB_Get(VAL)
/* No read/write barriers needed on Cortex-M, because they are currently all
 * single core. If this changes in the future, we may need DMB barriers. */
#define RME_READ_ACQUIRE(X)             (*(X))
#define RME_WRITE_RELEASE(X,V)          ((*(X))=(V))
/* Reboot the processor if the assert fails in this port */
#define RME_ASSERT_FAILED(F,L,D,T)      __RME_A7M_Reboot()

/* The CPU and application specific macros are here */
#include "rme_platform_a7m_conf.h"
/* End System macros *********************************************************/

/* Cortex-M specific macros **************************************************/
/* Registers *****************************************************************/
#define RME_A7M_REG(X)                  (*((volatile rme_ptr_t*)(X)))
#define RME_A7M_REGB(X)                 (*((volatile rme_u8_t*)(X)))

#define RME_A7M_ITM_TER                 RME_A7M_REG(0xE0000E00)
#define RME_A7M_ITM_PORT(X)             RME_A7M_REG(0xE0000000+((X)<<2))

#define RME_A7M_ITM_TCR                 RME_A7M_REG(0xE0000E80)
#define RME_A7M_ITM_TCR_ITMENA          (1U<<0)

#define RME_A7M_DWT_CTRL                RME_A7M_REG(0xE0001000)
#define RME_A7M_DWT_CTRL_NOCYCCNT       (1U<<25)
#define RME_A7M_DWT_CTRL_CYCCNTENA      (1U<<0)

#define RME_A7M_DWT_CYCCNT              RME_A7M_REG(0xE0001004)

#define RME_A7M_SCNSCB_ICTR             RME_A7M_REG(0xE000E004)

#define RME_A7M_SCNSCB_ACTLR            RME_A7M_REG(0xE000E008)
#define RME_A7M_SCNSCB_ACTLR_DISBTAC    (1U<<13)

#define RME_A7M_SYSTICK_CTRL            RME_A7M_REG(0xE000E010)
#define RME_A7M_SYSTICK_CTRL_CLKSOURCE  (1U<<2)
#define RME_A7M_SYSTICK_CTRL_TICKINT    (1U<<1)
#define RME_A7M_SYSTICK_CTRL_ENABLE     (1U<<0)

#define RME_A7M_SYSTICK_LOAD            RME_A7M_REG(0xE000E014)
#define RME_A7M_SYSTICK_VALREG          RME_A7M_REG(0xE000E018)
#define RME_A7M_SYSTICK_CALIB           RME_A7M_REG(0xE000E01C)

#define RME_A7M_NVIC_ISER(X)            RME_A7M_REG(0xE000E100+(((X)>>5)<<2))
#define RME_A7M_NVIC_ICER(X)            RME_A7M_REG(0xE000E180+(((X)>>5)<<2))

#define RME_A7M_NVIC_IPR(X)             RME_A7M_REGB(0xE000E400+(X))
#define RME_A7M_NVIC_GROUPING_P7S1      (0)
#define RME_A7M_NVIC_GROUPING_P6S2      (1)
#define RME_A7M_NVIC_GROUPING_P5S3      (2)
#define RME_A7M_NVIC_GROUPING_P4S4      (3)
#define RME_A7M_NVIC_GROUPING_P3S5      (4)
#define RME_A7M_NVIC_GROUPING_P2S6      (5)
#define RME_A7M_NVIC_GROUPING_P1S7      (6)
#define RME_A7M_NVIC_GROUPING_P0S8      (7)

#define RME_A7M_IRQN_NONMASKABLEINT     (-14)
#define RME_A7M_IRQN_MEMORYMANAGEMENT   (-12)
#define RME_A7M_IRQN_BUSFAULT           (-11)
#define RME_A7M_IRQN_USAGEFAULT         (-10)
#define RME_A7M_IRQN_SVCALL             (-5)
#define RME_A7M_IRQN_DEBUGMONITOR       (-4)
#define RME_A7M_IRQN_PENDSV             (-2)
#define RME_A7M_IRQN_SYSTICK            (-1)

#define RME_A7M_SCB_CPUID               RME_A7M_REG(0xE000ED00)
#define RME_A7M_SCB_ICSR                RME_A7M_REG(0xE000ED04)
#define RME_A7M_SCB_VTOR                RME_A7M_REG(0xE000ED08)
#define RME_A7M_SCB_AIRCR               RME_A7M_REG(0xE000ED0C)

#define RME_A7M_SCB_SCR                 RME_A7M_REG(0xE000ED10)
#define RME_A7M_SCB_SCR_SEVONPEND       (1<<4)
#define RME_A7M_SCB_SCR_SLEEPDEEP       (1<<2)
#define RME_A7M_SCB_SCR_SLEEPONEXIT     (1<<1)

#define RME_A7M_SCB_CCR                 RME_A7M_REG(0xE000ED14)
#define RME_A7M_SCB_CCR_IC              (1U<<17)
#define RME_A7M_SCB_CCR_DC              (1U<<16)

#define RME_A7M_SCB_SHPR(X)             RME_A7M_REGB(0xE000ED18+(X))

#define RME_A7M_SCB_SHCSR               RME_A7M_REG(0xE000ED24)
#define RME_A7M_SCB_SHCSR_MEMFAULTENA   (1U<<16)
#define RME_A7M_SCB_SHCSR_BUSFAULTENA   (1U<<17)
#define RME_A7M_SCB_SHCSR_USGFAULTENA   (1U<<18)

#define RME_A7M_SCB_CFSR                RME_A7M_REG(0xE000ED28)
#define RME_A7M_SCB_HFSR                RME_A7M_REG(0xE000ED2C)
#define RME_A7M_SCB_MMFAR               RME_A7M_REG(0xE000ED34)
#define RME_A7M_SCB_ID_PFR0             RME_A7M_REG(0xE000ED40)
#define RME_A7M_SCB_ID_PFR1             RME_A7M_REG(0xE000ED44)
#define RME_A7M_SCB_ID_DFR0             RME_A7M_REG(0xE000ED48)
#define RME_A7M_SCB_ID_AFR0             RME_A7M_REG(0xE000ED4C)
#define RME_A7M_SCB_ID_MMFR0            RME_A7M_REG(0xE000ED50)
#define RME_A7M_SCB_ID_MMFR1            RME_A7M_REG(0xE000ED54)
#define RME_A7M_SCB_ID_MMFR2            RME_A7M_REG(0xE000ED58)
#define RME_A7M_SCB_ID_MMFR3            RME_A7M_REG(0xE000ED5C)
#define RME_A7M_SCB_ID_ISAR0            RME_A7M_REG(0xE000ED60)
#define RME_A7M_SCB_ID_ISAR1            RME_A7M_REG(0xE000ED64)
#define RME_A7M_SCB_ID_ISAR2            RME_A7M_REG(0xE000ED68)
#define RME_A7M_SCB_ID_ISAR3            RME_A7M_REG(0xE000ED6C)
#define RME_A7M_SCB_ID_ISAR4            RME_A7M_REG(0xE000ED70)
#define RME_A7M_SCB_ID_ISAR5            RME_A7M_REG(0xE000ED74)
#define RME_A7M_SCB_CLIDR               RME_A7M_REG(0xE000ED78)
#define RME_A7M_SCB_CTR                 RME_A7M_REG(0xE000ED7C)

#define RME_A7M_SCB_CCSIDR              RME_A7M_REG(0xE000ED80)
#define RME_A7M_SCB_CCSIDR_WAYS(X)      (((X)&0x1FF8)>>3)
#define RME_A7M_SCB_CCSIDR_SETS(X)      (((X)&0x0FFFE000)>>13)

#define RME_A7M_SCB_CSSELR              RME_A7M_REG(0xE000ED84)
#define RME_A7M_SCB_CPACR               RME_A7M_REG(0xE000ED88)
#define RME_A7M_MPU_TYPE                RME_A7M_REG(0xE000ED90)

#define RME_A7M_MPU_CTRL                RME_A7M_REG(0xE000ED94)
#define RME_A7M_MPU_CTRL_PRIVDEF        (1U<<2)
#define RME_A7M_MPU_CTRL_ENABLE         (1U<<0)

#define RME_A7M_SCNSCB_STIR             RME_A7M_REG(0xE000EF00)

#define RME_A7M_SCNSCB_MVFR0            RME_A7M_REG(0xE000EF40)
#define RME_A7M_SCNSCB_MVFR1            RME_A7M_REG(0xE000EF44)
#define RME_A7M_SCNSCB_MVFR2            RME_A7M_REG(0xE000EF48)

#define RME_A7M_SCNSCB_ICALLU           RME_A7M_REG(0xE000EF50)
#define RME_A7M_SCNSCB_ICIMVAU          RME_A7M_REG(0xE000EF58)
#define RME_A7M_SCNSCB_DCIMVAC          RME_A7M_REG(0xE000EF5C)
#define RME_A7M_SCNSCB_DCISW            RME_A7M_REG(0xE000EF60)
#define RME_A7M_SCNSCB_DCCMVAC          RME_A7M_REG(0xE000EF68)
#define RME_A7M_SCNSCB_DCCSW            RME_A7M_REG(0xE000EF6C)
#define RME_A7M_SCNSCB_DCCIMVAC         RME_A7M_REG(0xE000EF70)
#define RME_A7M_SCNSCB_DCCISW           RME_A7M_REG(0xE000EF74)
#define RME_A7M_SCNSCB_BPIALL           RME_A7M_REG(0xE000EF78)

#define RME_A7M_SCNSCB_DC(SET,WAY)      (((SET)<<5)|((WAY)<<30))

#define RME_A7M_SCNSCB_PID4             RME_A7M_REG(0xE000EFD0)
#define RME_A7M_SCNSCB_PID5             RME_A7M_REG(0xE000EFD4)
#define RME_A7M_SCNSCB_PID6             RME_A7M_REG(0xE000EFD8)
#define RME_A7M_SCNSCB_PID7             RME_A7M_REG(0xE000EFDC)
#define RME_A7M_SCNSCB_PID0             RME_A7M_REG(0xE000EFE0)
#define RME_A7M_SCNSCB_PID1             RME_A7M_REG(0xE000EFE4)
#define RME_A7M_SCNSCB_PID2             RME_A7M_REG(0xE000EFE8)
#define RME_A7M_SCNSCB_PID3             RME_A7M_REG(0xE000EFEC)
#define RME_A7M_SCNSCB_CID0             RME_A7M_REG(0xE000EFF0)
#define RME_A7M_SCNSCB_CID1             RME_A7M_REG(0xE000EFF4)
#define RME_A7M_SCNSCB_CID2             RME_A7M_REG(0xE000EFF8)
#define RME_A7M_SCNSCB_CID3             RME_A7M_REG(0xE000EFFC)

/* Generic *******************************************************************/
/* ARMv7-M EXC_RETURN bits */
#define RME_A7M_EXC_RET_INIT            (0xFFFFFFFD)
/* Whether the stack frame is standard(contains no FPU data). 1 means yes, 0 means no */
#define RME_A7M_EXC_RET_STD_FRAME       (1<<4)
/* Are we returning to user mode? 1 means yes, 0 means no */
#define RME_A7M_EXC_RET_RET_USER        (1<<3)
/* FPU type definitions */
#define RME_A7M_FPU_NONE                (0)
#define RME_A7M_FPU_FPV4_SP             (1)
#define RME_A7M_FPU_FPV5_SP             (2)
#define RME_A7M_FPU_FPV5_DP             (3)

/* Handler *******************************************************************/
/* Fault definitions */
/* The NMI is active */
#define RME_A7M_ICSR_NMIPENDSET         (((rme_ptr_t)1)<<31)
/* Debug event has occurred. The Debug Fault Status Register has been updated */
#define RME_A7M_HFSR_DEBUGEVT           (((rme_ptr_t)1)<<31)
/* Processor has escalated a configurable-priority exception to HardFault */
#define RME_A7M_HFSR_FORCED             (1<<30)
/* Vector table read fault has occurred */
#define RME_A7M_HFSR_VECTTBL            (1<<1)
/* Divide by zero */
#define RME_A7M_UFSR_DIVBYZERO          (1<<25)
/* Unaligned load/store access */
#define RME_A7M_UFSR_UNALIGNED          (1<<24)
/* No such coprocessor */
#define RME_A7M_UFSR_NOCP               (1<<19)
/* Invalid vector return LR or PC value */
#define RME_A7M_UFSR_INVPC              (1<<18)
/* Attempt to enter an invalid instruction set (ARM) state */
#define RME_A7M_UFSR_INVSTATE           (1<<17)
/* Invalid IT instruction or related instructions */
#define RME_A7M_UFSR_UNDEFINSTR         (1<<16)
/* The Bus Fault Address Register is valid */
#define RME_A7M_BFSR_BFARVALID          (1<<15)
/* The bus fault happened during FP lazy stacking */
#define RME_A7M_BFSR_LSPERR             (1<<13)
/* A derived bus fault has occurred on exception entry */
#define RME_A7M_BFSR_STKERR             (1<<12)
/* A derived bus fault has occurred on exception return */
#define RME_A7M_BFSR_UNSTKERR           (1<<11)
/* Imprecise data access error has occurred */
#define RME_A7M_BFSR_IMPRECISERR        (1<<10)
/* Precise data access error has occurred, BFAR updated */
#define RME_A7M_BFSR_PRECISERR          (1<<9)
/* A bus fault on an instruction prefetch has occurred. The 
 * fault is signaled only if the instruction is issued */
#define RME_A7M_BFSR_IBUSERR            (1<<8)
/* The Memory Management Fault Address Register have valid contents */
#define RME_A7M_MFSR_MMARVALID          (1<<7)
/* A MemManage fault occurred during FP lazy state preservation */
#define RME_A7M_MFSR_MLSPERR            (1<<5)
/* A derived MemManage fault occurred on exception entry */
#define RME_A7M_MFSR_MSTKERR            (1<<4)
/* A derived MemManage fault occurred on exception return */
#define RME_A7M_MFSR_MUNSTKERR          (1<<3)
/* Data access violation. The MMFAR shows the data address that
 * the load or store tried to access */
#define RME_A7M_MFSR_DACCVIOL           (1<<1)
/* MPU or Execute Never (XN) default memory map access violation on an
 * instruction fetch has occurred. The fault is signalled only if the
 * instruction is issued */
#define RME_A7M_MFSR_IACCVIOL           (1<<0)
/* Initialization ************************************************************/
/* The capability table of the init process */
#define RME_BOOT_CAPTBL                 0
/* The top-level page table of the init process - always 4GB full range split into 8 pages */
#define RME_BOOT_PGTBL                  1
/* The init process */
#define RME_BOOT_INIT_PROC              2
/* The init thread */
#define RME_BOOT_INIT_THD               3
/* The initial kernel function capability */
#define RME_BOOT_INIT_KERN              4
/* The initial kernel memory capability */
#define RME_BOOT_INIT_KMEM              5
/* The initial timer endpoint */
#define RME_BOOT_INIT_TIMER             6
/* The initial default endpoint for all other vectors */
#define RME_BOOT_INIT_VECT              7
/* Booting capability layout */
#define RME_A7M_CPT                     ((struct RME_Cap_Captbl*)(RME_KMEM_VA_BASE))

/* Page Table ****************************************************************/
/* For ARMv7-M:
 * The layout of the page entry is:
 * [31:5] Paddr - The physical address to map this page to, or the physical
 *                address of the next layer of page table. This address is
 *                always aligned to 32 bytes.
 * [4:2] Reserved - Because subregions must share attributes, we have the permission
 *                  flags in the page table headers ("Page_Flags" field). These flags
 *                  are completely identical to RME standard page flags.
 * [1] Terminal - Is this page a terminal page, or points to another page table?
 * [0] Present - Is this entry present?
 *
 * The layout of a directory entry is:
 * [31:2] Paddr - The in-kernel physical address of the lower page directory.
 * [1] Terminal - Is this page a terminal page, or points to another page table?
 * [0] Present - Is this entry present?
 */
/* Get the actual table positions */
#define RME_A7M_PGTBL_TBL_NOM(X)        ((X)+(sizeof(struct __RME_A7M_Pgtbl_Meta)/sizeof(rme_ptr_t)))
#define RME_A7M_PGTBL_TBL_TOP(X)        ((X)+(sizeof(struct __RME_A7M_Pgtbl_Meta)+sizeof(struct __RME_A7M_MPU_Data))/sizeof(rme_ptr_t))
/* Page entry bit definitions */
#define RME_A7M_PGTBL_PRESENT           (1<<0)
#define RME_A7M_PGTBL_TERMINAL          (1<<1)
/* The address mask for the actual page address */
#define RME_A7M_PGTBL_PTE_ADDR(X)       ((X)&0xFFFFFFFC)
/* The address mask for the next level page table address */
#define RME_A7M_PGTBL_PGD_ADDR(X)       ((X)&0xFFFFFFFC)
/* Page table metadata definitions */
#define RME_A7M_PGTBL_START(X)          ((X)&0xFFFFFFFE)
#define RME_A7M_PGTBL_SIZEORD(X)        ((X)>>16)
#define RME_A7M_PGTBL_NUMORD(X)         ((X)&0x0000FFFF)
#define RME_A7M_PGTBL_DIRNUM(X)         ((X)>>16)
#define RME_A7M_PGTBL_PAGENUM(X)        ((X)&0x0000FFFF)
#define RME_A7M_PGTBL_INC_PAGENUM(X)    ((X)+=0x00000001)
#define RME_A7M_PGTBL_DEC_PAGENUM(X)    ((X)-=0x00000001)
#define RME_A7M_PGTBL_INC_DIRNUM(X)     ((X)+=0x00010000)
#define RME_A7M_PGTBL_DEC_DIRNUM(X)     ((X)-=0x00010000)
/* MPU operation flag */
#define RME_A7M_MPU_CLR                 (0)
#define RME_A7M_MPU_UPD                 (1)
/* MPU definitions */
/* Extract address for/from MPU */
#define RME_A7M_MPU_ADDR(X)             ((X)&0xFFFFFFE0)
/* Get info from MPU - X is the region's size order, not a subregion */
#define RME_A7M_MPU_SZORD(X)            ((((X)&0x3F)>>1)+1)
/* Write info to MPU - X is the region's size order, not a subregion */
#define RME_A7M_MPU_VALID               (1<<4)
#define RME_A7M_MPU_SRDCLR              (0x0000FF00)
#define RME_A7M_MPU_XN                  (1<<28)
#define RME_A7M_MPU_RO                  (2<<24)
#define RME_A7M_MPU_RW                  (3<<24)
#define RME_A7M_MPU_CACHEABLE           (1<<17)
#define RME_A7M_MPU_BUFFERABLE          (1<<16)
#define RME_A7M_MPU_REGIONSIZE(X)       ((X-1)<<1)
#define RME_A7M_MPU_SZENABLE            (1)

/* Events ********************************************************************/
/* The fixed maximum number */
#define RME_A7M_MAX_EVTS                (1024)

/* Platform-specific kernel function macros **********************************/
/* Page table entry mode which property to get */
#define RME_A7M_KERN_PGTBL_ENTRY_MOD_GET_FLAGS      (0)
#define RME_A7M_KERN_PGTBL_ENTRY_MOD_GET_SIZEORDER  (1)
#define RME_A7M_KERN_PGTBL_ENTRY_MOD_GET_NUMORDER   (2)
/* Interrupt source configuration */
#define RME_A7M_KERN_INT_LOCAL_MOD_GET_STATE        (0)
#define RME_A7M_KERN_INT_LOCAL_MOD_SET_STATE        (1)
#define RME_A7M_KERN_INT_LOCAL_MOD_GET_PRIO         (2)
#define RME_A7M_KERN_INT_LOCAL_MOD_SET_PRIO         (3)
/* Cache identifier */
#define RME_A7M_KERN_CACHE_ICACHE                   (0)
#define RME_A7M_KERN_CACHE_DCACHE                   (1)
#define RME_A7M_KERN_CACHE_BTAC                     (2)
/* Cache modification */
#define RME_A7M_KERN_CACHE_MOD_GET_STATE            (0)
#define RME_A7M_KERN_CACHE_MOD_SET_STATE            (1)
/* Cache state */
#define RME_A7M_KERN_CACHE_STATE_DISABLE            (0)
#define RME_A7M_KERN_CACHE_STATE_ENABLE             (1)
/* Cache maintenance */
#define RME_A7M_KERN_CACHE_CLEAN_ALL                (0)
#define RME_A7M_KERN_CACHE_CLEAN_ADDR               (1)
#define RME_A7M_KERN_CACHE_CLEAN_SET                (2)
#define RME_A7M_KERN_CACHE_CLEAN_WAY                (3)
#define RME_A7M_KERN_CACHE_CLEAN_SETWAY             (4)
#define RME_A7M_KERN_CACHE_INV_ALL                  (5)
#define RME_A7M_KERN_CACHE_INV_ADDR                 (6)
#define RME_A7M_KERN_CACHE_INV_SET                  (7)
#define RME_A7M_KERN_CACHE_INV_WAY                  (8)
#define RME_A7M_KERN_CACHE_INV_SETWAY               (9)
#define RME_A7M_KERN_CACHE_CLEAN_INV_ALL            (10)
#define RME_A7M_KERN_CACHE_CLEAN_INV_ADDR           (11)
#define RME_A7M_KERN_CACHE_CLEAN_INV_SET            (12)
#define RME_A7M_KERN_CACHE_CLEAN_INV_WAY            (13)
#define RME_A7M_KERN_CACHE_CLEAN_INV_SETWAY         (14)
/* Prefetcher modification */
#define RME_A7M_KERN_PRFTH_MOD_GET_STATE            (0)
#define RME_A7M_KERN_PRFTH_MOD_SET_STATE            (1)
/* Prefetcher state */
#define RME_A7M_KERN_PRFTH_STATE_DISABLE            (0)
#define RME_A7M_KERN_PRFTH_STATE_ENABLE             (1)
/* CPU feature support */
#define RME_A7M_KERN_CPU_FUNC_CPUID                 (0)
#define RME_A7M_KERN_CPU_FUNC_ID_PFR0               (1)
#define RME_A7M_KERN_CPU_FUNC_ID_PFR1               (2)
#define RME_A7M_KERN_CPU_FUNC_ID_DFR0               (3)
#define RME_A7M_KERN_CPU_FUNC_ID_AFR0               (4)
#define RME_A7M_KERN_CPU_FUNC_ID_MMFR0              (5)
#define RME_A7M_KERN_CPU_FUNC_ID_MMFR1              (6)
#define RME_A7M_KERN_CPU_FUNC_ID_MMFR2              (7)
#define RME_A7M_KERN_CPU_FUNC_ID_MMFR3              (8)
#define RME_A7M_KERN_CPU_FUNC_ID_ISAR0              (9)
#define RME_A7M_KERN_CPU_FUNC_ID_ISAR1              (10)
#define RME_A7M_KERN_CPU_FUNC_ID_ISAR2              (11)
#define RME_A7M_KERN_CPU_FUNC_ID_ISAR3              (12)
#define RME_A7M_KERN_CPU_FUNC_ID_ISAR4              (13)
#define RME_A7M_KERN_CPU_FUNC_ID_ISAR5              (14)
#define RME_A7M_KERN_CPU_FUNC_CLIDR                 (15)
#define RME_A7M_KERN_CPU_FUNC_CTR                   (16)
#define RME_A7M_KERN_CPU_FUNC_ICACHE_CCSIDR         (17)
#define RME_A7M_KERN_CPU_FUNC_DCACHE_CCSIDR         (18)
#define RME_A7M_KERN_CPU_FUNC_MPU_TYPE              (19)
#define RME_A7M_KERN_CPU_FUNC_MVFR0                 (20)
#define RME_A7M_KERN_CPU_FUNC_MVFR1                 (21)
#define RME_A7M_KERN_CPU_FUNC_MVFR2                 (22)
#define RME_A7M_KERN_CPU_FUNC_PID0                  (23)
#define RME_A7M_KERN_CPU_FUNC_PID1                  (24)
#define RME_A7M_KERN_CPU_FUNC_PID2                  (25)
#define RME_A7M_KERN_CPU_FUNC_PID3                  (26)
#define RME_A7M_KERN_CPU_FUNC_PID4                  (27)
#define RME_A7M_KERN_CPU_FUNC_PID5                  (28)
#define RME_A7M_KERN_CPU_FUNC_PID6                  (29)
#define RME_A7M_KERN_CPU_FUNC_PID7                  (30)
#define RME_A7M_KERN_CPU_FUNC_CID0                  (31)
#define RME_A7M_KERN_CPU_FUNC_CID1                  (32)
#define RME_A7M_KERN_CPU_FUNC_CID2                  (33)
#define RME_A7M_KERN_CPU_FUNC_CID3                  (34)
/* Perfomance counters */
#define RME_A7M_KERN_PERF_CYCLE_CYCCNT              (0)
/* Performance counter state operations */
#define RME_A7M_KERN_PERF_STATE_GET                 (0)
#define RME_A7M_KERN_PERF_STATE_SET                 (1)
/* Performance counter states */
#define RME_A7M_KERN_PERF_STATE_DISABLE             (0)
#define RME_A7M_KERN_PERF_STATE_ENABLE              (1)
/* Performance counter value operations */
#define RME_A7M_KERN_PERF_VAL_GET                   (0)
#define RME_A7M_KERN_PERF_VAL_SET                   (1)
/* Register read/write */
#define RME_A7M_KERN_DEBUG_REG_MOD_SP_GET           (0)
#define RME_A7M_KERN_DEBUG_REG_MOD_SP_SET           (1)
#define RME_A7M_KERN_DEBUG_REG_MOD_R4_GET           (2)
#define RME_A7M_KERN_DEBUG_REG_MOD_R4_SET           (3)
#define RME_A7M_KERN_DEBUG_REG_MOD_R5_GET           (4)
#define RME_A7M_KERN_DEBUG_REG_MOD_R5_SET           (5)
#define RME_A7M_KERN_DEBUG_REG_MOD_R6_GET           (6)
#define RME_A7M_KERN_DEBUG_REG_MOD_R6_SET           (7)
#define RME_A7M_KERN_DEBUG_REG_MOD_R7_GET           (8)
#define RME_A7M_KERN_DEBUG_REG_MOD_R7_SET           (9)
#define RME_A7M_KERN_DEBUG_REG_MOD_R8_GET           (10)
#define RME_A7M_KERN_DEBUG_REG_MOD_R8_SET           (11)
#define RME_A7M_KERN_DEBUG_REG_MOD_R9_GET           (12)
#define RME_A7M_KERN_DEBUG_REG_MOD_R9_SET           (13)
#define RME_A7M_KERN_DEBUG_REG_MOD_R10_GET          (14)
#define RME_A7M_KERN_DEBUG_REG_MOD_R10_SET          (15)
#define RME_A7M_KERN_DEBUG_REG_MOD_R11_GET          (16)
#define RME_A7M_KERN_DEBUG_REG_MOD_R11_SET          (17)
#define RME_A7M_KERN_DEBUG_REG_MOD_LR_GET           (18)
#define RME_A7M_KERN_DEBUG_REG_MOD_LR_SET           (19)
/* FPU register read/write */
#define RME_A7M_KERN_DEBUG_REG_MOD_S16_GET          (20)
#define RME_A7M_KERN_DEBUG_REG_MOD_S16_SET          (21)
#define RME_A7M_KERN_DEBUG_REG_MOD_S17_GET          (22)
#define RME_A7M_KERN_DEBUG_REG_MOD_S17_SET          (23)
#define RME_A7M_KERN_DEBUG_REG_MOD_S18_GET          (24)
#define RME_A7M_KERN_DEBUG_REG_MOD_S18_SET          (25)
#define RME_A7M_KERN_DEBUG_REG_MOD_S19_GET          (26)
#define RME_A7M_KERN_DEBUG_REG_MOD_S19_SET          (27)
#define RME_A7M_KERN_DEBUG_REG_MOD_S20_GET          (28)
#define RME_A7M_KERN_DEBUG_REG_MOD_S20_SET          (29)
#define RME_A7M_KERN_DEBUG_REG_MOD_S21_GET          (30)
#define RME_A7M_KERN_DEBUG_REG_MOD_S21_SET          (31)
#define RME_A7M_KERN_DEBUG_REG_MOD_S22_GET          (32)
#define RME_A7M_KERN_DEBUG_REG_MOD_S22_SET          (33)
#define RME_A7M_KERN_DEBUG_REG_MOD_S23_GET          (34)
#define RME_A7M_KERN_DEBUG_REG_MOD_S23_SET          (35)
#define RME_A7M_KERN_DEBUG_REG_MOD_S24_GET          (36)
#define RME_A7M_KERN_DEBUG_REG_MOD_S24_SET          (37)
#define RME_A7M_KERN_DEBUG_REG_MOD_S25_GET          (38)
#define RME_A7M_KERN_DEBUG_REG_MOD_S25_SET          (39)
#define RME_A7M_KERN_DEBUG_REG_MOD_S26_GET          (40)
#define RME_A7M_KERN_DEBUG_REG_MOD_S26_SET          (41)
#define RME_A7M_KERN_DEBUG_REG_MOD_S27_GET          (42)
#define RME_A7M_KERN_DEBUG_REG_MOD_S27_SET          (43)
#define RME_A7M_KERN_DEBUG_REG_MOD_S28_GET          (44)
#define RME_A7M_KERN_DEBUG_REG_MOD_S28_SET          (45)
#define RME_A7M_KERN_DEBUG_REG_MOD_S29_GET          (46)
#define RME_A7M_KERN_DEBUG_REG_MOD_S29_SET          (47)
#define RME_A7M_KERN_DEBUG_REG_MOD_S30_GET          (48)
#define RME_A7M_KERN_DEBUG_REG_MOD_S30_SET          (49)
#define RME_A7M_KERN_DEBUG_REG_MOD_S31_GET          (50)
#define RME_A7M_KERN_DEBUG_REG_MOD_S31_SET          (51)
/* Invocation register read/write */
#define RME_A7M_KERN_DEBUG_INV_MOD_SP_GET           (0)
#define RME_A7M_KERN_DEBUG_INV_MOD_SP_SET           (1)
#define RME_A7M_KERN_DEBUG_INV_MOD_LR_GET           (2)
#define RME_A7M_KERN_DEBUG_INV_MOD_LR_SET           (3)
/*****************************************************************************/
/* __RME_PLATFORM_A7M_H_DEFS__ */
#endif
/* __HDR_DEFS__ */
#endif
/* End Defines ***************************************************************/

/* Structs *******************************************************************/
#ifdef __HDR_STRUCTS__
#ifndef __RME_PLATFORM_A7M_H_STRUCTS__
#define __RME_PLATFORM_A7M_H_STRUCTS__
/* We used structs in the header */

/* Use defines in these headers */
#define __HDR_DEFS__
#undef __HDR_DEFS__
/*****************************************************************************/
/* Handler *******************************************************************/
/* Interrupt flag structure */
struct __RME_A7M_Flag_Set
{
    rme_ptr_t Lock;
    rme_ptr_t Group;
    rme_ptr_t Flags[32];
};

/* Interrupt flag pair structure */
struct __RME_A7M_Phys_Flags
{
    struct __RME_A7M_Flag_Set Set0;
    struct __RME_A7M_Flag_Set Set1;
};

/* Register Manipulation *****************************************************/
/* The register set struct - R0-R3, R12, PC, LR, xPSR is automatically pushed.
 * Here we need LR to decide EXC_RETURN, that's why it is here */
struct RME_Reg_Struct
{
    rme_ptr_t SP;
    rme_ptr_t R4;
    rme_ptr_t R5;
    rme_ptr_t R6;
    rme_ptr_t R7;
    rme_ptr_t R8;
    rme_ptr_t R9;
    rme_ptr_t R10;
    rme_ptr_t R11;
    rme_ptr_t LR;
};

/* The coprocessor register set structure. In Cortex-M, if there is a 
 * single-precision FPU, then the FPU S0-S15 is automatically pushed */
struct RME_Cop_Struct
{
    rme_ptr_t S16;
    rme_ptr_t S17;
    rme_ptr_t S18;
    rme_ptr_t S19;
    rme_ptr_t S20;
    rme_ptr_t S21;
    rme_ptr_t S22;
    rme_ptr_t S23;
    rme_ptr_t S24;
    rme_ptr_t S25;
    rme_ptr_t S26;
    rme_ptr_t S27;
    rme_ptr_t S28;
    rme_ptr_t S29;
    rme_ptr_t S30;
    rme_ptr_t S31;
};

/* Invocation register set structure */
struct RME_Iret_Struct
{
    rme_ptr_t LR;
    rme_ptr_t SP;
};

/* Page Table ****************************************************************/
/* MPU entry structure */
struct __RME_A7M_MPU_Entry
{
    rme_ptr_t MPU_RBAR;
    rme_ptr_t MPU_RASR;
};
/* Page table metadata structure */
struct __RME_A7M_Pgtbl_Meta
{
    /* The MPU setting is always in the top level. This is a pointer to the top level */
    rme_ptr_t Toplevel;
    /* The start mapping address of this page table */
    rme_ptr_t Base_Addr;
    /* The size/num order of this level */
    rme_ptr_t Size_Num_Order;
    /* The child directory/page number in this level */
    rme_ptr_t Dir_Page_Count;
    /* The page flags at this level. If any pages are mapped in, it must conform
     * to the same attributes as the older pages */
    rme_ptr_t Page_Flags;
};

/* MPU metadata structure */
struct __RME_A7M_MPU_Data
{
    /* Bitmap showing whether these are static or not */
    rme_ptr_t Static;
    /* The MPU data itself. For ARMv7-M, the number of regions shall not exceed 32 */
    struct __RME_A7M_MPU_Entry Data[RME_A7M_MPU_REGIONS];
};
/*****************************************************************************/
/* __RME_PLATFORM_A7M_H_STRUCTS__ */
#endif
/* __HDR_STRUCTS__ */
#endif
/* End Structs ***************************************************************/

/* Private Global Variables **************************************************/
#if(!(defined __HDR_DEFS__||defined __HDR_STRUCTS__))
#ifndef __RME_PLATFORM_A7M_MEMBERS__
#define __RME_PLATFORM_A7M_MEMBERS__

/* In this way we can use the data structures and definitions in the headers */
#define __HDR_DEFS__

#undef __HDR_DEFS__

#define __HDR_STRUCTS__

#undef __HDR_STRUCTS__

/* If the header is not used in the public mode */
#ifndef __HDR_PUBLIC_MEMBERS__
/*****************************************************************************/

/*****************************************************************************/
/* End Private Global Variables **********************************************/

/* Private C Function Prototypes *********************************************/
/* Vector Flags **************************************************************/
static void __RME_A7M_Set_Flag(rme_ptr_t Flagset, rme_ptr_t Pos);
/* Page Table ****************************************************************/
static rme_ptr_t __RME_A7M_Rand(void);
static rme_ptr_t ___RME_Pgtbl_MPU_Gen_RASR(rme_ptr_t* Table, rme_ptr_t Flags, 
                                           rme_ptr_t Size_Order, rme_ptr_t Num_Order);
static rme_ptr_t ___RME_Pgtbl_MPU_Clear(struct __RME_A7M_MPU_Data* Top_MPU, 
                                        rme_ptr_t Base_Addr, rme_ptr_t Size_Order, rme_ptr_t Num_Order);
static rme_ptr_t ___RME_Pgtbl_MPU_Add(struct __RME_A7M_MPU_Data* Top_MPU, 
                                      rme_ptr_t Base_Addr, rme_ptr_t Size_Order, rme_ptr_t Num_Order,
                                      rme_ptr_t MPU_RASR, rme_ptr_t Static);
static rme_ptr_t ___RME_Pgtbl_MPU_Update(struct __RME_A7M_Pgtbl_Meta* Meta, rme_ptr_t Op_Flag);
/* Kernel function ***********************************************************/
static rme_ret_t __RME_A7M_Pgtbl_Entry_Mod(struct RME_Cap_Captbl* Captbl, 
                                               rme_cid_t Cap_Pgtbl, rme_ptr_t Vaddr, rme_ptr_t Type);
static rme_ret_t __RME_A7M_Int_Local_Mod(rme_ptr_t Int_Num, rme_ptr_t Operation, rme_ptr_t Param);
static rme_ret_t __RME_A7M_Int_Local_Trig(rme_ptr_t CPUID, rme_ptr_t Int_Num);
static rme_ret_t __RME_A7M_Evt_Local_Trig(struct RME_Reg_Struct* Reg, rme_ptr_t CPUID, rme_ptr_t Evt_Num);
static rme_ret_t __RME_A7M_Cache_Mod(rme_ptr_t Cache_ID, rme_ptr_t Operation, rme_ptr_t Param);
static rme_ret_t __RME_A7M_Cache_Maint(rme_ptr_t Cache_ID, rme_ptr_t Operation, rme_ptr_t Param);
static rme_ret_t __RME_A7M_Prfth_Mod(rme_ptr_t Prfth_ID, rme_ptr_t Operation, rme_ptr_t Param);
static rme_ret_t __RME_A7M_Perf_CPU_Func(struct RME_Reg_Struct* Reg, rme_ptr_t Freg_ID);
static rme_ret_t __RME_A7M_Perf_Mon_Mod(rme_ptr_t Perf_ID, rme_ptr_t Operation, rme_ptr_t Param);
static rme_ret_t __RME_A7M_Perf_Cycle_Mod(struct RME_Reg_Struct* Reg, rme_ptr_t Cycle_ID, 
                                          rme_ptr_t Operation, rme_ptr_t Value);
static rme_ret_t __RME_A7M_Debug_Reg_Mod(struct RME_Cap_Captbl* Captbl, struct RME_Reg_Struct* Reg, 
                                         rme_cid_t Cap_Thd, rme_ptr_t Operation, rme_ptr_t Value);
static rme_ret_t __RME_A7M_Debug_Inv_Mod(struct RME_Cap_Captbl* Captbl, struct RME_Reg_Struct* Reg, 
                                         rme_cid_t Cap_Thd, rme_ptr_t Operation, rme_ptr_t Value);
/*****************************************************************************/
#define __EXTERN__
/* End Private C Function Prototypes *****************************************/

/* Public Global Variables ***************************************************/
/* __HDR_PUBLIC_MEMBERS__ */
#else
#define __EXTERN__ EXTERN 
/* __HDR_PUBLIC_MEMBERS__ */
#endif

/*****************************************************************************/
/* Cortex-M only have one core, thus this is its CPU-local data structure */
__EXTERN__ struct RME_CPU_Local RME_A7M_Local;
/*****************************************************************************/

/* End Public Global Variables ***********************************************/

/* Public C Function Prototypes **********************************************/
/* Generic *******************************************************************/
/* Interrupts */
EXTERN void __RME_Disable_Int(void);
EXTERN void __RME_Enable_Int(void);
EXTERN void __RME_A7M_Barrier(void);
EXTERN void __RME_A7M_Wait_Int(void);
/* MSB counting */
EXTERN rme_ptr_t __RME_A7M_MSB_Get(rme_ptr_t Val);
/* Atomics */
__EXTERN__ rme_ptr_t __RME_A7M_Comp_Swap(rme_ptr_t* Ptr, rme_ptr_t Old, rme_ptr_t New);
__EXTERN__ rme_ptr_t __RME_A7M_Fetch_Add(rme_ptr_t* Ptr, rme_cnt_t Addend);
__EXTERN__ rme_ptr_t __RME_A7M_Fetch_And(rme_ptr_t* Ptr, rme_ptr_t Operand);
/* Debugging */
__EXTERN__ rme_ptr_t __RME_Putchar(char Char);
/* Getting CPUID */
__EXTERN__ rme_ptr_t __RME_CPUID_Get(void);

/* Handler *******************************************************************/
/* Fault handler */
__EXTERN__ void __RME_A7M_Fault_Handler(struct RME_Reg_Struct* Reg);
/* Generic interrupt handler */
__EXTERN__ void __RME_A7M_Vect_Handler(struct RME_Reg_Struct* Reg, rme_ptr_t Vect_Num);
/* Kernel function handler */
__EXTERN__ rme_ret_t __RME_Kern_Func_Handler(struct RME_Cap_Captbl* Captbl, struct RME_Reg_Struct* Reg,
                                             rme_ptr_t Func_ID, rme_ptr_t Sub_ID, rme_ptr_t Param1, rme_ptr_t Param2);

/* Initialization ************************************************************/
EXTERN void _RME_Kmain(rme_ptr_t Stack);
__EXTERN__ void __RME_A7M_Low_Level_Preinit(void);
__EXTERN__ rme_ptr_t __RME_Low_Level_Init(void);
__EXTERN__ rme_ptr_t __RME_Boot(void);
EXTERN void __RME_A7M_Reset(void);
__EXTERN__ void __RME_A7M_Reboot(void);
__EXTERN__ void __RME_A7M_NVIC_Set_Exc_Prio(rme_cnt_t Exc, rme_ptr_t Prio);
__EXTERN__ void __RME_A7M_Cache_Init(void);
EXTERN void __RME_Enter_User_Mode(rme_ptr_t Entry_Addr, rme_ptr_t Stack_Addr, rme_ptr_t CPUID);

/* Register Manipulation *****************************************************/
/* Coprocessor */
EXTERN void ___RME_A7M_Thd_Cop_Save(struct RME_Cop_Struct* Cop_Reg);
EXTERN void ___RME_A7M_Thd_Cop_Restore(struct RME_Cop_Struct* Cop_Reg);
/* Syscall parameter */
__EXTERN__ void __RME_Get_Syscall_Param(struct RME_Reg_Struct* Reg, rme_ptr_t* Svc,
                                        rme_ptr_t* Capid, rme_ptr_t* Param);
__EXTERN__ void __RME_Set_Syscall_Retval(struct RME_Reg_Struct* Reg, rme_ret_t Retval);
/* Thread register sets */
__EXTERN__ void __RME_Thd_Reg_Init(rme_ptr_t Entry, rme_ptr_t Stack, rme_ptr_t Param, struct RME_Reg_Struct* Reg);
__EXTERN__ void __RME_Thd_Reg_Copy(struct RME_Reg_Struct* Dst, struct RME_Reg_Struct* Src);
__EXTERN__ void __RME_Thd_Cop_Init(struct RME_Reg_Struct* Reg, struct RME_Cop_Struct* Cop_Reg);
__EXTERN__ void __RME_Thd_Cop_Save(struct RME_Reg_Struct* Reg, struct RME_Cop_Struct* Cop_Reg);
__EXTERN__ void __RME_Thd_Cop_Restore(struct RME_Reg_Struct* Reg, struct RME_Cop_Struct* Cop_Reg);
/* Invocation register sets */
__EXTERN__ void __RME_Inv_Reg_Save(struct RME_Iret_Struct* Ret, struct RME_Reg_Struct* Reg);
__EXTERN__ void __RME_Inv_Reg_Restore(struct RME_Reg_Struct* Reg, struct RME_Iret_Struct* Ret);
__EXTERN__ void __RME_Set_Inv_Retval(struct RME_Reg_Struct* Reg, rme_ret_t Retval);

/* Page Table ****************************************************************/
/* Initialization */
__EXTERN__ rme_ptr_t __RME_Pgtbl_Kmem_Init(void);
__EXTERN__ rme_ptr_t __RME_Pgtbl_Init(struct RME_Cap_Pgtbl* Pgtbl_Op);
/* Checking */
__EXTERN__ rme_ptr_t __RME_Pgtbl_Check(rme_ptr_t Base_Addr, rme_ptr_t Top_Flag, 
                                       rme_ptr_t Size_Order, rme_ptr_t Num_Order, rme_ptr_t Vaddr);
__EXTERN__ rme_ptr_t __RME_Pgtbl_Del_Check(struct RME_Cap_Pgtbl* Pgtbl_Op);
/* Setting the page table */
EXTERN void ___RME_A7M_MPU_Set(rme_ptr_t MPU_Meta);
__EXTERN__ void __RME_Pgtbl_Set(rme_ptr_t Pgtbl);
/* Table operations */
__EXTERN__ rme_ptr_t __RME_Pgtbl_Page_Map(struct RME_Cap_Pgtbl* Pgtbl_Op, rme_ptr_t Paddr, rme_ptr_t Pos, rme_ptr_t Flags);
__EXTERN__ rme_ptr_t __RME_Pgtbl_Page_Unmap(struct RME_Cap_Pgtbl* Pgtbl_Op, rme_ptr_t Pos);
__EXTERN__ rme_ptr_t __RME_Pgtbl_Pgdir_Map(struct RME_Cap_Pgtbl* Pgtbl_Parent, rme_ptr_t Pos, 
                                           struct RME_Cap_Pgtbl* Pgtbl_Child, rme_ptr_t Flags);
__EXTERN__ rme_ptr_t __RME_Pgtbl_Pgdir_Unmap(struct RME_Cap_Pgtbl* Pgtbl_Parent, rme_ptr_t Pos,
                                             struct RME_Cap_Pgtbl* Pgtbl_Child);
/* Lookup and walking */
__EXTERN__ rme_ptr_t __RME_Pgtbl_Lookup(struct RME_Cap_Pgtbl* Pgtbl_Op, rme_ptr_t Pos, rme_ptr_t* Paddr, rme_ptr_t* Flags);
__EXTERN__ rme_ptr_t __RME_Pgtbl_Walk(struct RME_Cap_Pgtbl* Pgtbl_Op, rme_ptr_t Vaddr, rme_ptr_t* Pgtbl,
                                      rme_ptr_t* Map_Vaddr, rme_ptr_t* Paddr,
                                      rme_ptr_t* Size_Order, rme_ptr_t* Num_Order, rme_ptr_t* Flags);

/*****************************************************************************/
/* Undefine "__EXTERN__" to avoid redefinition */
#undef __EXTERN__
/* __RME_PLATFORM_A7M_MEMBERS__ */
#endif
/* !(defined __HDR_DEFS__||defined __HDR_STRUCTS__) */
#endif
/* End Public C Function Prototypes ******************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/