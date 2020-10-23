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

#include"client.h"

size_t
write_string(void *buffer, size_t size, size_t count, void *stream)
{
	int sizestream = size*count;
	char **response_ptr = (char**)stream;
    	*response_ptr = strndup(buffer, (size_t)(sizestream));
	return sizestream;
}

char*
do_request(CURL *handle, char *url)
{
	char *response = NULL;
	curl_opt(handle,CURLOPT_URL,url); 
	curl_opt(handle,CURLOPT_WRITEFUNCTION,write_string);
	curl_opt(handle,CURLOPT_WRITEDATA,&response);
	curl_perform(handle);
	curl_cleanup(handle);
	return response;
}

struct json_object*
parse_response(char* response)
{
	struct json_object *obj,*tks;
	obj = json_parse(response);
	tks = json_get(obj,"objects");
	return tks;
}

void
balance(int id)
{
	struct json_object *o;
	char url[128],val[16];
	char userid[8];
	sprintf(userid,"%d",id);
	printf("ID: %d\n",id);
	strcpy(val,"OK: ");
	strcpy(url,"http://api.efforia.com.br/balance?userid=");
	strcat(url,userid);
	o = parse_response(do_request(handle,url));
	o = json_get(o,"value");
	strcat(val,json_string(o));
	strcat(val,"\n");
	printf("%s",val);
	write_device(val,strlen(val));
	//write_stream(val,7);
}

void
recharge(int id, int value)
{
	struct json_object *o;
	char url[128],val[16],rec[16];
	char userid[8];
	sprintf(userid,"%d",id);
	sprintf(rec,"&value=%d",value);
	printf("ID: %d\n",id);
	strcpy(val,"OK: ");
	strcpy(url,"http://api.efforia.com.br/recharge?userid=");
	strcat(url,userid);
	strcat(url,rec);
	o = parse_response(do_request(handle,url));
	o = json_get(o,"value");
	strcat(val,json_string(o));
	strcat(val,"\n");
	printf("%s",val);
	write_device(val,strlen(val));
	//write_stream(val,7);
}

void
discharge(int id, int value)
{
	struct json_object *o;
	char url[128],val[16],rec[16];
	char userid[8];
	sprintf(userid,"%d",id);
	sprintf(rec,"&value=%d",value);
	printf("ID: %d\n",id);
	strcpy(val,"OK: ");
	strcpy(url,"http://api.efforia.com.br/discharge?userid=");
	strcat(url,userid);
	strcat(url,rec);
	o = parse_response(do_request(handle,url));
	o = json_get(o,"value");
	strcat(val,json_string(o));
	strcat(val,"\n");
	printf("%s",val);
	write_device(val,strlen(val));
	//write_stream(val,7);
}

int
main(int argc, char** argv)
{
	open_stream("/dev/ttyS0",DEVICE);
	forever{
		int id,value,tokened,count;
		char c,buffer[256],tokens[2];
		bzero(buffer,sizeof(buffer));
		tokened = 0; tokens[1] = '\0';
		handle = curl_init();
		/*open_stream("serial",STREAM);
		read_stream(buffer,sizeof(buffer));*/
		ever{
			read_device(&c,sizeof(c));
			tokens[0] = c;
			if(strcmp("_",tokens) == 0){
				if(tokened) break;
				else tokened++;
				count = 0;
			}
			if(tokened){
				buffer[count] = c;
				count++;
			}
			printf("Caractere lido:\n%c\n",c);
		}
		printf("Stream lido:\n%s\n",buffer);
		char *t = strtok(buffer,"_:");
		while(t != NULL){
			id = atoi(strtok(NULL,"_:"));
			if(strcmp(t,"BALANCE") == 0){
				balance(id);
				break;
			}else if(strcmp(t,"RECHARGE") == 0){ 
				value = atoi(strtok(NULL,"_:"));
				recharge(id,value); 
				break;
			}else if(strcmp(t,"DISCHARGE") == 0){
				value = atoi(strtok(NULL,"_:"));
				discharge(id,value); 
				break;
			}
			printf ("%s\n",t);
			t = strtok(NULL,"_:");
		}
	}
}
