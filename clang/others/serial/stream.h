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

#include<err.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

#define DEVICE 0
#define STREAM 1

int   fd;
FILE *fs;

void  open_stream(char* name,   int type);
void  read_device(char* chr,    int size);
void  read_stream(char* string, int size);
void write_device(char* string, int size);
void write_stream(char* string, int size);
