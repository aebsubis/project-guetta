/* 
 * File:   GuettaTime.h
 * Author: jose
 *
 * Created on 16 de octubre de 2011, 20:33
 */

#ifndef GUETTATIME_H
#define	GUETTATIME_H

#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o
#include "boost/date_time/posix_time/posix_time_types.hpp" //no i/o just types
#include "boost/date_time/gregorian/gregorian.hpp" //include all types plus i/o
#include "boost/date_time/gregorian/gregorian_types.hpp" //no i/o just types
using namespace boost::posix_time;
using namespace boost::gregorian;

class GuettaTime {
public:
    GuettaTime();
    void start();
    double stop();
private:
    double initialTime;
    
    double getTimeMs() const;

};

#endif	/* GUETTATIME_H */

