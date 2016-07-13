#include "Input.hpp"

namespace bas {

	Input::Input()
	{
		load();
	}

	void Input::load()
	{
		for (int i = 0; i < (int)Action::TOTAL; i++)
		{
			for (int j = 0; j < NUM_TRIGGERS; j++)
			{
				m_Triggers[i][j] = config::config1[i][j];
			}
		}
	}

	void Input::set(Type type, int code, bool value)
	{
		int Icode = getCode(type, code);

		int flank;
		if (value)
			flank = 1;
		else
			flank = -1;

		for (int i = 0; i < (int)Action::TOTAL; i++)
		{
			for (int j = 0; j < NUM_TRIGGERS; j++)
			{
				if (Icode == m_Triggers[i][j])
				{
					m_Input[i] = value;
					m_Flank[i] = flank;
				}
			}
		}
	}

	void Input::set2D(Type type, int dx, int dy)
	{
		/* Fil dis pls */
	}

	bool Input::getInput(int k)
	{
		return m_Input[k];
	}

	bool Input::getPress(int k)
	{
		return m_Flank[k] == 1;
	}

	bool Input::getRelease(int k)
	{
		return m_Flank[k] == -1;
	}

	void Input::clear()
	{
		for (int i = 0; i < (int)Action::TOTAL; i++)
			m_Flank[i] = 0;
	}

	int Input::getCode(Type type, int k)
	{
		return (int)type + k;
	}

}