// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2004 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/bgp/route_table_dump.cc,v 1.31 2005/01/31 22:04:16 pavlin Exp $"

//#define DEBUG_LOGGING
//#define DEBUG_PRINT_FUNCTION_NAME

#include "bgp_module.h"
#include "libxorp/xlog.h"
#include "libxorp/callback.hh"
#include "route_table_dump.hh"
#include "route_table_fanout.hh"

//#define DEBUG_CODEPATH
#ifdef DEBUG_CODEPATH
#define cp(x) debug_msg("DumpCodePath: %2d\n", x)
#else
#define cp(x) {}
#endif


template<class A>
DumpTable<A>::DumpTable(string table_name,
			const PeerHandler *peer,
			const list <const PeerTableInfo<A>*>& peer_list,
			BGPRouteTable<A> *parent_table,
			Safi safi)
    : BGPRouteTable<A>("DumpTable-" + table_name, safi),
      _dump_iter(peer, peer_list)
{
    debug_msg("%s peer: %p\n", this->tablename().c_str(), peer);
    //printf("New dumbtable %s peer: %p\n", this->tablename().c_str(), peer);

    cp(1);
    this->_parent = parent_table;
    _peer = peer;
    this->_next_table = 0;
    _output_busy = false;
    _waiting_for_deletion_completion = false;
    _completed = false;
#ifdef AUDIT_ENABLE
    _audit_entries = 0;
    _first_audit = 0;
    _last_audit = 0;
#endif
}

template<class A>
int
DumpTable<A>::add_route(const InternalMessage<A> &rtmsg,
			BGPRouteTable<A> *caller) 
{
    debug_msg("\n         %s\n caller: %s\n"
	      "rtmsg: %p route: %p\n%s\n",
	      this->tablename().c_str(),
	      caller->tablename().c_str(),
	      &rtmsg,
	      rtmsg.route(),
	      rtmsg.str().c_str());

    XLOG_ASSERT(caller == this->_parent);
    XLOG_ASSERT(this->_next_table != NULL);

    cp(1);
    if (_dump_iter.route_change_is_valid(rtmsg.origin_peer(),
					 rtmsg.net(),
					 rtmsg.genid(),
					 RTQUEUE_OP_ADD)) {
	cp(2);
#ifdef AUDIT_ENABLE
	add_audit(c_format("%s::add_route peer:%p/%u net:%s valid",
			   this->tablename().c_str(),
			   rtmsg.origin_peer(),
			   XORP_UINT_CAST(rtmsg.genid()),
			   rtmsg.net().str().c_str()));
#endif
	return this->_next_table->add_route(rtmsg,
				      static_cast<BGPRouteTable<A>*>(this));
    } else {
	cp(3);
#ifdef AUDIT_ENABLE
	add_audit(c_format("%s::add_route peer:%p/%u net:%s not valid",
			   this->tablename().c_str(),
			   rtmsg.origin_peer(),
			   XORP_UINT_CAST(rtmsg.genid()),
			   rtmsg.net().str().c_str()));
#endif
	return ADD_UNUSED;
    }
}

/*
 * We can see a replace_route during a route dump because routes we've
 * already dumped may then change before the dump has completed */

template<class A>
int
DumpTable<A>::replace_route(const InternalMessage<A> &old_rtmsg,
			    const InternalMessage<A> &new_rtmsg,
			    BGPRouteTable<A> *caller) 
{
    debug_msg("%s::replace_route %p -> %p\n",
	      this->tablename().c_str(), &old_rtmsg, &new_rtmsg);
    XLOG_ASSERT(caller == this->_parent);
    XLOG_ASSERT(this->_next_table != NULL);
    XLOG_ASSERT(old_rtmsg.net() == new_rtmsg.net());

    cp(4);

    bool old_is_valid =
	_dump_iter.route_change_is_valid(old_rtmsg.origin_peer(),
					 old_rtmsg.net(),
					 old_rtmsg.genid(),
					 RTQUEUE_OP_REPLACE_OLD);
    bool new_is_valid =
	_dump_iter.route_change_is_valid(new_rtmsg.origin_peer(),
					 new_rtmsg.net(),
					 new_rtmsg.genid(),
					 RTQUEUE_OP_REPLACE_NEW);

#ifdef AUDIT_ENABLE
    add_audit(c_format("%s::replace_route old_peer:%p/%u new_peer:%p/%u net:%s ov:%d nv:%d",
		       this->tablename().c_str(),
		       old_rtmsg.origin_peer(),
		       XORP_UINT_CAST(old_rtmsg.genid()),
		       new_rtmsg.origin_peer(),
		       XORP_UINT_CAST(new_rtmsg.genid()),
		       new_rtmsg.net().str().c_str(), old_is_valid, new_is_valid));
#endif
		       

    /* I'm not sure that all these combinations can happen */
    if (old_is_valid && new_is_valid) {
	cp(5);
	return this->_next_table->replace_route(old_rtmsg, new_rtmsg,
					  (BGPRouteTable<A>*)this);
    } else if (new_is_valid) {
	cp(6);
	return this->_next_table->add_route(new_rtmsg,
				      (BGPRouteTable<A>*)this);
    } else if (old_is_valid) {
	cp(7);
	return this->_next_table->delete_route(new_rtmsg,
					 (BGPRouteTable<A>*)this);
    } else {
	cp(8);
	return ADD_UNUSED;
    }
}

template<class A>
int
DumpTable<A>::route_dump(const InternalMessage<A> &rtmsg,
			 BGPRouteTable<A> *caller,
			 const PeerHandler* dump_peer) 
{
    cp(9);
    XLOG_ASSERT(caller == this->_parent);
    XLOG_ASSERT(this->_next_table != NULL);
    XLOG_ASSERT(dump_peer == _peer);
    XLOG_ASSERT(!_completed);

    debug_msg("Route_dump: %s %s\n", this->tablename().c_str(),
	      rtmsg.net().str().c_str());
#ifdef AUDIT_ENABLE
    add_audit(c_format("%s:route_dump peer:%p/%u net:%s valid",
		       this->tablename().c_str(),
		       rtmsg.origin_peer(),
		       XORP_UINT_CAST(rtmsg.genid()),
		       rtmsg.net().str().c_str()));
#endif
    /* turn the route_dump into a route_add */
    _dump_iter.route_dump(rtmsg);
    _dumped++;
    int result = this->_next_table->add_route(rtmsg, (BGPRouteTable<A>*)this);
    this->_next_table->push((BGPRouteTable<A>*)this);
    return result;
}

/*
 * We can see a delete_route during a route dump because routes we've
 * already dumped may then be deleted before the dump has completed */

template<class A>
int
DumpTable<A>::delete_route(const InternalMessage<A> &rtmsg,
			   BGPRouteTable<A> *caller) 
{
    debug_msg("%s::delete_route %p\n",
	      this->tablename().c_str(), &rtmsg);
    XLOG_ASSERT(caller == this->_parent);
    XLOG_ASSERT(this->_next_table != NULL);

    if (_dump_iter.route_change_is_valid(rtmsg.origin_peer(),
					 rtmsg.net(),
					 rtmsg.genid(),
					 RTQUEUE_OP_DELETE)) {
	cp(10);
#ifdef AUDIT_ENABLE
	add_audit(c_format("%s::add_route peer:%p/%u net:%s valid",
			   this->tablename().c_str(),
			   rtmsg.origin_peer(),
			   XORP_UINT_CAST(rtmsg.genid()),
			   rtmsg.net().str().c_str()));
#endif
	return this->_next_table->delete_route(rtmsg, (BGPRouteTable<A>*)this);
    } else {
	cp(11);
#ifdef AUDIT_ENABLE
	add_audit(c_format("%s::add_route peer:%p/%u net:%s not valid",
			   this->tablename().c_str(),
			   rtmsg.origin_peer(),
			   XORP_UINT_CAST(rtmsg.genid()),
			   rtmsg.net().str().c_str()));
#endif
	return 0;
    }
}

template<class A>
int
DumpTable<A>::push(BGPRouteTable<A> *caller) 
{
    XLOG_ASSERT(caller == this->_parent);
    cp(12);
    return this->_next_table->push((BGPRouteTable<A>*)this);
}

template<class A>
const SubnetRoute<A>*
DumpTable<A>::lookup_route(const IPNet<A> &net, uint32_t& genid) const 
{
    cp(13);
    return this->_parent->lookup_route(net, genid);
}

template<class A>
void
DumpTable<A>::route_used(const SubnetRoute<A>* rt, bool in_use)
{
    cp(14);
    this->_parent->route_used(rt, in_use);
}

template<class A>
string
DumpTable<A>::str() const 
{
    string s = "DumpTable<A>" + this->tablename();
    return s;
}

template<class A>
void
DumpTable<A>::initiate_background_dump() 
{
    XLOG_ASSERT(this->_next_table != NULL);
    XLOG_ASSERT(!_completed);
    cp(15);

    _dumped = 0;
    _dump_active = true;
    _dump_timer = eventloop().
	new_oneoff_after_ms(0 /*call back immediately, but after
				network events or expired timers */,
			    callback(this,
				     &DumpTable<A>::do_next_route_dump));
}

template<class A>
void
DumpTable<A>::suspend_dump() 
{
    debug_msg("%s\n", this->tablename().c_str());

    if (_dump_active == false)
	return;

    cp(16);
    _dump_active = false;
    _dump_timer.unschedule();

    // suspend is being called because the fanout table is unplumbing us.
    this->_next_table->set_parent(NULL);

    // ensure we can't continue to operate
    this->_next_table = (BGPRouteTable<A>*)0xd0d0;
    this->_parent = (BGPRouteTable<A>*)0xd0d0;
    delete this;
}

template<class A>
void
DumpTable<A>::do_next_route_dump() 
{
    XLOG_ASSERT(!_completed);

    if (_output_busy) {
	cp(17);
	// we can't really do anything yet - wait to be triggered by
	// the output state changing
	debug_msg("Dump: output busy\n");
	return;
    }

    // process any queue that built up
    while(this->_parent->get_next_message(this) == true) {
	cp(18);
	debug_msg("DumpTable<A>::do_next_route_dump processed queued message\n");
	if (_output_busy) {
	    cp(19);
	    return;
	}
    };

    // if we get here, the output is not busy and there's no queue of
    // changes upstream of us, so it's time to do more of the route
    // dump...
    debug_msg("dumped %d routes\n", _dumped);
    if (_dump_iter.is_valid() == false) {
	cp(20);
	if (_dump_iter.waiting_for_deletion_completion()) {
	    cp(21);
	    // go into final wait state
	    _waiting_for_deletion_completion = true;
	    // re-enable normal flow control
	    this->_parent->output_state(_output_busy, this);
	} else {
	    cp(22);
	    completed();
	}
	cp(23);
	return;
    } else {
	cp(24);
    }

    //    if (_dump_iter.route_iterator_is_valid())
    //	debug_msg("dump route with net %p\n", _dump_iter.net().str().c_str());
    if (this->_parent->dump_next_route(_dump_iter) == false) {
	cp(25);
	if (_dump_iter.next_peer() == false) {
	    cp(26);
	    if (_dump_iter.waiting_for_deletion_completion()) {
		cp(27);
		// go into final wait state
		_waiting_for_deletion_completion = true;
		// re-enable normal flow control
		this->_parent->output_state(_output_busy, this);
	    } else {
		cp(28);
		completed();
	    }
	    return;
	} else {
	    cp(29);
	}
    } else {
	cp(30);
    }

    _dump_timer = eventloop().
	new_oneoff_after_ms(0 /*call back immediately, but after
				network events or expired timers */,
			    callback(this,
				     &DumpTable<A>::do_next_route_dump));
}

template<class A>
void
DumpTable<A>::output_state(bool busy, BGPRouteTable<A> *next_table) 
{
    XLOG_ASSERT(next_table == this->_next_table);
    if (busy)
	debug_msg("Dump: output state busy\n");
    else
	debug_msg("Dump: output state not busy\n");

    if (_completed || _waiting_for_deletion_completion) {
	//we've finished dumping - just stay out of the way
	_output_busy = busy;
	return this->_parent-> output_state(busy, this);
    } 

    if (_output_busy == true && busy == false) {
	cp(33);
	_output_busy = false;
	debug_msg("Dump: output went idle so dump next\n");
	do_next_route_dump();
    } else {
	cp(34);
	_output_busy = busy;
    }
}

template<class A>
bool
DumpTable<A>::get_next_message(BGPRouteTable<A> *next_table) 
{
    XLOG_ASSERT(next_table == this->_next_table);

    if (_completed) {
	//we completed a while ago, but haven't removed ourselves yet.
	//typically this is because we're waiting for the queue
	//upstream to drain before it's safe to do so.

	bool messages_queued = this->_parent->
	    get_next_message(static_cast<BGPRouteTable<A>*>(this));

	if (messages_queued == false) {
	    //the queue upstream has now drained
	    //we can finally delete ourselves

	    if (!_output_busy) {
		//indicate to upstream that output is not busy anymore
		this->_parent->output_state(false, this);
	    }

	    unplumb_self();
	    delete this;
	    //XXX careful we only access stack state after
	    //deleting ourselves...
	}
	return messages_queued;
    }

    if (_waiting_for_deletion_completion) {
	cp(35);
	//just stay out of the way
	return this->_parent->get_next_message(this);
    } else {
	cp(36);
	debug_msg("Dump: get_next_message\n");
	/* get_next_message is normally used so that the RibOut can cause
	   the fanout table queue to drain clocked by transmit complete
	   interrupts.  But with a dump table, it's not the RibOut that
	   manages the draining of the upstream queue, so we simply return
	   false, pretending there's no queue.  If the output is no longer
	   busy, then we'll get our output_state method called, which we
	   can use to trigger the next batch of work */
	return false;
    }
}

template <class A>
void
DumpTable<A>::peering_is_down(const PeerHandler *peer, uint32_t genid)
{
    debug_msg("\n         %s\n peer: %p genid: %u\n",
	      this->tablename().c_str(),
	      peer, XORP_UINT_CAST(genid));

    if (peer != _peer) {
	//we only care about peers other than our own one - we won't
	//received routes for our own peer
	_dump_iter.peering_is_down(peer, genid);
    }
}

template<class A>
void
DumpTable<A>::peering_went_down(const PeerHandler *peer, uint32_t genid,
				BGPRouteTable<A> *caller) 
{
    debug_msg("\n         %s\n caller: %s\n peer: %p genid: %u\n",
	      this->tablename().c_str(),
	      caller->tablename().c_str(),
	      peer, XORP_UINT_CAST(genid));

    cp(37);
    XLOG_ASSERT(this->_parent == caller);
    XLOG_ASSERT(this->_next_table != NULL);
    if (peer != _peer) {
	_dump_iter.peering_went_down(peer, genid);
    } else {
	//do nothing, we'll soon be unplumbed.
    }
    this->_next_table->peering_went_down(peer, genid, this);
}

template<class A>
void
DumpTable<A>::peering_down_complete(const PeerHandler *peer, uint32_t genid,
				    BGPRouteTable<A> *caller) 
{
    debug_msg("\n         %s\n caller: %s\n peer: %p genid: %u\n",
	      this->tablename().c_str(),
	      caller->tablename().c_str(),
	      peer, XORP_UINT_CAST(genid));

    cp(38);
    XLOG_ASSERT(this->_parent == caller);
    XLOG_ASSERT(this->_next_table != NULL);

    this->_next_table->peering_down_complete(peer, genid, this);

    if (_completed) {
	//we're already done, just waiting for the queue upstream to drain
	return;
    }

    if (peer != _peer) {
	_dump_iter.peering_down_complete(peer, genid);
    } else {
	//do nothing, we'll soon be unplumbed.
    }

    // If we were waiting for this signal, we can now unplumb ourselves.
    if (_waiting_for_deletion_completion
	&& (_dump_iter.waiting_for_deletion_completion() == false)) {
	cp(39);
	completed();
    } else {
	cp(40);
    }
}

template<class A>
void
DumpTable<A>::peering_came_up(const PeerHandler *peer, uint32_t genid,
			      BGPRouteTable<A> *caller) 
{
    debug_msg("\n         %s\n caller: %s\n peer: %p genid: %u\n",
	      this->tablename().c_str(),
	      caller->tablename().c_str(),
	      peer, XORP_UINT_CAST(genid));

    XLOG_ASSERT(this->_parent == caller);
    XLOG_ASSERT(this->_next_table != NULL);
    _dump_iter.peering_came_up(peer, genid);
    this->_next_table->peering_came_up(peer, genid, this);
}

template<class A>
void
DumpTable<A>::completed() 
{
    debug_msg("Completed: %s\n", this->tablename().c_str());
    XLOG_ASSERT(!_completed);

    _completed = true;

    // When we started dumping it looks we asserted flow control
    // on the queue to us in the fanout.

    // We need to drain the queue for everything to be consistent.
    // Otherwise there can be stuff in the queue that came from
    // background deletion that requires our state to be consistent.
    // Thus we *still* can't go away if we can't drain that queue.

    bool messages_queued = true;  //assume there are messages queued
    while(!_output_busy) {
	messages_queued = this->_parent->get_next_message(this);
	if (messages_queued == false)
	    break;
	debug_msg("DumpTable<A>::completed processed queued message\n");
    };
    
    if (messages_queued) {
	//we need to stay around.
	return;
    } 

    if (!_output_busy) {
	//indicate to upstream that output is not busy anymore
	this->_parent->output_state(false, this);
    }

    unplumb_self();
    delete this;
}

template<class A>
void
DumpTable<A>::unplumb_self() 
{
    debug_msg("%s: unplumbing self\n", this->tablename().c_str());
    XLOG_ASSERT(this->_next_table != NULL);
    XLOG_ASSERT(this->_parent != NULL 
		|| (this->_parent == NULL && _dump_active == false));
    _dump_active = false;

    this->_next_table->set_parent(this->_parent);
    cp(41);
    if (this->_parent != NULL) {
	cp(42);
	FanoutTable<A> *ftp = dynamic_cast<FanoutTable<A>*>(this->_parent);
	XLOG_ASSERT(ftp);
#ifdef NOTDEF
	ftp->remove_next_table(static_cast<BGPRouteTable<A>*>(this));
	ftp->add_next_table(this->_next_table, _peer);
#endif
	ftp->replace_next_table(static_cast<BGPRouteTable<A>*>(this), 
				this->_next_table);
    }
    // ensure we can't continue to operate
    this->_next_table = reinterpret_cast<BGPRouteTable<A>*>(0xd0d0);
    this->_parent = reinterpret_cast<BGPRouteTable<A>*>(0xd0d0);
}

#ifdef AUDIT_ENABLE
template<class A>
void 
DumpTable<A>::add_audit(const string& log_entry) {
    //printf("add_audit: %s\n", log_entry.c_str());
    if (_audit_entries == 0) {
	_audit_entries++;
	_last_audit = _first_audit = 0; 
    } else {
	_audit_entries++;
	_last_audit = (_last_audit + 1) % AUDIT_LEN;
	//have we caught our tail
	if (_last_audit == _first_audit) {
	    _first_audit = (_last_audit + 1) % AUDIT_LEN;
	    _audit_entries--;
	}
    }
    _audit_entry[_last_audit] = log_entry;
}

template<class A>
void 
DumpTable<A>::print_and_clear_audit() {
    for (int i = 0; i < _audit_entries; i++) {
	printf("%d:%s\n", i, _audit_entry[(i + _first_audit)%AUDIT_LEN].c_str());
    }
    _audit_entries = 0;
    _first_audit = 0;
    _last_audit = 0;
}
#endif


template class DumpTable<IPv4>;
template class DumpTable<IPv6>;
