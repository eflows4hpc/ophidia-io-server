/*
    Ophidia IO Server
    Copyright (C) 2014-2020 CMCC Foundation

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __OPH_METADB_INTERFACE_H
#define __OPH_METADB_INTERFACE_H

#include "oph_iostorage_data.h"

#define OPH_METADB_DATABASE_SCHEMA_PREFIX         OPH_SERVER_DATABASE_SCHEMA_PREFIX
#define OPH_METADB_FRAGMENT_SCHEMA_PREFIX         OPH_SERVER_FRAGMENT_SCHEMA_PREFIX
#define OPH_METADB_TEMP_SCHEMA_PREFIX             OPH_SERVER_TEMP_SCHEMA_PREFIX
#define OPH_METADB_DATABASE_SCHEMA                OPH_SERVER_DATABASE_SCHEMA
#define OPH_METADB_FRAGMENT_SCHEMA                OPH_SERVER_FRAGMENT_SCHEMA
#define OPH_METADB_TEMP_SCHEMA                    OPH_SERVER_TEMP_SCHEMA

// include and define

// error codes
#define OPH_METADB_OK 0
#define OPH_METADB_NULL_ERR 1
#define OPH_METADB_MEMORY_ERR 2
#define OPH_METADB_IO_ERR 3
#define OPH_METADB_DATA_ERR 4

//default hash table size
#define OPH_METADB_FRAG_TABLE_SIZE 5000

/**
 * \brief			        Structure to contain a database schema record
 * \param db_name		  Name of database
 * \param table			Pointer to fragment hash table inside the DB
 * \param next_db 	  Pointer to next db inside the stack
 * \param file_offset	Offset inside binary file
 * \param device      Name of device where DB is stored
 * \param is_persistent Flag used to indicate whether the device is persistent (1) or transient (0)
 * \param db_id      	ID of DB in device (generated by I/O storage API)
 * \param frag_number Number of fragments managed by the database
 */
typedef struct oph_metadb_db_row {
	char *db_name;
	struct oph_metadb_frag_table *table;
	struct oph_metadb_db_row *next_db;
	unsigned long long file_offset;
	char *device;
	short unsigned int is_persistent;
	oph_iostore_resource_id db_id;
	//Info section
	unsigned long long frag_number;
} oph_metadb_db_row;

/**
 * \brief			        Structure to contain a fragment schema record
 * \param frag_name		Name of fragment
 * \param next_frag	  Pointer to next fragment inside the stack
 * \param db_ptr	    Pointer to DB containing fragment
 * \param file_offset	Offset inside binary file
 * \param frag_id     ID of Fragment (generated by I/O storage API)
 * \param device      Name of device where DB is stored
 * \param is_persistent Flag used to indicate whether the device is persistent (1) or transient (0)
 * \param db_id      	ID of DB in device (generated by I/O storage API)
 * \param frag_size   Size of fragment
 */
typedef struct oph_metadb_frag_row {
	char *frag_name;
	struct oph_metadb_frag_row *next_frag;
	oph_metadb_db_row *db_ptr;
	unsigned long long file_offset;
	oph_iostore_resource_id frag_id;
	char *device;
	short unsigned int is_persistent;
	oph_iostore_resource_id db_id;
	//Info section
	unsigned long long frag_size;
} oph_metadb_frag_row;


/**
 * \brief			        Structure to contain a fragment schema hash table
 * \param size				Size of hash table
 * \param rows   			Array of pointers to fragment schema records
 */
typedef struct oph_metadb_frag_table {
	int size;
	oph_metadb_frag_row **rows;
} oph_metadb_frag_table;

/**
 * \brief               Function to set MEtaDB file path
 * \param p		          Path where MetaDB files will be stored (otherwise defaut path will be used)
 */
void oph_metadb_set_data_prefix(char *p);

/**
 * \brief               Function create a new MetaDB Db record
 * \param db_name		    Name of database
 * \param device        Name of device where DB is stored
 * \param db_id        	ID of DB in device (generated by I/O storage API)
 * \param frag_number   Number of fragments managed by the database
 * \param db            New DB record
 * \return              0 if successfull, non-0 otherwise
 */
int oph_metadb_setup_db_struct(char *db_name, char *device, short unsigned int is_persistent, oph_iostore_resource_id * db_id, unsigned long long frag_number, oph_metadb_db_row ** db);

/**
 * \brief               Function to clean up MetaDB Db record
 * \param db            DB record
 * \return              0 if successfull, non-0 otherwise
 */
int oph_metadb_cleanup_db_struct(oph_metadb_db_row * db);

/**
 * \brief               Function create a new MetaDB Frag record
 * \param frag_name		  Name of fragment
 * \param device        Name of device where frag is stored
 * \param db_id        	ID of DB in device (generated by I/O storage API)
 * \param frag_id       ID of Frag in device (generated by I/O storage API)
 * \param frag_size     Size of fragment
 * \param frag          New frag record
 * \return              0 if successfull, non-0 otherwise
 */
int oph_metadb_setup_frag_struct(char *frag_name, char *device, short unsigned int is_persistent, oph_iostore_resource_id * db_id, oph_iostore_resource_id * frag_id, unsigned long long frag_size,
				 oph_metadb_frag_row ** frag);

/**
 * \brief               Function to clean up MetaDB Frag record
 * \param frag          Frag record
 * \return              0 if successfull, non-0 otherwise
 */
int oph_metadb_cleanup_frag_struct(oph_metadb_frag_row * frag);

/**
 * \brief               Function to load database and fragment schema from persitent file
 * \param meta_db       Array that will be filled with MetaDB
 * \param cleanup       With 1 this flag indicates that the MetaDB should be cleaned before loading
 * \return              0 if successfull, non-0 otherwise
 */
int oph_metadb_load_schema(oph_metadb_db_row ** meta_db, short unsigned int cleanup);

/**
 * \brief               Function to unload database and fragment schema from memory
 * \param meta_db       Array to be freed from MetaDB
 * \return              0 if successfull, non-0 otherwise
 */
int oph_metadb_unload_schema(oph_metadb_db_row * meta_db);

/**
 * \brief           Function to add a new DB inside MetaDB (also checks for DB existance).
 * \param meta_db   MetaDB table
 * \param db        DB record to be inserted. The DB record inserted is a copy of this structure, hence db must be freed outside.
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_add_db(oph_metadb_db_row ** meta_db, oph_metadb_db_row * db);

/**
 * \brief           Function to update DB inside MetaDB (also checks for its existance).
 * \param meta_db   MetaDB table
 * \param db        DB record to be updated.  The DB record updated is a copy of this structure, hence db must be freed outside.
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_update_db(oph_metadb_db_row * meta_db, oph_metadb_db_row * db);

/**
 * \brief           Function to remove an empty DB (after verifying its existance) from MetaDB and update meta_db. NOTE: db is uniquely identified by the couple db_name and device.
 * \param meta_db   MetaDB table
 * \param db_name   Name of DB to be removed
 * \param device    Device managing DB to be removed
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_remove_db(oph_metadb_db_row ** meta_db, char *db_name, char *device);

/**
 * \brief           Function to find a DB from MetaDB or verify it existence. If db_name is NULL, then the first db is found. NOTE: db is uniquely identified by the couple db_name and device. 
 * \param meta_db   MetaDB table.
 * \param db_name   Name of DB to be found. Returns a copy of the record.
 * \param device    Device managing DB to be found.
 * \param db        Pointer to DB to be found. WARNING: db points directly to memory record, hence its content should NEVER be modified directly. 
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_find_db(oph_metadb_db_row * meta_db, char *db_name, char *device, oph_metadb_db_row ** db);

/**
 * \brief           Function to insert a frag record into MetaDB (if it does not exist). Also update first_frag into DB.
 * \param db        Pointer to DB where the frag should be placed
 * \param frag      Frag to be inserted. The frag record inserted is a copy of this structure, hence frag must be freed outside.
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_add_frag(oph_metadb_db_row * db, oph_metadb_frag_row * frag);

/**
 * \brief           Function to remove a frag record (if it does exist) from DB. Also update first_frag into DB if necessary.   NOTE: frag is uniquely identified by the couple frag_name and the DB record. 
 * \param db        Pointer to DB where the frag is placed
 * \param frag_name Name of fragment to be removed
 * \param frag_id 	Resource identifier of fragment to be removed (must be freed by the caller). If null is passed no identifier will be returned.
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_remove_frag(oph_metadb_db_row * db, char *frag_name, oph_iostore_resource_id * frag_id);

/**
 * \brief           Function to find a frag from MetaDB (after verifying its existance). If frag_name is NULL, then the first frag is found.  NOTE: frag is uniquely identified by the couple frag_name and the DB record. 
 * \param db        Pointer to DB record where fragment is placed
 * \param frag_name Name of frag to be found
 * \param frag      Frag retrieved
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_find_frag(oph_metadb_db_row * db, char *frag_name, oph_metadb_frag_row ** frag);

/**
 * \brief           Function to update a frag record in MetaDB (if it does exist).
 * \param db        Pointer to DB where the frag is be placed
 * \param frag      Frag to be updated. The frag record updated is a copy of this structure, hence frag must be freed outside.
 * \return          0 if successfull, non-0 otherwise
 */
int oph_metadb_update_frag(oph_metadb_db_row * db, oph_metadb_frag_row * frag);

#endif				/* OPH_METADB_INTERFACE_H */
