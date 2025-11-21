#include "kpi.h"

#include <string.h>
#include <errno.h>
#include <stdbool.h>

int kpi_bank_init_static(kpi_bank_t *bank, kpi_event_handler_t handler, int button_count,
                         uint32_t long_tks, uint32_t mtap_tks)
{
	if (bank == NULL || handler == NULL ||
		button_count < 0 || button_count > KPI_MAX_BUTTONS)
		return -EINVAL;

	bank->tick = 0;
	bank->button_count = button_count;
	bank->handler = handler;
	bank->long_tks = long_tks;
	bank->mtap_tks = mtap_tks;

	memset(bank->tick_buf, 0, sizeof(bank->tick_buf[0]) * button_count);
	memset(bank->state_buf, 0, sizeof(bank->state_buf[0]) * button_count);

	return 0;
}

int kpi_bank_destroy(kpi_bank_t *bank)
{
	if (bank == NULL)
		return -EINVAL;

	//Nothing really needed
	bank->handler = NULL;

	return 0;
}

static kpi_event_type_e kpi_state_machine(kpi_bank_t *bank, bool pressed, int i)
{
	uint32_t elapsed = bank->tick - bank->tick_buf[i];

	switch (bank->state_buf[i])
	{
	case _KPI_STATE_UP_NONE:
		if (!pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_DOWN1;
		bank->tick_buf[i] = bank->tick;
		return KPI_EV_NONE;

	case _KPI_STATE_DOWN1:
		if (elapsed == bank->long_tks)
		{
			bank->state_buf[i] = _KPI_STATE_DOWN_LONG;
			return KPI_EV_NONE;
		}
		if (pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_UP1;
		bank->tick_buf[i] = bank->tick;
		return KPI_EV_NONE;

	case _KPI_STATE_DOWN_LONG:
		if (pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_UP_NONE;
		return KPI_EV_LONG;

	case _KPI_STATE_UP1:
		if (elapsed == bank->mtap_tks)
		{
			bank->state_buf[i] = _KPI_STATE_UP_NONE;
			return KPI_EV_SHORT;
		}
		if (!pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_DOWN2;
		bank->tick_buf[i] = bank->tick;
		return KPI_EV_NONE;

	case _KPI_STATE_DOWN2:
		if (pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_UP2;
		bank->tick_buf[i] = bank->tick;
		return KPI_EV_NONE;

	case _KPI_STATE_UP2:
		if (elapsed == bank->mtap_tks)
		{
			bank->state_buf[i] = _KPI_STATE_UP_NONE;
			return KPI_EV_DOUBLE;
		}
		if (!pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_DOWN3;
		bank->tick_buf[i] = bank->tick;
		return KPI_EV_NONE;

	case _KPI_STATE_DOWN3:
		if (pressed) return KPI_EV_NONE;

		bank->state_buf[i] = _KPI_STATE_UP_NONE;
		return KPI_EV_TRIPLE;
	}

	//REVIEW: Use assert here?
	return KPI_EV_NONE;
}

int kpi_tick(kpi_bank_t *bank, uint32_t button_mask)
{
	if (bank == NULL)
		return -EINVAL;

	++bank->tick;

	for (int i = 0; i < bank->button_count; ++i)
	{
		uint32_t mask = 1 << i;
		bool pressed = (button_mask & mask) != 0;

		kpi_event_type_e type = kpi_state_machine(bank, pressed, i);
		if (type != KPI_EV_NONE)
		{
			kpi_event_t ev;
			ev.button = i;
			ev.type = type;
			bank->handler(ev);
		}
	}

	return 0;
}
