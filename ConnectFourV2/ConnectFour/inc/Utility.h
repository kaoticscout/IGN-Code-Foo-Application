#ifndef UTILITY_H
#define UTILITY_H

static int Round(float num)
{
	if(num + 0.5 >= static_cast<int>(num+1))
		return static_cast<int>(num+1);
	else
		return static_cast<int>(num);
}

#endif