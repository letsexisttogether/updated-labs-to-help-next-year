#pragma once

#define _COMP_BEGIN_ namespace Comps {
#define _COMP_END_					 }

#include <stdint.h>

#include "../Menu/MenuItem.h"

_COMP_BEGIN_

template <class _CType>
bool SimpleComp(const _CType& leftValue, const _CType& rightValue)
{
	return leftValue == rightValue;
}

template <class _FType, class _SType>
bool DiffTypeValuesComp(const _FType& first, const _SType second)
{
	return first == second;
}

bool ItemIndexComp(const MenuItem& item, const uint16_t& index)
{
	return item.getIndex() == index;
}

_COMP_END_