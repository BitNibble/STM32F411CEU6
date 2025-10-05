/******************************************************************************
	ESP8266 AT COMMANDS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ALL
Date:     05102025
Comment:
	
*******************************************************************************/
#ifndef _ESP8266_COMMANDS_
	#define _ESP8266_COMMANDS_
 
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/************************************************/
/************** Basic AT Commands ***************/
/************************************************/
const char* esp8266_cmd_check(void);
const char* esp8266_cmd_reset(void);
const char* esp8266_cmd_version(void);
const char* esp8266_cmd_setgslp(uint16_t time);
const char* esp8266_cmd_echo(uint8_t enable);
const char* esp8266_cmd_restore(void);
const char* esp8266_cmd_setuart_cur(uint32_t baud, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t control);
const char* esp8266_cmd_setuart_def(uint32_t baud, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t control);
//const char* esp8266_cmd_setuart_def(uint32_t baud, uint32_t databits, uint32_t stopbits, uint32_t parity, uint32_t control);
const char* esp8266_cmd_querysleep(void);
const char* esp8266_cmd_setsleep(uint8_t mode);
const char* esp8266_cmd_setrfpower(uint8_t TX_power);
const char* esp8266_cmd_queryrfvdd(void);
const char* esp8266_cmd_setrfvdd(uint16_t vdd33);
const char* esp8266_cmd_rfvdd(void);
/************************************************/
/********** Wi-Fi Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_queryparwmode(void);
const char* esp8266_cmd_querywmode(void);
const char* esp8266_cmd_setwmode_cur(uint8_t mode);
const char* esp8266_cmd_setwmode_def(uint8_t mode);
// AP - Access Point (Router)
const char* esp8266_cmd_querywjap(void); // join access point
const char* esp8266_cmd_setwjap_cur(const char* ssid, const char* password); // This command needs station mode enable.
const char* esp8266_cmd_setwjap_def(const char* ssid, const char* password); // This command needs station mode enable.
// List Settings
const char* esp8266_cmd_setwlapopt(uint8_t sort_enable, uint8_t mask);
const char* esp8266_cmd_setwlap(const char* ssid);
const char* esp8266_cmd_wlap(void);
const char* esp8266_cmd_wqap(void);
// SAP - Soft Access Point
const char* esp8266_cmd_querywsap(void);
const char* esp8266_cmd_setwsap_cur(const char* ssid, const char* pwd, uint8_t chl, uint8_t ecn);
const char* esp8266_cmd_setwsap_def(const char* ssid, const char* pwd, uint8_t chl, uint8_t ecn);
const char* esp8266_cmd_wlif(void);
const char* esp8266_cmd_querywdhcp(void);
const char* esp8266_cmd_setwdhcp_cur(uint8_t mode, uint8_t enable);
const char* esp8266_cmd_setwdhcp_def(uint8_t mode, uint8_t enable);
const char* esp8266_cmd_querywdhcps(void);
const char* esp8266_cmd_setwdhcps_cur(uint8_t enable, uint8_t mode, const char* start_IP, const char* end_IP);
const char* esp8266_cmd_setwdhcps_def(uint8_t enable, uint8_t mode, const char* start_IP, const char* end_IP);
const char* esp8266_cmd_setwautoconn(uint8_t enable);
const char* esp8266_cmd_queryipstamac(void);
const char* esp8266_cmd_setipstamac_cur(const char* mac);
const char* esp8266_cmd_setipstamac_def(const char* mac);
const char* esp8266_cmd_queryipapmac(void);
const char* esp8266_cmd_setipapmac_cur(const char* mac);
const char* esp8266_cmd_setipapmac_def(const char* mac);
const char* esp8266_cmd_queryipsta(void);
const char* esp8266_cmd_setipsta_cur(const char* IP, const char* gateway, const char* netmask);
const char* esp8266_cmd_setipsta_def(const char* IP, const char* gateway, const char* netmask);
const char* esp8266_cmd_queryipap(void);
const char* esp8266_cmd_setipap_cur(const char* IP, const char* gateway, const char* netmask);
const char* esp8266_cmd_setipap_def(const char* IP, const char* gateway, const char* netmask);
const char* esp8266_cmd_wstartsmart(void);
const char* esp8266_cmd_setwstartsmart(uint8_t type); // Access point
const char* esp8266_cmd_wstopsmart(void);
const char* esp8266_cmd_setwstartdiscover(const char* WeChat_number, const char* dev_type, uint8_t time);
const char* esp8266_cmd_wstopdiscover(void);
const char* esp8266_cmd_setwps(uint8_t enable);
const char* esp8266_cmd_setmdns(uint8_t enable, const char* hostname, const char* server_name, uint16_t server_port);
/************************************************/
/********* TCP/IP Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_ipstatus(void);
//IPSTATUS:
//2 - The ESP8266 Station is connected to an AP and its IP is obtained.
//3 - The ESP8266 Station has created a TCP or UDP transmission.
//4 - The TCP or UDP n of ESP8266 Station is disconnected.
//5 - The ESP8266 Station does NOT connect to an AP.
const char* esp8266_cmd_setipdomain(const char* domain_name);
//Connect to Server
const char* esp8266_cmd_muxipstart_tcp(const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_mux0ipstart_udp(const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode);
const char* esp8266_cmd_mux1ipstart_udp(uint8_t link_ID, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode);
const char* esp8266_cmd_muxipstart_ssl(const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_ipsslsize(uint16_t size);
//Communication (Used in all settings)
const char* esp8266_cmd_mux0ipsend_udp(uint16_t length);
const char* esp8266_cmd_mux1ipsend_udp(uint8_t link_ID, uint16_t length);
const char* esp8266_cmd_ipsend_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_ipsend(void);
const char* esp8266_cmd_mux0ipsendex(uint16_t length);
const char* esp8266_cmd_mux1ipsendex(uint8_t link_ID, uint16_t length);
const char* esp8266_cmd_ipsendex_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_mux0ipsend_tcp(uint16_t length);
const char* esp8266_cmd_mux1ipsend_tcp(uint8_t link_ID, uint16_t length);
const char* esp8266_cmd_mux0ipstatus_tcp(void);
const char* esp8266_cmd_mux1ipstatus_tcp(uint8_t link_ID);
const char* esp8266_cmd_mux0ipcheckseq_tcp(uint8_t segment_ID);
const char* esp8266_cmd_mux1ipcheckseq_tcp(uint8_t link_ID, uint8_t segment_ID);
const char* esp8266_cmd_mux0ipreset_tcp(void);
const char* esp8266_cmd_mux1ipreset_tcp(uint8_t link_ID);
const char* esp8266_cmd_multipclose(uint8_t link_ID);
const char* esp8266_cmd_singipclose(void);
const char* esp8266_cmd_ifsr(void);
// MUX Single or Multiple connections
const char* esp8266_cmd_queryipmux(void);
const char* esp8266_cmd_setipmux(uint8_t mode);
const char* esp8266_cmd_muxipserver_tcp(uint8_t mode, uint16_t port);
const char* esp8266_cmd_queryipmode(void);
const char* esp8266_cmd_setipmode(uint8_t mode);
const char* esp8266_cmd_savetranslink_tcp(uint8_t mode, const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_savetranslink_udp(uint8_t mode, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port);
const char* esp8266_cmd_queryipsto_tcp(void);
const char* esp8266_cmd_ipsto_tcp(uint16_t time);
const char* esp8266_cmd_ping(const char* host);
const char* esp8266_cmd_iupdate(void);
const char* esp8266_cmd_ipdinfo(uint8_t mode);
/************************************************/
/**************** Turing Machine ****************/
/************************************************/
void tm_delay( uint32_t tm_delay );
uint32_t tm_getstep( void );
void tm_setstep( uint32_t tm_step );
void tm_jumpstep( uint32_t from, uint32_t to );
void Turingi1to11_Wifi_Connect( uint8_t mode, const char* ssid, const char* password );
void Turingi12to16_Wifi_Setting( void );
void Turingi17to21_Station_Mux0ClientSend_tcp( const char* server, const char * send, size_t size );
void Turingi22to24_Station_Mux1Server( void );
void Turingi25to28_Station_Mux1ServerSend_tcp( uint8_t link_ID, const char * send, size_t size );
void Turingi500to505_Machine( void );

#endif

/*** EOF ***/

