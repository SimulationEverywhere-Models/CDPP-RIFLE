/*******************************************************************
*
*  DESCRIPTION: Atomic Model BoltAssy
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

/** include files **/
#include "BoltAssy.h"	// class BoltAssy
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: BoltAssy
* Description:
********************************************************************/
BoltAssy::BoltAssy( const string &name )
: Atomic( name )
, in_bulletReady( addInputPort( "in_bulletReady") )
, in_releaseBolt( addInputPort( "in_releaseBolt") )
, in_boltBack( addInputPort( "in_boltBack") )
, out_boltPosn( addOutputPort( "out_boltPosn") )
, out_bulletLoaded( addOutputPort( "out_bulletLoaded") )
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
Model &BoltAssy::initFunction()
{
	tempMsgVal = 0;
	boltFree = 0;		//by default, the bolt is not assumed to be free, unless msg otherwise
	readyBullet = 0;	//by default, it is assumed that there is no bullet ready to be loaded
	boltState = 0;		//by default the bolt is forward
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: response to the receptions of external event
********************************************************************/
Model &BoltAssy::externalFunction( const ExternalMessage &msg )
{
	tempMsgVal =(int)msg.value();

	if( msg.port() == in_bulletReady )
	{
		readyBullet = tempMsgVal;
	}

	else if( msg.port() == in_releaseBolt )
	{
		if ( (tempMsgVal == 1) && (boltState == 1) )	//if the bolt is back, and it has been released, free the bolt
			boltFree = tempMsgVal;
	}
	else if( msg.port() == in_boltBack )
	{
		if ( (tempMsgVal == 1) && (boltState == 0) ) //if message is bolt is back, and bolt currently is forward
		{
			boltState = 1;		//if the Cocking Handle is pulled back (or bolt pushed back by firing in chamber), pull the bolt back
		}
		else if ( (tempMsgVal == 1) && (boltState == 1) ) //if message is bolt is back, and bolt currently is back
			boltState = 0;
	}
	holdIn( active, preparationTime );

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: invoked after the end of external function to do internal transition
********************************************************************/
Model &BoltAssy::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: performs the output function
********************************************************************/
Model &BoltAssy::outputFunction( const InternalMessage &msg )
{
	if ((boltFree == 1) && (boltState == 1))	//bolt can be freed, bolt is currently back
	{
		if (readyBullet == 1)					//bullet is ready to be loaded from magazine
		{
			if ((double)rand() / (double)RAND_MAX < 0.90)	//90% of time, the bullet will load properly.
			{
				boltState = 0;	//bring the bolt forward
				sendOutput( msg.time(), out_bulletLoaded, 1 ) ;	//bullet is loaded
			}
			else
			{
				boltState = 2;	//10% of time, the bullet will not load, due to bolt/magazine issues.
				sendOutput( msg.time(), out_bulletLoaded, 0 ) ;	//no bullet loaded
			}
		}
		else 									//no bullet ready to be loaded from magazine
		{
			boltState = 0;	//bring the bolt forward
			sendOutput( msg.time(), out_bulletLoaded, 0 ) ;	//no bullet loaded
		}

		readyBullet = 0;	//no more bullet ready
		boltFree = 0;		//bolt is not freed any longer
		sendOutput( msg.time(), out_boltPosn, boltState ) ;
	}

	return *this ;
}
