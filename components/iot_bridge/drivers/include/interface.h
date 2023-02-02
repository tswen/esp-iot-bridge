/*
 * SPDX-FileCopyrightText: 2015-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"

#ifdef CONFIG_ESP_HOST_SDIO_INTERFACE

#ifdef CONFIG_IDF_TARGET_ESP32
	#include "driver/sdio_slave.h"
#elif defined CONFIG_IDF_TARGET_ESP32S2
	#error "SDIO is not supported ESP32S2"
#endif

#endif

typedef enum {
	LENGTH_1_BYTE  = 1,
	LENGTH_2_BYTE  = 2,
	LENGTH_3_BYTE  = 3,
	LENGTH_4_BYTE  = 4,
} byte_length;

typedef void *wlan_buf_handle_t;

typedef enum {
	SDIO = 0,
	SPI = 1,
} transport_layer;

typedef enum {
	DEINIT,
	INIT,
	ACTIVE,
	DEACTIVE,
} INTERFACE_STATE;

typedef struct {
	union {
#ifdef CONFIG_ESP_HOST_SDIO_INTERFACE
#ifdef CONFIG_IDF_TARGET_ESP32
		sdio_slave_buf_handle_t sdio_buf_handle;
#endif
#endif
		wlan_buf_handle_t	wlan_buf_handle;
		void *priv_buffer_handle;
	};
	uint8_t if_type;
	uint8_t if_num;
	uint8_t *payload;
	uint8_t flag;
	uint16_t payload_len;
	uint16_t seq_num;

	void (*free_buf_handle)(void *buf_handle);
} interface_buffer_handle_t;

typedef struct {
	/*
	union {
	} phy_context;
	*/
	INTERFACE_STATE state;
}interface_handle_t;

typedef struct {
	interface_handle_t * (*init)(void);
	int32_t (*write)(interface_handle_t *handle, interface_buffer_handle_t *buf_handle);
	int (*read)(interface_handle_t *handle, interface_buffer_handle_t *buf_handle);
	esp_err_t (*reset)(interface_handle_t *handle);
	void (*deinit)(interface_handle_t *handle);
} if_ops_t;

typedef struct {
	transport_layer type;
	void *priv;
	if_ops_t *if_ops;
	int (*event_handler)(uint8_t bitmap);
} interface_context_t;

interface_context_t * interface_insert_driver(int (*callback)(uint8_t val));
int interface_remove_driver();
void generate_startup_event(uint8_t cap);