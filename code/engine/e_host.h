#pragma once

class EHost
{
public:
	~EHost();
	EHost();

	bool	Update( uint dt );
};
extern EHost*	gHost;
