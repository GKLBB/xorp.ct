#!/bin/sh

#
# $XORP: xorp/bgp/xrl_shell_funcs.sh,v 1.14 2005/11/29 15:25:59 atanu Exp $
#

CALLXRL=${CALLXRL:-../libxipc/call_xrl}

local_config()
{
    echo "local_config" $*
#    $CALLXRL  "finder://bgp/bgp/0.1/local_config?localhost:txt=$1&port:i32=$2&as_num:i32=$3&id:ipv4=$4&version:i32=$5&holdtime:i32=$6"
    $CALLXRL  "finder://bgp/bgp/0.2/local_config?as:u32=$1&id:ipv4=$2"
}

route_reflector()
{
    echo "route_reflector" $*
    $CALLXRL "finder://bgp/bgp/0.2/set_cluster_id?cluster_id:ipv4=$1&disable:bool=$2"
}

set_damping()
{
    echo "route_flap_damping" $*
    $CALLXRL "finder://bgp/bgp/0.2/set_damping?half_life:u32=$1&max_suppress:u32=$2&reuse:u32=$3&suppress:u32=$4&disable:bool=$5"
}

add_peer()
{
    echo "add_peer" $*
#    $CALLXRL "finder://bgp/bgp/0.1/add_peer?peer:txt=$1&as:i32=$2&port:i32=$3&next_hop:ipv4=$4"	
    $CALLXRL "finder://bgp/bgp/0.2/add_peer?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4&as:u32=$5&next_hop:ipv4=$6&holdtime:u32=$7"
}

delete_peer()
{
    echo "delete_peer" $*
#    $CALLXRL "finder://bgp/bgp/0.1/delete_peer?peer:txt=$1&as:i32=$2"
    $CALLXRL "finder://bgp/bgp/0.2/delete_peer?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4&as:u32=$5"
}

enable_peer()
{
    echo "enable_peer" $*
#    $CALLXRL "finder://bgp/bgp/0.1/enable_peer?peer:txt=$1&as:i32=$2"
    $CALLXRL "finder://bgp/bgp/0.2/enable_peer?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4"
}

set_parameter()
{
    echo "set_parameter" $*
#    $CALLXRL "finder://bgp/bgp/0.2/set_parameter?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4&parameter:txt=$5"

    $CALLXRL "finder://bgp/bgp/0.2/set_parameter?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4&parameter:txt=$5&toggle:bool=$6"
}

disable_peer()
{
    echo "disable_peer" $*
#    $CALLXRL "finder://bgp/bgp/0.1/disable_peer?peer:txt=$1&as:i32=$2"
    $CALLXRL "finder://bgp/bgp/0.2/disable_peer?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4"
}

route_reflector_client()
{
    echo "route_reflector_client" $*
    $CALLXRL "finder://bgp/bgp/0.2/set_route_reflector_client?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$3&state:bool=$5"
}

set_peer_md5_password()
{
    echo "set_peer_md5_password" $*
    $CALLXRL "finder://bgp/bgp/0.2/set_peer_md5_password?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4&password:txt=$5"
}

next_hop_rewrite_filter()
{
    echo "next_hop_rewrite_filter" $*
    $CALLXRL "finder://bgp/bgp/0.2/next_hop_rewrite_filter?local_ip:txt=$1&local_port:u32=$2&peer_ip:txt=$3&peer_port:u32=$4&next_hop:ipv4=$5"
}

register_rib()
{
    echo "register_rib" $*
    $CALLXRL "finder://bgp/bgp/0.2/register_rib?name:txt=$1"
}

originate_route4()
{
    echo "originate_route4" $*
    $CALLXRL "finder://bgp/bgp/0.2/originate_route4?nlri:ipv4net=$1&next_hop:ipv4=$2&unicast:bool=$3&multicast:bool=$4"
}

originate_route6()
{
    echo "originate_route6" $*
    $CALLXRL "finder://bgp/bgp/0.2/originate_route6?nlri:ipv6net=$1&next_hop:ipv6=$2&unicast:bool=$3&multicast:bool=$4"
}

withdraw_route4()
{
    echo "withdraw_route4" $*
    $CALLXRL "finder://bgp/bgp/0.2/withdraw_route4?nlri:ipv4net=$1&unicast:bool&=$2multicast:bool=$3"
}

withdraw_route6()
{
    echo "withdraw_route6" $*
    $CALLXRL "finder://bgp/bgp/0.2/withdraw_route6?nlri:ipv6net=$1&unicast:bool&=$2multicast:bool=$3"
}

shutdown()
{
    echo "shutdown" $*
    $CALLXRL "finder://bgp/common/0.1/shutdown"
}

time_wait_seconds()
{
    # If there are less than 200 PCB's in TIMEWAIT then return 0.

    local twc
    twc=`netstat -n | grep TIME_WAIT | grep 19999 | wc -l`
    if [ $twc -lt 200 ]
    then
	echo "0"
	return
    fi

    local tw os

    os=`uname -s`
    case $os in
	Linux)
	tw=`sysctl -n net.ipv4.tcp_fin_timeout 2>/dev/null`
	if [ $? -eq 0 ] ; then
	    echo $tw
	    return
	fi
	;;

	FreeBSD)
	local msl
	msl=`sysctl -n net.inet.tcp.msl 2>/dev/null`
	if [ $? -eq 0 ] ; then
	    # Timewait is 2 * msl and msl is in milliseconds
	    tw=`expr $msl + $msl + 1`
	    tw=`expr $tw / 1000`
	    echo $tw
	    return
	fi
	;;

	*)
	# All other OS: use the default value below
	;;
    esac

    # Defailt to 60 seconds
    echo "60"
}

# We have arguments.
if [ $# != 0 ]
then
    $*
fi


# Local Variables:
# mode: shell-script
# sh-indentation: 4
# End: