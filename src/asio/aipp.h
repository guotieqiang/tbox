/*!The Treasure Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		aipp.h
 * @ingroup 	asio
 *
 */
#ifndef TB_ASIO_POLL_POOL_H
#define TB_ASIO_POLL_POOL_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "aioo.h"
#include "../container/container.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the aioo poll pool reactor type
struct __tb_aipp_t;
typedef struct __tb_aipp_reactor_t
{
	/// aipp
	struct __tb_aipp_t* 	aipp;

	/// exit
	tb_void_t 				(*exit)(struct __tb_aipp_reactor_t* reactor);

	/// cler
	tb_void_t 				(*cler)(struct __tb_aipp_reactor_t* reactor);

	/// addo
	tb_bool_t 				(*addo)(struct __tb_aipp_reactor_t* reactor, tb_handle_t handle, tb_size_t etype);

	/// seto
	tb_bool_t 				(*seto)(struct __tb_aipp_reactor_t* reactor, tb_handle_t handle, tb_size_t etype, tb_aioo_t const* obj);

	/// delo
	tb_bool_t 				(*delo)(struct __tb_aipp_reactor_t* reactor, tb_handle_t handle);

	/// wait
	tb_long_t 				(*wait)(struct __tb_aipp_reactor_t* reactor, tb_aioo_t* aioo, tb_size_t maxn, tb_long_t timeout);

}tb_aipp_reactor_t;

/*! the aioo poll pool type
 *
 * <pre>
 * objs: |-----|------|------|--- ... ...---|-------|
 * wait:    |            |
 * evet:   read         writ ...
 * </pre>
 *
 */
typedef struct __tb_aipp_t
{
	/// the object type
	tb_size_t 				type;

	/// the object maxn
	tb_size_t 				maxn;

	/// the objects hash
	tb_handle_t 			hash;

	/// the reactor
	tb_aipp_reactor_t* 		rtor;

}tb_aipp_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*!init the aioo poll pool
 *
 * @param 	type 	the object type
 * @param 	maxn 	the maximum number of concurrent objects
 *
 * @return 	the aioo poll pool
 */
tb_aipp_t* 			tb_aipp_init(tb_size_t type, tb_size_t maxn);

/*! exit the aioo poll pool
 *
 * @param 	aipp 	the aioo poll pool
 */
tb_void_t 			tb_aipp_exit(tb_aipp_t* aipp);

/*! cler the aioo poll pool
 *
 * @param 	aipp 	the aioo poll pool
 */
tb_void_t 			tb_aipp_cler(tb_aipp_t* aipp);

/*! add the asio object
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 * @param 	etype 	the event type
 * @param 	odata 	the object data
 *
 * @return 	 		tb_true or tb_false
 */
tb_bool_t 			tb_aipp_addo(tb_aipp_t* aipp, tb_handle_t handle, tb_size_t etype, tb_pointer_t odata);

/*! del the asio object
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 *
 * @return 	 		tb_true or tb_false
 */
tb_bool_t 			tb_aipp_delo(tb_aipp_t* aipp, tb_handle_t handle);

/*! set the asio event
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 * @param 	etype 	the event type
 *
 * @return 			the new event type
 */
tb_size_t 			tb_aipp_gete(tb_aipp_t* aipp, tb_handle_t handle);

/*! set the asio event
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 * @param 	etype 	the event type
 *
 */
tb_void_t 			tb_aipp_sete(tb_aipp_t* aipp, tb_handle_t handle, tb_size_t etype);

/*! add the asio event
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 * @param 	etype 	the event type
 *
 */
tb_void_t 			tb_aipp_adde(tb_aipp_t* aipp, tb_handle_t handle, tb_size_t etype);

/*! del the asio event
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 *
 */
tb_void_t 			tb_aipp_dele(tb_aipp_t* aipp, tb_handle_t handle, tb_size_t etype);

/*! set the asio odata
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 * @param 	odata 	the object data
 *
 */
tb_void_t 			tb_aipp_setp(tb_aipp_t* aipp, tb_handle_t handle, tb_pointer_t odata);

/*! get the asio odata
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	handle 	the aioo native handle
 *
 * @return 			the object data
 */
tb_pointer_t 		tb_aipp_getp(tb_aipp_t* aipp, tb_handle_t handle);

/*! wait the asio objects in the pool
 *
 * blocking wait the multiple event objects
 * return the event number if ok, otherwise return 0 for timeout
 *
 * @param 	aipp 	the aioo poll pool
 * @param 	aioo 	the asio objects
 * @param 	maxn 	the maximum size of the asio objects
 * @param 	timeout the timeout value, return immediately if 0, infinity if -1
 *
 * @return 	the event number, return 0 if timeout, return -1 if error
 */
tb_long_t 			tb_aipp_wait(tb_aipp_t* aipp, tb_aioo_t* aioo, tb_size_t maxn, tb_long_t timeout);

#endif