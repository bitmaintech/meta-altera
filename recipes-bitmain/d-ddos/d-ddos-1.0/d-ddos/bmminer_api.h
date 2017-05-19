/*
 * bmminer_api.h
 *
 *  Created on: Mar 19, 2015
 *      Author: fazio
 */

#ifndef SRC_BMMINER_API_H_
#define SRC_BMMINER_API_H_

typedef struct pools
{
    char *pool;
    char *status;
    char *user;
    int Priority;
    struct pools *next;
} pools;

char *callapi(char *command, char *host, short int port);

#endif /* SRC_bmminer_API_H_ */
