/*
 * This file is part of Efforia C API.
 * 
 * Copyright (C) 2009-2012 William Oliveira de Lagos <william.lagos1@gmail.com>
 *
 * Efforia C API is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Efforia C API is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Efforia C API.  If not, see <http://www.gnu.org/licenses/>.
 */

#include"stream.h"
#include<curl/curl.h>
#include<json/json.h>

#define curl_init curl_easy_init
#define curl_opt curl_easy_setopt
#define curl_perform curl_easy_perform
#define curl_cleanup curl_easy_cleanup

#define json_parse json_tokener_parse
#define json_get json_object_object_get
#define json_string json_object_get_string

#define forever while(1)
#define ever while(1)

CURL *handle;
