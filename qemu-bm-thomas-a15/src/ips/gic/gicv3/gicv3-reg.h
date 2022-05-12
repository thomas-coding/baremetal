/*
 * GICv3 register
 *
 * Author: Zhigang.Kang <Zhigang.Kang@verisilicon.com>
 *
 * Copyright (C) 2020 VeriSilicon Microelectronics (Shanghai) Co., Ltd.
 *
 */

#ifndef __GICV3_REG_H__
#define __GICV3_REG_H__

/*
 * Distributor registers.
 */
#define GICD_CTLR			0x0000
#define GICD_TYPER			0x0004
#define GICD_IIDR			0x0008
#define GICD_STATUSR			0x0010
#define GICD_SETSPI_NSR			0x0040
#define GICD_CLRSPI_NSR			0x0048
#define GICD_SETSPI_SR			0x0050
#define GICD_CLRSPI_SR			0x0058
#define GICD_SEIR			0x0068
#define GICD_IGROUPR			0x0080
#define GICD_ISENABLER			0x0100
#define GICD_ICENABLER			0x0180
#define GICD_ISPENDR			0x0200
#define GICD_ICPENDR			0x0280
#define GICD_ISACTIVER			0x0300
#define GICD_ICACTIVER			0x0380
#define GICD_IPRIORITYR			0x0400
#define GICD_ITARGETSR			0x0800
#define GICD_ICFGR			0x0c00
#define GICD_IGRPMODR			0x0d00
#define GICD_NSACR			0x0e00
#define GICD_SGIR			0x0f00
#define GICD_CPENDSGIR			0x0f10
#define GICD_SPENDSGIR			0x0f20
#define GICD_IROUTER			0x6000	/* 0 to 31 are reserved. */
#define GICD_IDREGS			0xffd0
#define GICD_PIDR2			0xffe8

#define GICD_TYPER_RSS			(1U << 26)
#define GICD_TYPER_LPIS			(1U << 17)
#define GICD_TYPER_MBIS			(1U << 16)

#define GICD_TYPER_ID_BITS(typer)	((((typer) >> 19) & 0x1f) + 1)
#define GICD_TYPER_NUM_LPIS(typer)	((((typer) >> 11) & 0x1f) + 1)
#define GICD_TYPER_IRQS(typer)		((((typer) & 0x1f) + 1) * 32)

/*
 * Re-Distributor registers, offsets from RD_base
 */
#define GICR_CTLR			0x0000
#define GICR_IIDR			0x0004
#define GICR_TYPER			0x0008
#define GICR_STATUSR			0x0010
#define GICR_WAKER			0x0014
#define GICR_FCTLR			0x0020
#define GICR_PWRR			0x0024
#define GICR_CLASS			0x0028
#define GICR_SETLPIR			0x0040
#define GICR_CLRLPIR			0x0048
#define GICR_PROPBASER			0x0070
#define GICR_PENDBASER			0x0078
#define GICR_INVLPIR			0x00a0
#define GICR_INVALLR			0x00b0
#define GICR_SYNCR			0x00c0
#define GICR_PIDR2			0xffe8

#define GICR_CTLR_ENABLE_LPIS		(1UL << 0)
#define GICR_CTLR_RWP			(1UL << 3)

#define GICR_TYPER_CPU_NUMBER(r)	(((r) >> 8) & 0xffff)

#define GICR_WAKER_ProcessorSleep	(1U << 1)
#define GICR_WAKER_ChildrenAsleep	(1U << 2)

#define GIC_BASER_CACHE_nCnB		0ULL
#define GIC_BASER_CACHE_SameAsInner	0ULL
#define GIC_BASER_CACHE_nC		1ULL
#define GIC_BASER_CACHE_RaWt		2ULL
#define GIC_BASER_CACHE_RaWb		3ULL
#define GIC_BASER_CACHE_WaWt		4ULL
#define GIC_BASER_CACHE_WaWb		5ULL
#define GIC_BASER_CACHE_RaWaWt		6ULL
#define GIC_BASER_CACHE_RaWaWb		7ULL
#define GIC_BASER_CACHE_MASK		7ULL
#define GIC_BASER_NonShareable		0ULL
#define GIC_BASER_InnerShareable	1ULL
#define GIC_BASER_OuterShareable	2ULL
#define GIC_BASER_SHAREABILITY_MASK	3ULL

#define GIC_BASER_CACHEABILITY(reg, inner_outer, type)			\
	(GIC_BASER_CACHE_##type << reg##_##inner_outer##_CACHEABILITY_SHIFT)

#define GIC_BASER_SHAREABILITY(reg, type)				\
	(GIC_BASER_##type << reg##_SHAREABILITY_SHIFT)

#define GICR_PROPBASER_OUTER_CACHEABILITY_SHIFT		56
#define GICR_PROPBASER_OUTER_CACHEABILITY_MASK				\
	(7UL << GICR_PROPBASER_OUTER_CACHEABILITY_SHIFT)
#define GICR_PROPBASER_SHAREABILITY_SHIFT		10
#define GICR_PROPBASER_SHAREABILITY_MASK				\
	(3UL << GICR_PROPBASER_SHAREABILITY_SHIFT)
#define GICR_PROPBASER_INNER_CACHEABILITY_SHIFT		7
#define GICR_PROPBASER_INNER_CACHEABILITY_MASK				\
	(7UL << GICR_PROPBASER_INNER_CACHEABILITY_SHIFT)
#define GICR_PROPBASER_RES0_MASK					\
	(GENMASK(63, 59) | GENMASK(55, 52) | GENMASK(6, 5))

#define GICR_PENDBASER_SHAREABILITY_SHIFT		10
#define GICR_PENDBASER_INNER_CACHEABILITY_SHIFT		7
#define GICR_PENDBASER_OUTER_CACHEABILITY_SHIFT		56
#define GICR_PENDBASER_SHAREABILITY_MASK				\
	(3UL << GICR_PENDBASER_SHAREABILITY_SHIFT)
#define GICR_PENDBASER_INNER_CACHEABILITY_MASK				\
	(7UL << GICR_PENDBASER_INNER_CACHEABILITY_SHIFT)
#define GICR_PENDBASER_OUTER_CACHEABILITY_MASK				\
	(7UL << GICR_PENDBASER_OUTER_CACHEABILITY_SHIFT)
#define GICR_PENDBASER_PTZ				BIT(62)
#define GICR_PENDBASER_RES0_MASK					\
	(BIT(63) | GENMASK(61, 59) | GENMASK(55, 52) |			\
	GENMASK(15, 12) | GENMASK(6, 0))

#define GICR_PROPBASER_nCnB			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, nCnB)
#define GICR_PROPBASER_nC			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, nC)
#define GICR_PROPBASER_RaWt			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, RaWt)
#define GICR_PROPBASER_RaWb			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, RaWt)
#define GICR_PROPBASER_WaWt			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, WaWt)
#define GICR_PROPBASER_WaWb			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, WaWb)
#define GICR_PROPBASER_RaWaWt			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, RaWaWt)
#define GICR_PROPBASER_RaWaWb			\
	GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, RaWaWb)

#define GICR_PROPBASER_IDBITS_MASK			(0x1f)
#define GICR_PROPBASER_ADDRESS(x)	((x) & GENMASK_ULL(51, 12))
#define GICR_PENDBASER_ADDRESS(x)	((x) & GENMASK_ULL(51, 16))

/*
 * Re-Distributor registers, offsets from SGI_base
 */
#define GICR_IGROUPR0			0x0080
#define GICR_ISENABLER0			0x0100
#define GICR_ICENABLER0			0x0180
#define GICR_ISPENDR0			0x0200
#define GICR_ICPENDR0			0x0280
#define GICR_ISACTIVER0			0x0300
#define GICR_ICACTIVER0			0x0380
#define GICR_IPRIORITYR0		0x0400
#define GICR_ICFGR0			0x0c00
#define GICR_IGRPMODR0			0x0d00
#define GICR_NSACR			0x0e00

#define GICR_TYPER_PLPIS		(1U << 0)
#define GICR_TYPER_VLPIS		(1U << 1)
#define GICR_TYPER_DirectLPIS		(1U << 3)
#define GICR_TYPER_LAST			(1U << 4)

#define GICV3_REDIST_SIZE		0x20000
#define GICV3_REDIST_RD_OFF		0x00000
#define GICV3_REDIST_SGI_OFF		0x10000

/*
 * ITS registers, offsets from ITS_base
 */
#define GITS_CTLR			0x0000
#define GITS_IIDR			0x0004
#define GITS_TYPER			0x0008
#define GITS_CBASER			0x0080
#define GITS_CWRITER			0x0088
#define GITS_CREADR			0x0090
#define GITS_BASER_NR_REGS		8
#define GITS_BASER			0x0100
#define GITS_IDREGS_BASE		0xffd0
#define GITS_PIDR0			0xffe0
#define GITS_PIDR1			0xffe4
#define GITS_PIDR2			0xffe8
#define GITS_PIDR4			0xffd0
#define GITS_CIDR0			0xfff0
#define GITS_CIDR1			0xfff4
#define GITS_CIDR2			0xfff8
#define GITS_CIDR3			0xfffc

#define GITS_TRANSLATER			0x10040

/* Register bits */
#define GITS_VALID_BIT			(1ULL << 63)

#define GITS_CTLR_ENABLE		(1U << 0)
#define GITS_CTLR_ImDe			(1U << 1)
#define	GITS_CTLR_ITS_NUMBER_SHIFT	4
#define	GITS_CTLR_ITS_NUMBER		(0xFU << GITS_CTLR_ITS_NUMBER_SHIFT)
#define GITS_CTLR_QUIESCENT		(1U << 31)

#define GITS_TYPER_PTA			(1U << 19)
#define GITS_TYPER_DEVIDS_SHIFT		13
#define GITS_TYPER_DEVIDS_MASK		(0x1fUL << GITS_TYPER_DEVIDS_SHIFT)
#define GITS_TYPER_DEVICE_ID_BITS(r)	(((r & GITS_TYPER_DEVIDS_MASK) >> \
						GITS_TYPER_DEVIDS_SHIFT) + 1)

#define GITS_TYPER_IDBITS_SHIFT		8
#define GITS_TYPER_IDBITS_MASK		(0x1fUL << GITS_TYPER_IDBITS_SHIFT)
#define GITS_TYPER_EVENT_ID_BITS(r)	(((r & GITS_TYPER_IDBITS_MASK) >> \
						GITS_TYPER_IDBITS_SHIFT) + 1)

#define GITS_TYPER_ITT_SIZE_SHIFT	4
#define GITS_TYPER_ITT_SIZE_MASK	(0xfUL << GITS_TYPER_ITT_SIZE_SHIFT)
#define GITS_TYPER_ITT_SIZE(r)		((((r) & GITS_TYPER_ITT_SIZE_MASK) >> \
						GITS_TYPER_ITT_SIZE_SHIFT) + 1)
#define GITS_TYPER_PHYSICAL		(1U << 0)

#define GITS_BASER_INDIRECT		(1U << 62)
#define GITS_BASER_INNER_CACHEABILITY_SHIFT	59
#define GITS_BASER_TYPE_SHIFT		56
#define GITS_BASER_TYPE_MASK		(7ULL << GITS_BASER_TYPE_SHIFT)
#define GITS_BASER_OUTER_CACHEABILITY_SHIFT	53
#define GITS_BASER_TYPE_NONE		0UL
#define GITS_BASER_TYPE_DEVICE		1UL
#define GITS_BASER_TYPE_VCPU		2UL
#define GITS_BASER_TYPE_CPU		3UL
#define GITS_BASER_TYPE_COLLECTION	4UL
#define GITS_BASER_TYPE_RESERVED5	5UL
#define GITS_BASER_TYPE_RESERVED6	6UL
#define GITS_BASER_TYPE_RESERVED7	7UL
#define GITS_BASER_ENTRY_SIZE_SHIFT	48
#define GITS_BASER_ENTRY_SIZE(reg)					\
			(((reg >> GITS_BASER_ENTRY_SIZE_SHIFT) & 0x1f) + 1)
#define GITS_BASER_SHAREABILITY_SHIFT	10
#define GITS_BASER_PAGE_SIZE_SHIFT	8
#define GITS_BASER_SIZE_MASK		0xff
#define GITS_BASER_SHAREABILITY_MASK			\
	(0x3ULL << GITS_BASER_SHAREABILITY_SHIFT)
#define GITS_BASER_OUTER_CACHEABILITY_MASK		\
	(0x7ULL << GITS_BASER_OUTER_CACHEABILITY_SHIFT)
#define GITS_BASER_INNER_CACHEABILITY_MASK		\
	(0x7ULL << GITS_BASER_INNER_CACHEABILITY_SHIFT)

#define GITS_CBASER_SIZE_MASK		0xff

#endif /* __GICV3_REG_H__ */
