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

#include "stream.h"

void  
open_stream(char* name, int type)
{
	if(type == DEVICE){
		fd = open(name,O_NOCTTY | O_RDWR);
		if(fd == -1) err(1,"open");
	}else if(type == STREAM) fs = fopen(name,"rw");
}

void  
read_device(char* chr, int size)
{
	ssize_t status = read(fd,chr,size);
	if(status == -1) err(1,"read");
}

void  
write_device(char* string, int size)
{
	ssize_t status = write(fd,string,size);
	if(status == -1) err(1,"write");
}

void 
read_stream(char* string, int size)
{
	size_t status = fread(string,1,size,fs);
	if(status == -1) err(1,"fread");
}

void 
write_stream(char* string, int size)
{
	size_t status = fwrite(string,1,size,fs);
	if(status == -1) err(1,"fwrite");
}
