//-----------------------------------------------------------------------------
//
//  $Logfile:: /Code/DLLs/game/coverCombatWithRangedWeapon.hpp                $
// $Revision:: 169                                                            $
//   $Author:: sketcher                                                   $
//     $Date:: 4/26/02 2:22p                                                  $
//
// Copyright (C) 2002 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
//
// DESCRIPTION:
// CoverCombatWithRangedWeapon Behavior Definition
//
//--------------------------------------------------------------------------------

//==============================
// Forward Declarations
//==============================
class GotoHelperNode;

#ifndef __GOTO_HELPER_NODE___
#define __GOTO_HELPER_NODE___

#include "behavior.h"
#include "behaviors_general.h"

//------------------------- CLASS ------------------------------
//
// Name:           CoverCombatWithRangedWeapon
// Base Class:     Behavior
//
// Description:   
//
// Method of Use:  Called From State Machine
//--------------------------------------------------------------
class GotoHelperNode : public Behavior
	{
	//------------------------------------
	// States
	//------------------------------------
	public:  
		typedef enum
		{
			GOTO_HNODE_FIND_NODE,
			GOTO_HNODE_MOVE_TO_NODE,
			GOTO_HNODE_SUCCESS,
			GOTO_HNODE_FAILED
		} GotoHelperNodeStates_t;

	//------------------------------------
	// Parameters
	//------------------------------------
	private:
		str			    _nodeType;
		str				_movementAnim;
		HelperNodePtr	_node;
		float			_maxDistance;

	//-------------------------------------
	// Internal Functionality
	//-------------------------------------
	protected:
		void	transitionToState	( GotoHelperNodeStates_t state );
		void	setInternalState	( GotoHelperNodeStates_t state , const str &stateName );
		void	init				( Actor &self );
		void	think				();		
	

		void					setupStateMoveToNode		();
		BehaviorReturnCode_t	evaluateStateMoveToNode		();
		void					failureStateFindNode		( const str& failureReason );

		void					setupStateFindNode		    ();
		BehaviorReturnCode_t    evaluateStateFindNode       ();
		void					failureStateMoveToNode		( const str& failureReason );

	//-------------------------------------
	// Public Interface
	//-------------------------------------
	public:
		CLASS_PROTOTYPE( GotoHelperNode );

										GotoHelperNode();
									   ~GotoHelperNode();

		void							SetArgs			( Event *ev );      
		void							AnimDone		( Event *ev );
	
		void							Begin			( Actor &self );		
		BehaviorReturnCode_t			Evaluate		( Actor &self );
		void							End				( Actor &self );

		// Accessors
		void							SetNode			( HelperNode *node );
		void							SetMovementAnim ( const str &anim );


		virtual void					Archive  ( Archiver &arc );

	//-------------------------------------
	// Components
	//-------------------------------------
	private: 	
		GotoPoint						_gotoPoint;


	//-------------------------------------
	// Member Variables
	//-------------------------------------
	private: 
		GotoHelperNodeStates_t			_state;		 				
		Actor						   *_self;		

		static const float				NODE_RADIUS;

	};

inline void GotoHelperNode::SetNode ( HelperNode *node )
{
	assert ( node );
	_node = node;
}

inline void	GotoHelperNode::SetMovementAnim ( const str &anim )
{
	_movementAnim = anim;
}


inline void GotoHelperNode::Archive( Archiver &arc	)
{
	Behavior::Archive ( arc );	     

	//
	// Archive Parameters
	//
	arc.ArchiveString( &_nodeType );
	arc.ArchiveString		( &_movementAnim );
	arc.ArchiveSafePointer	( &_node );
	arc.ArchiveFloat( &_maxDistance );

	//
	// Archive Components
	//
	arc.ArchiveObject		( &_gotoPoint );

	//
	// Archive Member Variables
	//
	ArchiveEnum				( _state, GotoHelperNodeStates_t   );	
	arc.ArchiveObjectPointer( ( Class ** )&_self			);
}

#endif /* __GOTO_HELPER_NODE___ */
