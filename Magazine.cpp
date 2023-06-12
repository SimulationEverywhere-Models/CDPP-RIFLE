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

/** include files **/
#include "Magazine.h"		// class Magazine
#include "message.h"		// class ExternalMessage, InternalMessage
#include "mainsimu.h"		// MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Magazine
* Description: This is the model that represents the weapon's magazine, which feeds bullets.
********************************************************************/
Magazine::Magazine( const string &name )
: Atomic( name )

, in_initBullets( addInputPort( "in_initBullets") )
, in_initMagSeating( addInputPort( "in_initMagSeating") )
, in_bulletLoaded( addInputPort( "in_bulletLoaded") )

, out_bulletReady( addOutputPort( "out_bulletReady") )
, preparationTime( 0, 0, 0, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;
	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Initializes the current function parameters
********************************************************************/
Model &Magazine::initFunction()
{
	tempMsgVal = 0;
	bulletsLeft = 0;		//initially, there are no bullets in magazine
	magSeating = 0;			//initially, there is no magazine seated, nor seated properly
	bulletReady = 0;		//initially, there is no bullet ready
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: response to the receptions of external event
********************************************************************/
Model &Magazine::externalFunction( const ExternalMessage &msg )
{
	tempMsgVal = (int) msg.value ();

	if( msg.port() == in_initBullets )
	{
		if ((tempMsgVal >= 0) && (tempMsgVal <= 30))		//A magazine can only hold between 0 and 30 bullets
			bulletsLeft = tempMsgVal;
	}
	else if (msg.port() == in_initMagSeating )
		magSeating = tempMsgVal;

	else if( msg.port() == in_bulletLoaded )
	{
		if (tempMsgVal == 1)
			bulletsLeft--;
	}

	holdIn( active, preparationTime );
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: invoked after the end of external function to do internal transition
********************************************************************/
Model &Magazine::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: performs the output function
********************************************************************/
Model &Magazine::outputFunction( const InternalMessage &msg )
{
	if (bulletsLeft >= 0)		//if the magazine is just empty, or fuller
	{
		if (magSeating == 1)	//and if the magazine is seated properly
		{
			bulletReady = 1;	//there is a bullet ready to be loaded
		}
	}
	else bulletReady = 0;

	sendOutput(msg.time(), out_bulletReady, bulletReady);

	return *this ;
}
