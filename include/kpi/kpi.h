#ifndef _KPI_H_
#define _KPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define KPI_MAX_BUTTONS 32

typedef enum {
        KPI_EV_NONE = 0,
        KPI_EV_SHORT,
        KPI_EV_LONG,
        KPI_EV_DOUBLE,
        KPI_EV_TRIPLE,
} kpi_event_type_e;

typedef enum {
        _KPI_STATE_UP_NONE = 0,		//Not pressed and no state
        _KPI_STATE_DOWN1,		//First press and waiting for long
        _KPI_STATE_DOWN_LONG,		//Long limit elapsed
        _KPI_STATE_UP1,			//Short and waiting for double
        _KPI_STATE_DOWN2,		//Second tap still down
        _KPI_STATE_UP2,			//Second tap up, waiting for third
        _KPI_STATE_DOWN3,		//Third tap still down
} kpi_button_state_e;

typedef struct kpi_event {
        kpi_event_type_e type;
        int button;
} kpi_event_t;

typedef void(*kpi_event_handler_t)(kpi_event_t ev);

typedef struct kpi_bank {
        kpi_event_handler_t handler;
        uint32_t tick;
        uint32_t tick_buf[KPI_MAX_BUTTONS];
        kpi_button_state_e state_buf[KPI_MAX_BUTTONS];
        int button_count;
        uint32_t long_tks;
        uint32_t mtap_tks;
} kpi_bank_t;



int kpi_bank_init_static(kpi_bank_t *bank, kpi_event_handler_t handler, int button_count,
                         uint32_t long_tks, uint32_t mtap_tks);
int kpi_bank_destroy(kpi_bank_t *bank);

int kpi_tick(kpi_bank_t *bank, uint32_t button_mask);

#ifdef __cplusplus
}
#endif

#endif
