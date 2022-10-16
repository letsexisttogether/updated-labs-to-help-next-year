#pragma once

#define _COMP_BEGIN_ namespace Comps {
#define _COMP_END_					 }

_COMP_BEGIN_

template <class _CType>
bool SimpleComp(_CType leftValue, _CType rightValue)
{
	return leftValue == rightValue;
}

_COMP_END_