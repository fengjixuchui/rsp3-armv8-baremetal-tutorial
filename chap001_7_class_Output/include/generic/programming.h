/*
 * programming.h
 *
 *  Created on: Jun 9, 2018
 *      Author: 13774
 */

#ifndef INCLUDE_GENERIC_PROGRAMMING_H_
#define INCLUDE_GENERIC_PROGRAMMING_H_

#define AS_MACRO __attribute__((always_inline)) inline
#define arrsizeof(arr) (sizeof(arr)/sizeof(arr[0]))

#define DEFINE_COPY_CONSTRUCTOR(className) className(const className &rhs)
#define DEFINE_COPY_OPERATOR(className) className & operator=(const className &rhs)
#define DELETE_COPY(className) DEFINE_COPY_CONSTRUCTOR(className)=delete; \
                               DEFINE_COPY_OPERATOR(className)=delete



#endif /* INCLUDE_GENERIC_PROGRAMMING_H_ */
