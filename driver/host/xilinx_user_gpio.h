/***********************************************************************
 * Userspace GPIO interface (uses sysfs)
 **********************************************************************/

#pragma once

/*!
 * Register a GPIO under sysfs.
 * \param gpio the GPIO index
 * \return 0 to indicate success
 */
static inline int gpio_export(unsigned int gpio);

/*!
 * Remove a GPIO from sysfs.
 * \param gpio the GPIO index
 * \return 0 to indicate success
 */
static inline int gpio_unexport(unsigned int gpio);

/*!
 * Set the GPIO direction (input or output).
 * \param gpio the GPIO index
 * \param out_flag 0=input, 1=output
 * \return 0 to indicate success
 */
static inline int gpio_set_dir(unsigned int gpio, unsigned int out_flag);

/*!
 * Set the value of the GPIO (high or low).
 * \param gpio the GPIO index
 * \param value 0=low, 1=high
 * \return 0 to indicate success
 */
static inline int gpio_set_value(unsigned int gpio, unsigned int value);

/*!
 * Read the value of the GPIO (high or low).
 * \param gpio the GPIO index
 * \param [out] value 0=low, 1=high
 * \return 0 to indicate success
 */
static inline int gpio_get_value(unsigned int gpio, unsigned int *value);

/*!
 * Set the GPIO interrupt edge.
 * \param gpio the GPIO index
 * \param edge "rising" or "falling"
 * \return 0 to indicate success
 */
static inline int gpio_set_edge(unsigned int gpio, const char *edge);

/*!
 * Open the GPIO to get a file descriptor.
 * The descriptor can be used for interrupts.
 * \param gpio the GPIO index
 * \return a file descriptor or error code
 */
static inline int gpio_fd_open(unsigned int gpio);

/*!
 * Close the GPIO file descriptor.
 * \param fd the descriptor from gpio_fd_open()
 */
static inline int gpio_fd_close(int fd);

/*!
 * Poll the GPIO for an interrupt request.
 * \param fd the descriptor from gpio_fd_open()
 * \param timeout_ms the timeout in ms
 * \return the result of poll() 0=timeout, 1=IRQ, or error
 */
static inline int gpio_poll_irq(int fd, long timeout_ms);

/***********************************************************************
 * Implementation details
 **********************************************************************/
/* Copyright (c) 2011, RidgeRun
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the RidgeRun.
 * 4. Neither the name of the RidgeRun nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY RIDGERUN ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RIDGERUN BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

 /****************************************************************
 * Constants
 ****************************************************************/
 
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

/****************************************************************
 * gpio_export
 ****************************************************************/
static inline int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];
 
	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}
 
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	if (len < 0) return len;
	len = write(fd, buf, len);
	if (len < 0) return len;
	close(fd);
 
	return 0;
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
static inline int gpio_unexport(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];
 
	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}
 
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	if (len < 0) return len;
	len = write(fd, buf, len);
	if (len < 0) return len;
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
static inline int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
	if (len < 0) return len;
 
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/direction");
		return fd;
	}
 
	if (out_flag)
		len = write(fd, "out", 4);
	else
		len = write(fd, "in", 3);
	if (len < 0) return len;
 
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
static inline int gpio_set_value(unsigned int gpio, unsigned int value)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	if (len < 0) return len;
 
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return fd;
	}
 
	if (value)
		len = write(fd, "1", 2);
	else
		len = write(fd, "0", 2);
	if (len < 0) return len;
 
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
static inline int gpio_get_value(unsigned int gpio, unsigned int *value)
{
	int fd, len;
	char buf[MAX_BUF];
	char ch;

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	if (len < 0) return len;
 
	fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perror("gpio/get-value");
		return fd;
	}
 
	read(fd, &ch, 1);

	if (ch != '0') {
		*value = 1;
	} else {
		*value = 0;
	}
 
	close(fd);
	return 0;
}


/****************************************************************
 * gpio_set_edge
 ****************************************************************/

static inline int gpio_set_edge(unsigned int gpio, const char *edge)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);
	if (len < 0) return len;
 
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-edge");
		return fd;
	}
 
	write(fd, edge, strlen(edge) + 1); 
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/

static inline int gpio_fd_open(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	if (len < 0) return len;
 
	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/

static inline int gpio_fd_close(int fd)
{
	return close(fd);
}

/****************************************************************
 * gpio_poll_irq
 ****************************************************************/

static inline int gpio_poll_irq(int fd, long timeout_ms)
{
    char buf[MAX_BUF];
    struct pollfd fdset[1];
    fdset[0].fd = fd;
    fdset[0].events = POLLPRI;
    fdset[0].revents = 0;
    int r = poll(fdset, 1, timeout_ms);

    //reset for next poll with a read + seek
    if (fdset[0].revents & POLLPRI)
    {
        read(fd, buf, MAX_BUF);
        lseek(fd, 0, SEEK_SET);
    }

    return r;
}
