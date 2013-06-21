/*
 *  Chack'n Pop (C) 1983 TAITO Corp.
 *  simulate 68705 MCU
 */

#include "emu.h"
#include "cpu/z80/z80.h"
#include "includes/chaknpop.h"


/* mcu data that is extracted from the real board! */
/* updated on 2st Jun 2003 */
static const UINT8 mcu_data[256] = {
	0x3a, 0xe6, 0x80, 0xc6, 0x0e, 0xdd, 0x77, 0xfd,
	0x7e, 0xfe, 0x10, 0x38, 0x10, 0xdd, 0x7e, 0x03,
	0xc6, 0x08, 0xdd, 0x77, 0x03, 0xdd, 0x7e, 0xff,
	0xc6, 0x08, 0xdd, 0x77, 0xff, 0x34, 0x23, 0xc9,
	0x06, 0x10, 0xdd, 0xe5, 0xe1, 0x23, 0x23, 0x23,
	0x4e, 0x23, 0x5e, 0x23, 0x56, 0x23, 0x23, 0x7b,
	0xb2, 0x28, 0x02, 0x79, 0x12, 0x10, 0xf1, 0xc9,
	0xe6, 0x03, 0x87, 0x87, 0x6f, 0x26, 0x00, 0x29,
	0x29, 0x29, 0xe5, 0x29, 0x29, 0x29, 0xc1, 0x09,
	0x01, 0xc3, 0x81, 0x09, 0xe5, 0xdd, 0xe1, 0xc9,
	0x10, 0x00, 0x08, 0x10, 0x20, 0x64, 0x50, 0x00,
	0x08, 0x50, 0xb0, 0x01, 0x34, 0xa0, 0x13, 0x34,
	0xb0, 0x05, 0x34, 0xc0, 0x04, 0x34, 0xd0, 0x02,
	0x34, 0xf0, 0x02, 0x34, 0x00, 0x60, 0x00, 0x00,
	0x3f, 0x00, 0x0c, 0x1f, 0xa0, 0x3f, 0x1e, 0xa2,
	0x01, 0x1e, 0xa1, 0x0a, 0x1e, 0xa2, 0x07, 0x1e,
	0x92, 0x05, 0x1e, 0x02, 0x04, 0x1e, 0x12, 0x09,
	0x3f, 0x22, 0x06, 0x3f, 0x21, 0x03, 0x3f, 0x20,
	0x02, 0x00, 0x00, 0x3f, 0x00, 0x04, 0x02, 0xa0,
	0x40, 0x12, 0xa1, 0x06, 0x12, 0xa2, 0x02, 0x12,
	0xa1, 0x0a, 0x12, 0xa2, 0x07, 0x10, 0x92, 0x05,
	0x10, 0x02, 0x04, 0x12, 0x12, 0x09, 0x12, 0x22,
	0x06, 0x12, 0x21, 0x03, 0x12, 0x20, 0x02, 0x26,
	0x00, 0x14, 0x12, 0x00, 0x00, 0x00, 0x3f, 0x00,
	0x04, 0x1a, 0xa0, 0x40, 0x3f, 0x00, 0x00, 0x00,
	0x3e, 0x3a, 0x87, 0x83, 0x3c, 0x32, 0x87, 0x83,
	0x0f, 0x0f, 0xe6, 0x07, 0xfe, 0x02, 0x20, 0x01,
	0xaf, 0x11, 0x40, 0x98, 0x1d, 0x12, 0x1d, 0x20,
	0xfb, 0x2a, 0x89, 0x83, 0x2b, 0x22, 0x89, 0x83,
	0xc9, 0x3a, 0x5b, 0x81, 0xa7, 0xc0, 0x21, 0x80,
	0x81, 0x11, 0x04, 0x00, 0x06, 0x09, 0x34, 0x19,
	0x10, 0xfc, 0x3e, 0x01, 0x32, 0x5b, 0x81, 0xc9
};

static void mcu_update_seed( running_machine &machine, UINT8 data )
{
	chaknpop_state *state = machine.driver_data<chaknpop_state>();

	if (!(data & 0x80))
	{
		state->m_mcu_seed += 0x83;
		state->m_mcu_seed = (state->m_mcu_seed & 0x80) | (state->m_mcu_seed >> 1);
	}

	state->m_mcu_seed += 0x19;

	//logerror("New seed: 0x%02x\n", state->m_mcu_seed);
}


/***************************************************************************
  Memory handlers
***************************************************************************/

READ8_MEMBER(chaknpop_state::chaknpop_mcu_port_a_r)
{
	//logerror("%04x: MCU port_a read\n", space.device().safe_pc());
	return m_mcu_result;
}


READ8_MEMBER(chaknpop_state::chaknpop_mcu_port_b_r)
{
	//logerror("%04x: MCU port_b read\n", space.device().safe_pc());

	return 0xff;
}

READ8_MEMBER(chaknpop_state::chaknpop_mcu_port_c_r)
{
	//logerror("%04x: MCU port_c read\n", space.device().safe_pc());
	return 0x00;
}

WRITE8_MEMBER(chaknpop_state::chaknpop_mcu_port_a_w)
{
	UINT8 mcu_command;

	mcu_command = data + m_mcu_seed;
	m_mcu_result = 0;

	if (mcu_command < 0x08)
	{
		mcu_update_seed(machine(), data);

		m_mcu_result = mcu_data[m_mcu_select * 8 + mcu_command];
		m_mcu_result -= m_mcu_seed;

		mcu_update_seed(machine(), m_mcu_result);

		logerror("%04x: MCU command 0x%02x, result 0x%02x\n", space.device().safe_pc(), mcu_command, m_mcu_result);
	}
	else if (mcu_command >= 0x28 && mcu_command <= 0x2a)
	{
		mcu_update_seed(machine(), data);

		m_mcu_result = m_mcu_ram[0x380 + mcu_command];
		m_mcu_result -= m_mcu_seed;

		mcu_update_seed(machine(), m_mcu_result);

		logerror("%04x: MCU command 0x%02x, result 0x%02x\n", space.device().safe_pc(), mcu_command, m_mcu_result);
	}
	else if (mcu_command < 0x80)
	{
		mcu_update_seed(machine(), data);

		if (mcu_command >= 0x40 && mcu_command < 0x60)
		{
			m_mcu_select = mcu_command - 0x40;

			logerror("%04x: MCU select 0x%02x\n", space.device().safe_pc(), m_mcu_select);
		}
	}
	else if (mcu_command == 0x9c|| mcu_command == 0xde)
	{
		mcu_update_seed(machine(), data);

		logerror("%04x: MCU command 0x%02x\n", space.device().safe_pc(), mcu_command);
	}
}

WRITE8_MEMBER(chaknpop_state::chaknpop_mcu_port_b_w)
{
	//logerror("%04x: MCU port_b write 0x%02x\n", space.device().safe_pc(), data);
}

WRITE8_MEMBER(chaknpop_state::chaknpop_mcu_port_c_w)
{
	//logerror("%04x: MCU port_c write 0x%02x\n", space.device().safe_pc(), data);
}