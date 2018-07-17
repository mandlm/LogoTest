#pragma once

#include "PRMap.h"

class GenusPR : public PRMap
{
public:
	GenusPR()
	{
		// clang-format off
		m_ages = {
			{ 4, 0 },
			{ 5, 0 },
			{ 6, 0 },
			{ 7, 0 },
			{ 8, 0 },
			{ 9, 0 }
		};

		m_PRs = {
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 2, 1, 0, 0, 0 },
			{ 3, 1, 1, 0, 0 },
			{ 9, 1, 1, 0, 0 },
			{ 13, 3, 2, 0, 0 },
			{ 14, 5, 2, 1, 0 },
			{ 19, 7, 2, 1, 0 },
			{ 22, 8, 3, 1, 0 },
			{ 27, 10, 4, 2, 0 },
			{ 31, 13, 5, 2, 0 },
			{ 35, 17, 7, 2, 0 },
			{ 39, 18, 7, 2, 0 },
			{ 46, 20, 8, 2, 0 },
			{ 51, 23, 9, 2, 1 },
			{ 56, 26, 11, 2, 1 },
			{ 62, 34, 17, 4, 1 },
			{ 71, 47, 22, 8, 4 },
			{ 81, 57, 29, 17, 9 },
			{ 94, 75, 49, 37, 27 },
			{ 100, 100, 100, 100, 100 },
		};
		// clang-format on
	}
};
