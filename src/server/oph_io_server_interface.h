/*
    Ophidia IO Server
    Copyright (C) 2014-2016 CMCC Foundation

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

#ifndef OPH_IO_SERVER_INTERFACE_H
#define OPH_IO_SERVER_INTERFACE_H

// error codes
#define OPH_IO_SERVER_SUCCESS                             0
#define OPH_IO_SERVER_NULL_PARAM                          1
#define OPH_IO_SERVER_MEMORY_ERROR                        2
#define OPH_IO_SERVER_ERROR                               3
#define OPH_IO_SERVER_PARSE_ERROR                         4
#define OPH_IO_SERVER_EXEC_ERROR                          5
#define OPH_IO_SERVER_METADB_ERROR                        6
#define OPH_IO_SERVER_API_ERROR                           7

//Log error codes
#define OPH_IO_SERVER_LOG_NULL_INPUT_PARAM                "Missing input argument\n"
#define OPH_IO_SERVER_LOG_MEMORY_ALLOC_ERROR              "Memory allocation error\n"
#define OPH_IO_SERVER_LOG_FILE_OPEN_ERROR                 "Error %d while opening file %s\n"
#define OPH_IO_SERVER_LOG_HASHTBL_ERROR                   "Error while creating hash table for plugins\n"
#define OPH_IO_SERVER_LOG_FILE_READ_ERROR                 "Unable to read line from %s\n"
#define OPH_IO_SERVER_LOG_PLUGIN_FILE_CORRUPTED           "Unable to read plugin file line %s\n"
#define OPH_IO_SERVER_LOG_QUERY_PARSING_ERROR             "Unable to parse query %s\n"
#define OPH_IO_SERVER_LOG_PLUGIN_LOAD_ERROR               "Unable to load plugin table\n"
#define OPH_IO_SERVER_LOG_HASHTBL_CREATE_ERROR            "Unable to create Hash table\n"
#define OPH_IO_SERVER_LOG_QUERY_ARG_LOAD_ERROR            "Unable to load query args in table\n"
#define OPH_IO_SERVER_LOG_MISSING_QUERY_ARGUMENT          "Missing argument %s in query\n"
#define OPH_IO_SERVER_LOG_QUERY_OPERATION_UNKNOWN         "Unknown input operation %s\n"
#define OPH_IO_SERVER_LOG_QUERY_METADB_ERROR              "Error querying metaDB for %s operation\n"
#define OPH_IO_SERVER_LOG_QUERY_METADB_ALLOC_ERROR        "Error creating MetaDB %s record\n"
#define OPH_IO_SERVER_LOG_QUERY_DISPATCH_ERROR            "Error dispatching query to the right operation branch\n"
#define OPH_IO_SERVER_LOG_PLUGIN_EXEC_ERROR               "Error while executing %s\n"
#define OPH_IO_SERVER_LOG_QUERY_DB_EXIST_ERROR            "DB provided already exists\n"
#define OPH_IO_SERVER_LOG_QUERY_DB_NOT_EXIST_ERROR        "DB provided does not exists\n"
#define OPH_IO_SERVER_LOG_QUERY_FRAG_EXIST_ERROR          "Frag provided already exists\n"
#define OPH_IO_SERVER_LOG_QUERY_FRAG_NOT_EXIST_ERROR      "Frag provided does not exists\n"
#define OPH_IO_SERVER_LOG_QUERY_NO_DB_SELECTED            "No DB was previously selected\n"
#define OPH_IO_SERVER_LOG_QUERY_WRONG_DB_SELECTED         "Wrong DB selected\n"
#define OPH_IO_SERVER_LOG_QUERY_HIERARCHY_PARSE_ERROR      "Error while parsing hierarchical arg %s\n"
#define OPH_IO_SERVER_LOG_QUERY_MULTIVAL_PARSE_ERROR      "Error while parsing multivalue arg %s\n"
#define OPH_IO_SERVER_LOG_QUERY_MULTIVAL_ARGS_DIFFER      "Multivalue args for %s are not the same number\n"
#define OPH_IO_SERVER_LOG_QUERY_ENGINE_ERROR              "Error while executing engine on query %s\n"
#define OPH_IO_SERVER_LOG_QUERY_TYPE_ERROR                "Data type %s not recognized\n"
#define OPH_IO_SERVER_LOG_QUERY_INSERT_STATUS_ERROR       "Unable to perform INSERT operation due to missing table info\n"
#define OPH_IO_SERVER_LOG_QUERY_INSERT_COLUMN_ERROR       "Unable to perform INSERT: field name not found in table\n"
#define OPH_IO_SERVER_LOG_QUERY_INSERT_COLUMN_TYPE_ERROR  "Unable to perform INSERT: field type does not correspond to table\n"
#define OPH_IO_SERVER_LOG_QUERY_FRAG_STORE_ERROR  		  "Unable to store the fragment\n"
#define OPH_IO_SERVER_LOG_QUERY_TABLE_COLUMN_CONSTRAINT  	"Only tables with 2 columns can be created\n"
#define OPH_IO_SERVER_LOG_QUERY_ROW_CREATE_ERROR  		  "Unable to create the row\n"
#define OPH_IO_SERVER_LOG_QUERY_SELECTION_ERROR						"Unable to perform SELECTION\n"
#define OPH_IO_SERVER_LOG_QUERY_LIMIT_ERROR								"Unable to compute LIMIT values\n"
#define OPH_IO_SERVER_LOG_QUERY_EMPTY_SELECTION				"Unable to create empty table\n"
#define OPH_IO_SERVER_LOG_API_SETUP_ERROR                 "Unable to setup specified device: %s\n"
#define OPH_IO_SERVER_LOG_QUERY_IO_API_ERROR              "Error while executing %s API\n"
#define OPH_IO_SERVER_LOG_LOCK_ERROR                      "Unable to execute mutex lock\n"
#define OPH_IO_SERVER_LOG_UNLOCK_ERROR                    "Unable to execute mutex unlock\n"
#define OPH_IO_SERVER_LOG_FIELD_TYPE_ERROR                "Field type not recognized: %s\n"
#define OPH_IO_SERVER_LOG_FIELD_NAME_UNKNOWN               "Field name not found: %s\n"
#define OPH_IO_SERVER_LOG_FIELDS_EXEC_ERROR                "Unable to build select columns\n"
#define OPH_IO_SERVER_LOG_FIELDS_ALIAS_NOT_MATCH           "Select alias does not match selection field number\n"
#define OPH_IO_SERVER_LOG_MISSING_WHERE_MULTITABLE         "Missing where in multi-table query\n"
#define OPH_IO_SERVER_LOG_ID_MULTITABLE_CONSTRAINT_ERROR   "Table %s id column does not guarantee order and uniqueness constraints\n"
#define OPH_IO_SERVER_LOG_ONLY_ID_ERROR   				"Only id columns can be used in where clauses\n"

//Packet codes

#define OPH_IO_SERVER_MSG_TYPE_LEN 2
#define OPH_IO_SERVER_MSG_LONG_LEN sizeof(unsigned long long)
#define OPH_IO_SERVER_MSG_SHORT_LEN sizeof(unsigned int)

#define OPH_IO_SERVER_MSG_PING "PG"
#define OPH_IO_SERVER_MSG_RESULT "RS"
#define OPH_IO_SERVER_MSG_USE_DB "UD"
#define OPH_IO_SERVER_MSG_SET_QUERY "SQ"
#define OPH_IO_SERVER_MSG_EXEC_QUERY "EQ"

#define OPH_IO_SERVER_MSG_ARG_DATA_LONG "DL"
#define OPH_IO_SERVER_MSG_ARG_DATA_DOUBLE "DD"
#define OPH_IO_SERVER_MSG_ARG_DATA_NULL "DN"
#define OPH_IO_SERVER_MSG_ARG_DATA_VARCHAR "DV"
#define OPH_IO_SERVER_MSG_ARG_DATA_BLOB "DB"

#define OPH_IO_SERVER_REQ_ERROR   "ER"

// enum and struct
#define OPH_IO_SERVER_MAX_LONG_LEN 24
#define OPH_IO_SERVER_MAX_DOUBLE_LEN 32

#define OPH_IO_SERVER_BUFFER 1024

// Prototypes

#include "hashtbl.h"
#include "oph_iostorage_data.h"
#include "oph_iostorage_interface.h"
#include "oph_query_parser.h"
#include "oph_metadb_interface.h"

/**
 * \brief			            Structure to contain info about a running statement (query executed in multiple runs)
 * \param tot_run         Total number of times the query should be executed
 * \param curr_run        Current value of execution counter
 * \param partial_result_set	Pointer to last result set retrieved by a selection query
 * \param device        	Device where result set belongs
 * \param frag       	    Frag name related to result set
 * \param mi_prev_rows     If multi-insert remainder rows are expected, it will contain the rows already inserted otherwise it will be zero
 */
typedef struct{
  unsigned long long          tot_run;
  unsigned long long          curr_run;
  oph_iostore_frag_record_set *partial_result_set;
  char                        *device;
  char                        *frag;
  unsigned long long          size;
  unsigned long long          mi_prev_rows;
}oph_io_server_running_stmt;

/**
 * \brief			            Structure to store thread status info
 * \param current_db 	    Pointer to current (default) database, if defined
 * \param last_result_set	Pointer to last result set retrieved by a selection query
 * \param device        	Device selected for operations
 * \param curr_stmt       Current statement being executed, if any
 */
typedef struct{
  //oph_metadb_db_row *current_db; 
  char *current_db;
  oph_iostore_frag_record_set *last_result_set;
  char *device;
  oph_io_server_running_stmt *curr_stmt;
}oph_io_server_thread_status;

//Server Auxiliary functions
/**
 * \brief               Function used to dispatch query and execute the correct operation
 * \param meta_db       Pointer to metadb
 * \param dev_handle 		Handler to current IO server device
 * \param thread_status Status of thread executing the query
 * \param args          Additional query arguments
 * \param query_args    Hash table containing args to be selected
 * \param plugin_table  Hash table with plugin
 * \return              0 if successfull, non-0 otherwise
 */
int oph_io_server_dispatcher(oph_metadb_db_row **meta_db, oph_iostore_handler* dev_handle, oph_io_server_thread_status *thread_status, oph_query_arg **args, HASHTBL *query_args, HASHTBL *plugin_table);

//Internal functions used to execute query main blocks

/**
 * \brief               Internal function used to compute offset and limit of a query (LIMIT block)
 * \param query_args    Hash table containing args to be selected
 * \param offset       	Arg to be filled with offset value
 * \param limit 		Arg to be filled with limit value
 * \return              0 if successfull, non-0 otherwise
 */
int _oph_io_server_query_compute_limits(HASHTBL *query_args, long long *offset, long long *limit);

/**
 * \brief               Internal function used to release memory for input record sets of a query (FROM and WHERE blocks). Used in case of select and create as select. 
 * \param dev_handle 		Handler to current IO server device
 * \param stored_rs    	Pointer to be freed with list of original stored recordsets (null terminated list)
 * \param input_rs 		Pointer to be freed with list of filtered recordsets (null terminated list)
 * \return              0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_release_input_record_set(oph_iostore_handler* dev_handle, oph_iostore_frag_record_set **stored_rs, oph_iostore_frag_record_set **input_rs);

/**
 * \brief               Internal function used to select and filter input record set of a query (FROM and WHERE blocks). Used in case of create as select. 
 * \param query_args    Hash table containing args to be selected
 * \param meta_db       Pointer to metadb
 * \param dev_handle 		Handler to current IO server device
 * \param out_db_name 	Name of DB used by output fragment
 * \param out_frag_name Name of output fragment
 * \param thread_status Status of thread executing the query
 * \param stored_rs    	Pointer to be filled with list of original stored recordsets (null terminated list)
 * \param input_row_num Arg to be filled with total number of rows in filtered recordset 
 * \param input_rs 		Pointer to be filled with list of filtered recordset (null terminated list)
 * \return              0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_build_input_record_set_create(HASHTBL *query_args, oph_metadb_db_row **meta_db, oph_iostore_handler* dev_handle, char *out_db_name, char *out_frag_name, oph_io_server_thread_status *thread_status, oph_iostore_frag_record_set ***stored_rs, long long *input_row_num, oph_iostore_frag_record_set ***input_rs);

/**
 * \brief               Internal function used to select and filter input record set of a query (FROM and WHERE blocks). Used in case of select. 
 * \param query_args    Hash table containing args to be selected
 * \param meta_db       Pointer to metadb
 * \param dev_handle 		Handler to current IO server device
 * \param thread_status Status of thread executing the query
 * \param stored_rs    	Pointer to be filled with list of original stored recordsets (null terminated list)
 * \param input_row_num Arg to be filled with total number of rows in filtered recordset
 * \param input_rs 		Pointer to be filled with list of filtered recordset (null terminated list)
 * \return              0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_build_input_record_set_select(HASHTBL *query_args, oph_metadb_db_row **meta_db, oph_iostore_handler* dev_handle, oph_io_server_thread_status *thread_status, oph_iostore_frag_record_set ***stored_rs, long long *input_row_num, oph_iostore_frag_record_set ***input_rs);

/**
 * \brief               	Internal function used to build selection field columns. Used in case of select. 
 * \param field_list    	List of select fields
 * \param field_list_num    Number of select fields to be processed
 * \param offset 			Starting point of input record set
 * \param total_row_number 	Total numbers of row to be processed from input
 * \param args 				Additional args used in prepared statements (can be NULL)
 * \param inputs   			Null terminated list of input record sets
 * \param output 			Output records set to be filled (must be already allocated)
 * \return              	0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_build_select_columns(char **field_list, int field_list_num, long long offset, long long total_row_number, oph_query_arg **args, oph_iostore_frag_record_set **inputs, oph_iostore_frag_record_set *output);

/**
 * \brief               	Internal function used to set column name/alias and default types. Used in case of select or create as select. 
 * \param query_args    	Hash table containing args to be selected
 * \param field_list    	List of select fields
 * \param field_list_num    Number of select fields to be processed
 * \param rs 				Records set to be filled (must be already allocated)
 * \return              	0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_set_column_info(HASHTBL *query_args, char **field_list, int field_list_num, oph_iostore_frag_record_set *rs);

/**
 * \brief               Internal function used to store the final record set. Used in case of insert and multi-insert. 
 * \param meta_db       Pointer to metadb
 * \param dev_handle 		Handler to current IO server device
 * \param thread_status Status of thread executing the query
 * \param frag_name 	Name of fragment to be stored in the IO server
 * \param frag_size 	Size of fragment to be stored in the IO server
 * \param final_result_set 	Pointer with final recordset to be stored in the IO server
 * \return              0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_store_fragment(oph_metadb_db_row **meta_db, oph_iostore_handler* dev_handle, oph_io_server_thread_status *thread_status, char *frag_name, unsigned long long frag_size, oph_iostore_frag_record_set **final_result_set);

/**
 * \brief               Internal function used to create a row from query. Used in case of insert and multi-insert. 
 * \param arg_count     Pointer to variable used to reference current number of arguments used in previous rows
 * \param row_size 		Variable used to save row size
 * \param partial_result_set 	Pointer with partial recordset being created in the IO server
 * \param field_list 	List of insert fields
 * \param value_list 	List of insert values
 * \param args 			Additional args used in prepared statements (can be NULL)
 * \param new_record 	Record to be created
 * \return              0 if successfull, non-0 otherwise
 */
int _oph_ioserver_query_build_row(int *arg_count, unsigned long long *row_size, oph_iostore_frag_record_set *partial_result_set, char **field_list, char **value_list, oph_query_arg **args, oph_iostore_frag_record **new_record);

/**
 * \brief               Function used to release thread status resources
 * \param status        Thread status
 * \return              0 if successfull, non-0 otherwise
 */
int oph_io_server_free_status(oph_io_server_thread_status *status);

#endif /* OPH_IO_SERVER_INTERFACE_H */
