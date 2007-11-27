/*
 * Copyright (C) 2007 B.A.T.M.A.N. contributors:
 * Marek Lindner
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */





#include "types.h"



struct list_head if_list;
static struct proc_dir_entry *proc_batman_dir, *proc_interface_file;



int init_module( void )
{
	proc_batman_dir = proc_mkdir(PROC_ROOT_DIR, NULL);

	if (!proc_batman_dir) {
		printk("B.A.T.M.A.N.: Registering the '/proc/%s' folder failed\n", PROC_ROOT_DIR);
		return -ENOMEM;
	}

	proc_interface_file = create_proc_entry(PROC_FILE_INTERFACES, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, proc_batman_dir);

	if (proc_interface_file) {
		proc_file->read_proc = proc_interfaces_read;
		proc_file->data = NULL;
	} else {
		printk("B.A.T.M.A.N.: Registering the '/proc/%s/%s' file failed\n", PROC_ROOT_DIR, PROC_FILE_INTERFACES);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&if_list);
	return 0;
}

void cleanup_module( void )
{
	if (proc_interface_file)
		remove_proc_entry(PROC_FILE_INTERFACES, proc_batman_dir);

	if (proc_batman_dir)
		remove_proc_entry(PROC_ROOT_DIR, NULL);
}






/* int batman_core_attach(struct net_device *dev, u_int8_t *ie_buff, u_int8_t *ie_buff_len)
{
	struct list_head *list_pos;
	struct batman_if *batman_if = NULL;

	list_for_each(list_pos, &if_list) {

		batman_if = list_entry(list_pos, struct batman_if, list);

		if (batman_if->net_dev == dev)
			break;
		else
			batman_if = NULL;

	}

	if (batman_if == NULL) {

		printk( "B.A.T.M.A.N. Adv: attaching to %s\n", dev->name);

		batman_if = kmalloc(sizeof(struct batman_if), GFP_KERNEL);

		if (!batman_if)
			return -ENOMEM;

		batman_if->net_dev = dev;

		memcpy(batman_if->out.orig, batman_if->net_dev->dev_addr, 6);
		batman_if->out.packet_type = BAT_PACKET;
		batman_if->out.flags = 0x00;
		batman_if->out.ttl = TTL;
		batman_if->out.seqno = 1;
		batman_if->out.gwflags = 0;
		batman_if->out.version = COMPAT_VERSION;

		batman_if->bcast_seqno = 1;

		INIT_LIST_HEAD(&batman_if->list);
		list_add_tail(&batman_if->list, &if_list);

		memcpy(ie_buff, &batman_if->out, sizeof(struct batman_packet));
		*ie_buff_len = sizeof(struct batman_packet);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
		MOD_INC_USE_COUNT;
#else
		try_module_get(THIS_MODULE);
#endif
		return 0;

	}

	// return 1 to indicate that the interface is already attached
	return 1;
}
EXPORT_SYMBOL(batman_core_attach);

int batman_core_detach(struct net_device *dev)
{
	struct list_head *list_pos, *list_pos_tmp;
	struct batman_if *batman_if;

	list_for_each_safe(list_pos, list_pos_tmp, &if_list) {

		batman_if = list_entry(list_pos, struct batman_if, list);

		if (batman_if->net_dev == dev) {

			printk( "B.A.T.M.A.N. Adv: detaching from %s\n", batman_if->net_dev->name);

			list_del(list_pos);
			kfree(batman_if);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
			MOD_DEC_USE_COUNT;
#else
			module_put(THIS_MODULE);
#endif
			return 0;

		}

	}

	// return 1 to indicate that the interface has not been attached yet
	return 1;
}
EXPORT_SYMBOL(batman_core_detach);

void batman_core_ogm_update(struct net_device *dev, u_int8_t *ie_buff, u_int8_t *ie_buff_len)
{
	struct list_head *list_pos;
	struct batman_if *batman_if = NULL;

	list_for_each(list_pos, &if_list) {

		batman_if = list_entry(list_pos, struct batman_if, list);

		if (batman_if->net_dev == dev)
			break;
		else
			batman_if = NULL;

	}

	if (batman_if != NULL) {

		printk( "B.A.T.M.A.N. Adv: updating ogm for %s\n", batman_if->net_dev->name);

		batman_if->out.seqno++;
		((struct batman_packet *)ie_buff)->seqno = batman_if->out.seqno;

	}
}
EXPORT_SYMBOL(batman_core_ogm_update); */



MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE(DRIVER_DEVICE);
