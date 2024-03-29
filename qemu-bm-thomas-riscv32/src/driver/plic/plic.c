/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 *   Samuel Holland <samuel@sholland.org>
 */

#include "common.h"
#include "plic.h"

#define PLIC_PRIORITY_BASE 0x04
#define PLIC_PENDING_BASE 0x1000
#define PLIC_ENABLE_BASE 0x2000
#define PLIC_ENABLE_STRIDE 0x80
#define PLIC_CONTEXT_BASE 0x200000
#define PLIC_CONTEXT_STRIDE 0x1000
#define PLIC_CONTEXT_CLAIM_OFFSET 4UL

uint32_t plic_get_claim(const struct plic_data *plic)
{
    volatile void *plic_claim = (char *)plic->addr +
            PLIC_CONTEXT_BASE + PLIC_CONTEXT_CLAIM_OFFSET;
    return read_mreg32(plic_claim);
}

void plic_set_claim(const struct plic_data *plic, uint32_t source)
{
    volatile void *plic_claim = (char *)plic->addr +
            PLIC_CONTEXT_BASE + PLIC_CONTEXT_CLAIM_OFFSET;
    write_mreg32(plic_claim, source);
}

uint32_t plic_get_priority(const struct plic_data *plic, uint32_t source)
{
    volatile void *plic_priority = (char *)plic->addr +
            PLIC_PRIORITY_BASE + 4 * source;
    return read_mreg32(plic_priority);
}

void plic_set_priority(const struct plic_data *plic, uint32_t source, uint32_t val)
{
    volatile void *plic_priority = (char *)plic->addr +
            PLIC_PRIORITY_BASE + 4 * source;
    write_mreg32(plic_priority, val);
}

void plic_priority_save(const struct plic_data *plic, uint8_t *priority)
{
    for (uint32_t i = 0; i < plic->num_src; i++)
        priority[i] = plic_get_priority(plic, i);
}

void plic_priority_restore(const struct plic_data *plic, const uint8_t *priority)
{
    for (uint32_t i = 0; i < plic->num_src; i++)
        plic_set_priority(plic, i, priority[i]);
}

uint32_t plic_get_thresh(const struct plic_data *plic, uint32_t cntxid)
{
    volatile void *plic_thresh;

    plic_thresh = (char *)plic->addr +
              PLIC_CONTEXT_BASE + PLIC_CONTEXT_STRIDE * cntxid;

    return read_mreg32(plic_thresh);
}

void plic_set_thresh(const struct plic_data *plic, uint32_t cntxid, uint32_t val)
{
    volatile void *plic_thresh;

    plic_thresh = (char *)plic->addr +
              PLIC_CONTEXT_BASE + PLIC_CONTEXT_STRIDE * cntxid;
    write_mreg32(plic_thresh, val);
}

uint32_t plic_get_ie(const struct plic_data *plic, uint32_t cntxid,
                     uint32_t word_index)
{
    volatile void *plic_ie;

    plic_ie = (char *)plic->addr +
           PLIC_ENABLE_BASE + PLIC_ENABLE_STRIDE * cntxid +
           4 * word_index;

    return read_mreg32(plic_ie);
}

void plic_set_ie(const struct plic_data *plic, uint32_t cntxid,
                 uint32_t word_index, uint32_t val)
{
    volatile void *plic_ie;

    plic_ie = (char *)plic->addr +
           PLIC_ENABLE_BASE + PLIC_ENABLE_STRIDE * cntxid +
           4 * word_index;
    write_mreg32(plic_ie, val);
}

void plic_context_save(const struct plic_data *plic, int context_id,
                       uint32_t *enable, uint32_t *threshold)
{
    uint32_t ie_words = (plic->num_src + 31) / 32;

    for (uint32_t i = 0; i < ie_words; i++)
        enable[i] = plic_get_ie(plic, context_id, i);

    *threshold = plic_get_thresh(plic, context_id);
}

void plic_context_restore(const struct plic_data *plic, int context_id,
                          const uint32_t *enable, uint32_t threshold)
{
    uint32_t ie_words = (plic->num_src + 31) / 32;

    for (uint32_t i = 0; i < ie_words; i++)
        plic_set_ie(plic, context_id, i, enable[i]);

    plic_set_thresh(plic, context_id, threshold);
}

int plic_context_init(const struct plic_data *plic, int context_id,
                      bool enable, uint32_t threshold)
{
    uint32_t ie_words, ie_value;

    if (!plic || context_id < 0)
        return -1;

    ie_words = (plic->num_src + 31) / 32;
    ie_value = enable ? 0xffffffffU : 0U;

    for (uint32_t i = 0; i < ie_words; i++)
        plic_set_ie(plic, context_id, i, ie_value);

    plic_set_thresh(plic, context_id, threshold);

    return 0;
}

int plic_warm_irqchip_init(const struct plic_data *plic,
                           int m_cntx_id, int s_cntx_id)
{
    int ret;

    /* By default, disable all IRQs for M-mode of target HART */
    if (m_cntx_id > -1) {
        ret = plic_context_init(plic, m_cntx_id, false, 0x7);
        if (ret)
            return ret;
    }

    /* By default, disable all IRQs for S-mode of target HART */
    if (s_cntx_id > -1) {
        ret = plic_context_init(plic, s_cntx_id, false, 0x7);
        if (ret)
            return ret;
    }

    return 0;
}

int plic_cold_irqchip_init(const struct plic_data *plic)
{
    int i;

    if (!plic)
        return -1;

    /* Configure default priorities of all IRQs */
    for (i = 1; i <= plic->num_src; i++)
        plic_set_priority(plic, i, 2);

    return 0;
}
