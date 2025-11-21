#ifndef _KPI_H_
#define _KPI_H_

#include <stdint.h>

typedef enum {
	KPI_EV_NONE = 0,
	KPI_EV_SHORT,
	KPI_EV_LONG,
	KPI_EV_DOUBLE,
	KPI_EV_TRIPLE,
} kpi_event_type_e;

typedef struct {
	kpi_event_handler_t handler;
	uint32_t tick;
	uint32_t *tick_buf;
	int button_count;
} kpi_bank_t;

typedef struct {
	kpi_event_type_e type;
	int button;
} kpi_event_t;

typedef void(*kpi_event_handler_t)(kpi_event_t);

int kpi_bank_init_static(kpi_bank_t *bank, kpi_event_handler_t handler, uint32_t *tick_buf, int button_count);
int kpi_bank_destroy(kpi_bank_t *bank);

int kpi_tick(kpi_bank_t *bank, uint32_t button_mask);

#endif
