/*******************************************************************
*
*  DESCRIPTION: Atomic Model TrigAssy
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

#ifndef __TRIGASSY_H
#define __TRIGASSY_H

#include "atomic.h"     // class Atomic

class TrigAssy : public Atomic
{
public:
	TrigAssy( const string &name = "TrigAssy" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_triggerPressed, &in_firingSelector, &in_boltBack;
	Port &out_releaseBolt;
	Time preparationTime;

	int triggerPull;	//0 if the trigger has no tension, 1 if the trigger has tension
	int FSstate;		//the state of the Firing Selector, 0 for safe, 1 for single, 2 for automatic

};	// class TrigAssy

// ** inline ** //
inline string TrigAssy::className() const
{
	return "TrigAssy" ;
}

#endif   //__TRIGASSY_H
