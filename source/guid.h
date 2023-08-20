
#pragma once

#include "types.h"

// 48bit-guid

// collision probabilities:

//  N     Collision chance
// 100K        0.002%
// 500K        0.05%
//   1M        0.2%
//   2M        0.7%
//   3M        1.5%
//  10M        16%
//  20M        50%

struct guid
{
	byte bytes[6];
};