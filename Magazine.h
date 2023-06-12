/*******************************************************************
*
*  DESCRIPTION: Atomic Model Magazine
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

#ifndef __MAGAZINE_H
#define __MAGAZINE_H

#include "atomic.h"     // class Atomic

class Magazine : public Atomic
{
public:
	Magazine( const string &name = "Magazine" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_initBullets, &in_initMagSeating, &in_bulletLoaded;
	Port &out_bulletReady;
	Time preparationTime;

	int bulletsLeft;		//the total number of bullets that are in the magazine. from 0 to 30
	int magSeating;			//whether the magazine is seated correctly in the housing (1) or not (0)
	int bulletReady;		//if a bullet is ready to be loaded (ie. seated properly in magazine 1, or not, 0)
	int tempMsgVal;

};	// class Magazine

// ** inline ** //
inline string Magazine::className() const
{
	return "Magazine" ;
}

#endif   //__MAGAZINE_H
