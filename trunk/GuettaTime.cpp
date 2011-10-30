/* 
 * File:   GuettaTime.cpp
 * Author: jose
 * 
 * Created on 16 de octubre de 2011, 20:33
 */

#include "GuettaTime.h"

GuettaTime::GuettaTime() 
{
    initialTime = 0;
}

void GuettaTime::start()
{
    initialTime = getTimeMs();
}

double GuettaTime::stop()
{
    return getTimeMs()-initialTime;
}

double GuettaTime::getTimeMs() const
{
	ptime t3 = microsec_clock::local_time();
	time_duration t4 = t3.time_of_day();
	return t4.total_milliseconds();
}