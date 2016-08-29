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

#ifndef OPH_QUERY_ENGINE_H
#define OPH_QUERY_ENGINE_H

#include "hashtbl.h"
#include "oph_iostorage_data.h"
#include "oph_query_expression_evaluator.h"

#define OPH_QUERY_ENGINE_BUFFER 1024
#define OPH_IO_SERVER_MAX_PLUGIN_NUMBER 1000

/**
 * \brief               Function to startup query engine resources
 * \param plugin_table  Hash table loaded with list of run-time plugins
 * \param function_table  Symtable with list of run-time plugins
 * \return              0 if successfull, non-0 otherwise
 */
int oph_query_engine_start(HASHTBL **plugin_table, oph_query_expr_symtable **function_table);

/**
 * \brief               Function to execute a query operation. NOTE: this block only takes care of plugin part of query
 * \param plugin_table  Hash table containing list of run-time plugins
 * \param plugin_string Plugin part of query to be executed
 * \param record_set    Input record set to operate on
 * \param result_set    Output record set generated by the engine
 * \return              0 if successfull, non-0 otherwise
 */
int oph_query_engine_run(HASHTBL *plugin_table, const char *plugin_string, oph_iostore_frag_record_set *record_set, oph_iostore_frag_record_set **result_set);

/**
 * \brief               Function to end query engine and release resources
 * \param plugin_table  Hash table containing list of run-time plugins to be freed
 * \param function_table  Symtable containing run-time plugins to be freed
 * \return              0 if successfull, non-0 otherwise
 */
int oph_query_engine_end(HASHTBL **plugin_table, oph_query_expr_symtable **function_table);

#endif /* OPH_QUERY_ENGINE_H */
