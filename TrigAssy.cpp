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

/** include files **/

#include "TrigAssy.h"		// class TrigAssy
#include "message.h"		// class ExternalMessage, InternalMessage
#include "mainsimu.h"		// MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: TrigAssy
* Description: The Trigger Assembly (TrigAssy) encompasses the trigger
* and the Firing Selector Assembly group. It decides whether or not it
* can release the Bolt catch, based on the initial inputs.
********************************************************************/

TrigAssy::TrigAssy( const string &name )
: Atomic( name )
, in_triggerPressed( addInputPort( "in_triggerPressed") )
, in_firingSelector( addInputPort( "in_firingSelector") )
, in_boltBack( addInputPort( "in_boltBack") )
, out_releaseBolt( addOutputPort( "out_releaseBolt") )
, preparationTime ( 0, 0, 0, 0 )								//time for an action, specifically TrigAssy mechanics
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;
	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Initializes the current function parameters
********************************************************************/
Model &TrigAssy::initFunction()
{
	FSstate = 1;		//by default, the weapon is on single
	triggerPull = 0;	//by default, there is no trigger tension/pull

	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: response to the receptions of external event
********************************************************************/

Model &TrigAssy::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in_triggerPressed )	//tension is received (1) or released (0) on trigger
	{
		triggerPull = (int) msg.value();
		holdIn( active, preparationTime );
	}

	else if ( msg.port() == in_firingSelector )	//sidenote: don't need to change any variables if bolt goes back
	{
		FSstate = (int) msg.value();
		holdIn( active, preparationTime );
	}

	else if ( msg.port() == in_boltBack )
		holdIn( active, preparationTime );

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: invoked after the end of external function to do internal transition
********************************************************************/

Model &TrigAssy::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: performs the output function
********************************************************************/
Model &TrigAssy::outputFunction( const InternalMessage &msg )
{
	switch (FSstate)
	{
		case 0:		//firing selector is on safe
		{
			if (triggerPull == 1)	//even though trigger is pulled, while on safe, do not release bolt
				sendOutput( msg.time(), out_releaseBolt, 0 ) ;
			break;
		}
		case 1:		//firing selector is on single
		{
			if (triggerPull == 1)	//release the bolt
				sendOutput (msg.time(), out_releaseBolt, 1 );
			triggerPull = 0;		//trigger tension is released, single shot, must have a trigger pull event to fire again
			break;
		}
		case 2:		//firing selector is on automatic
		{
			if (triggerPull == 1)	//release bolt
				sendOutput (msg.time(), out_releaseBolt, 1 );
			break;
		}
		default:
			break;
	}

	return *this ;
}
