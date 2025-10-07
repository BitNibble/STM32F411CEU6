#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#define ESP8266AT_BUFF_SIZE 512
static char ESP8266AT[ESP8266AT_BUFF_SIZE];
static int ESP8266AT_LEN = 0;

/* ===========================================================
 * Core builder functions
 * =========================================================== */
static inline const char* esp8266_cmd_format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ESP8266AT_LEN = vsnprintf(ESP8266AT, ESP8266AT_BUFF_SIZE, fmt, args);
    va_end(args);
    return ESP8266AT;
}

static inline int esp8266_cmd_lastlen(void) {
    return ESP8266AT_LEN;
}

/* ===========================================================
 * Generic AT command helpers
 * =========================================================== */
static inline const char* esp8266_cmd_basic(const char* cmd) {
    return esp8266_cmd_format("AT%s\r\n", cmd ? cmd : "");
}

static inline const char* esp8266_cmd_query(const char* cmd) {
    return esp8266_cmd_format("AT+%s?\r\n", cmd);
}

static inline const char* esp8266_cmd_test(const char* cmd) {
    return esp8266_cmd_format("AT+%s=?\r\n", cmd);
}

static inline const char* esp8266_cmd_execute(const char* cmd) {
    return esp8266_cmd_format("AT+%s\r\n", cmd);
}

static inline const char* esp8266_cmd_set(const char* cmd, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ESP8266AT_LEN = snprintf(ESP8266AT, ESP8266AT_BUFF_SIZE, "AT+%s=", cmd);
    ESP8266AT_LEN += vsnprintf(ESP8266AT + ESP8266AT_LEN, ESP8266AT_BUFF_SIZE - ESP8266AT_LEN, fmt, args);
    va_end(args);
    ESP8266AT[ESP8266AT_LEN++] = '\r';
    ESP8266AT[ESP8266AT_LEN++] = '\n';
    ESP8266AT[ESP8266AT_LEN] = '\0';
    return ESP8266AT;
}

/* ===========================================================
 * Thin wrappers for common AT commands
 * (just examples – add more as needed)
 * =========================================================== */

/* Basic control */
#define ESP8266_CMD_AT()         esp8266_cmd_basic("")
#define ESP8266_CMD_RST()        esp8266_cmd_execute("RST")
#define ESP8266_CMD_GMR()        esp8266_cmd_execute("GMR")

/* Wi-Fi */
#define ESP8266_CMD_CWMODEQ()    esp8266_cmd_query("CWMODE")
#define ESP8266_CMD_CWMODE(mode) esp8266_cmd_set("CWMODE", "%d", (mode))
#define ESP8266_CMD_CWJAP(ssid, pwd) esp8266_cmd_set("CWJAP", "\"%s\",\"%s\"", (ssid), (pwd))
#define ESP8266_CMD_CWLAP()      esp8266_cmd_execute("CWLAP")

/* TCP/IP */
#define ESP8266_CMD_CIPSTART(proto, addr, port) \
    esp8266_cmd_set("CIPSTART", "\"%s\",\"%s\",%u", (proto), (addr), (port))
#define ESP8266_CMD_CIPSEND(len) esp8266_cmd_set("CIPSEND", "%u", (len))
#define ESP8266_CMD_CIPCLOSE()   esp8266_cmd_execute("CIPCLOSE")

/* MQTT (example custom) */
#define ESP8266_CMD_MQTTUSERCFG(link, scheme, client_id, user, pwd) \
    esp8266_cmd_set("MQTTUSERCFG", "%d,%d,\"%s\",\"%s\",\"%s\"", (link), (scheme), (client_id), (user), (pwd))

/* ===========================================================
 * Example usage:
 *
 *   ESP8266_CMD_RST();
 *   ESP8266_CMD_CWMODE(1);
 *   ESP8266_CMD_CWJAP("MySSID", "MyPass");
 *   ESP8266_CMD_CIPSTART("TCP", "192.168.1.10", 1883);
 *
 *   uart_send(ESP8266AT, esp8266_cmd_lastlen());
 * =========================================================== */

```
```c
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#define ESP8266AT_BUFF_SIZE 512
static char ESP8266AT[ESP8266AT_BUFF_SIZE];
static int ESP8266AT_LEN = 0;

/* ===========================================================
 * Core builder functions
 * =========================================================== */
static inline const char* esp8266_cmd_format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ESP8266AT_LEN = vsnprintf(ESP8266AT, ESP8266AT_BUFF_SIZE, fmt, args);
    va_end(args);
    return ESP8266AT;
}

static inline int esp8266_cmd_lastlen(void) {
    return ESP8266AT_LEN;
}

static inline const char* esp8266_cmd_basic(const char* cmd) {
    return esp8266_cmd_format("AT%s\r\n", cmd ? cmd : "");
}

static inline const char* esp8266_cmd_query(const char* cmd) {
    return esp8266_cmd_format("AT+%s?\r\n", cmd);
}

static inline const char* esp8266_cmd_test(const char* cmd) {
    return esp8266_cmd_format("AT+%s=?\r\n", cmd);
}

static inline const char* esp8266_cmd_execute(const char* cmd) {
    return esp8266_cmd_format("AT+%s\r\n", cmd);
}

static inline const char* esp8266_cmd_set(const char* cmd, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ESP8266AT_LEN = snprintf(ESP8266AT, ESP8266AT_BUFF_SIZE, "AT+%s=", cmd);
    ESP8266AT_LEN += vsnprintf(ESP8266AT + ESP8266AT_LEN, ESP8266AT_BUFF_SIZE - ESP8266AT_LEN, fmt, args);
    va_end(args);
    ESP8266AT[ESP8266AT_LEN++] = '\r';
    ESP8266AT[ESP8266AT_LEN++] = '\n';
    ESP8266AT[ESP8266AT_LEN] = '\0';
    return ESP8266AT;
}

/* ===========================================================
 * Thin wrappers: Organized by AT command family
 * =========================================================== */

/* --- Basic control --- */
#define ESP8266_CMD_AT()          esp8266_cmd_basic("")
#define ESP8266_CMD_RST()         esp8266_cmd_execute("RST")
#define ESP8266_CMD_GMR()         esp8266_cmd_execute("GMR")
#define ESP8266_CMD_GSLP(ms)      esp8266_cmd_set("GSLP", "%u", (ms))
#define ESP8266_CMD_ECHO(on)      esp8266_cmd_set("E", "%d", (on))
#define ESP8266_CMD_RESTORE()     esp8266_cmd_execute("RESTORE")
#define ESP8266_CMD_UART(baud,bit,stop,par,flow) \
    esp8266_cmd_set("UART_CUR", "%u,%d,%d,%d,%d", (baud),(bit),(stop),(par),(flow))

/* --- Wi-Fi station/AP --- */
#define ESP8266_CMD_CWMODEQ()     esp8266_cmd_query("CWMODE")
#define ESP8266_CMD_CWMODE(mode)  esp8266_cmd_set("CWMODE", "%d", (mode))
#define ESP8266_CMD_CWJAP(ssid, pwd) esp8266_cmd_set("CWJAP", "\"%s\",\"%s\"", (ssid), (pwd))
#define ESP8266_CMD_CWQAP()       esp8266_cmd_execute("CWQAP")
#define ESP8266_CMD_CWLAP()       esp8266_cmd_execute("CWLAP")
#define ESP8266_CMD_CWSAP(ssid,pwd,ch,ecn) \
    esp8266_cmd_set("CWSAP", "\"%s\",\"%s\",%d,%d", (ssid),(pwd),(ch),(ecn))
#define ESP8266_CMD_CWLIF()       esp8266_cmd_execute("CWLIF")
#define ESP8266_CMD_CIPSTAQ()     esp8266_cmd_query("CIPSTA")
#define ESP8266_CMD_CIPAPQ()      esp8266_cmd_query("CIPAP")

/* --- TCP/IP --- */
#define ESP8266_CMD_CIPSTATUS()   esp8266_cmd_execute("CIPSTATUS")
#define ESP8266_CMD_CIPSTART(proto, addr, port) \
    esp8266_cmd_set("CIPSTART", "\"%s\",\"%s\",%u", (proto), (addr), (port))
#define ESP8266_CMD_CIPSEND(len)  esp8266_cmd_set("CIPSEND", "%u", (len))
#define ESP8266_CMD_CIPCLOSE()    esp8266_cmd_execute("CIPCLOSE")
#define ESP8266_CMD_CIPMUX(on)    esp8266_cmd_set("CIPMUX", "%d", (on))
#define ESP8266_CMD_CIPSERVER(mode, port) esp8266_cmd_set("CIPSERVER", "%d,%u", (mode), (port))
#define ESP8266_CMD_CIPMODE(mode) esp8266_cmd_set("CIPMODE", "%d", (mode))
#define ESP8266_CMD_CIPSTO(sec)   esp8266_cmd_set("CIPSTO", "%u", (sec))

/* --- DNS / MDNS --- */
#define ESP8266_CMD_CIPDOMAIN(domain) esp8266_cmd_set("CIPDOMAIN", "\"%s\"", (domain))
#define ESP8266_CMD_MDNSENABLE(en)    esp8266_cmd_set("MDNS", "%d", (en))
#define ESP8266_CMD_MDNSNAME(name)    esp8266_cmd_set("MDNSNAME", "\"%s\"", (name))

/* --- SmartConfig --- */
#define ESP8266_CMD_SMARTSTART()  esp8266_cmd_execute("CWSTARTSMART")
#define ESP8266_CMD_SMARTSTOP()   esp8266_cmd_execute("CWSTOPSMART")

/* --- MQTT (if firmware supports it) --- */
#define ESP8266_CMD_MQTTUSERCFG(link, scheme, client_id, user, pwd) \
    esp8266_cmd_set("MQTTUSERCFG", "%d,%d,\"%s\",\"%s\",\"%s\"", (link),(scheme),(client_id),(user),(pwd))
#define ESP8266_CMD_MQTTCONN(link, host, port, reconnect) \
    esp8266_cmd_set("MQTTCONN", "%d,\"%s\",%u,%d", (link),(host),(port),(reconnect))
#define ESP8266_CMD_MQTTPUB(link, topic, msg, qos, retain) \
    esp8266_cmd_set("MQTTPUB", "%d,\"%s\",\"%s\",%d,%d", (link),(topic),(msg),(qos),(retain))
#define ESP8266_CMD_MQTTSUB(link, topic, qos) \
    esp8266_cmd_set("MQTTSUB", "%d,\"%s\",%d", (link),(topic),(qos))
#define ESP8266_CMD_MQTTUNSUB(link, topic) \
    esp8266_cmd_set("MQTTUNSUB", "%d,\"%s\"", (link),(topic))

/* ===========================================================
 * Example usage:
 *
 *   ESP8266_CMD_RST();
 *   ESP8266_CMD_CWMODE(1);
 *   ESP8266_CMD_CWJAP("MySSID", "MyPass");
 *   ESP8266_CMD_CIPSTART("TCP", "192.168.1.10", 1883);
 *
 *   uart_send(ESP8266AT, esp8266_cmd_lastlen());
 * =========================================================== */


#include <stdio.h>
#include <stdarg.h>

#define ESP8266AT_BUFF_SIZE 512
static char ESP8266AT[ESP8266AT_BUFF_SIZE];
static int ESP8266AT_LEN = 0;

/* One generic builder: base + format + params */
static inline const char* esp8266_cmd(const char* base, const char* fmt, ...) {
    va_list args;
    ESP8266AT_LEN = snprintf(ESP8266AT, ESP8266AT_BUFF_SIZE, "AT%s", base);

    if (fmt && *fmt) {
        ESP8266AT_LEN += snprintf(ESP8266AT + ESP8266AT_LEN,
                                  ESP8266AT_BUFF_SIZE - ESP8266AT_LEN,
                                  "=");
        va_start(args, fmt);
        ESP8266AT_LEN += vsnprintf(ESP8266AT + ESP8266AT_LEN,
                                   ESP8266AT_BUFF_SIZE - ESP8266AT_LEN,
                                   fmt, args);
        va_end(args);
    }

    ESP8266AT_LEN += snprintf(ESP8266AT + ESP8266AT_LEN,
                              ESP8266AT_BUFF_SIZE - ESP8266AT_LEN,
                              "\r\n");

    return ESP8266AT;
}

static inline int esp8266_cmd_lastlen(void) {
    return ESP8266AT_LEN;
}

/* ===========================================================
 * Example usage:
 *
 * esp8266_cmd("", NULL);                          // "AT\r\n"
 * esp8266_cmd("+RST", NULL);                      // "AT+RST\r\n"
 * esp8266_cmd("+CWMODE", "%d", 1);                // "AT+CWMODE=1\r\n"
 * esp8266_cmd("+CWJAP", "\"%s\",\"%s\"", "SSID","PWD");
 *                                                 // "AT+CWJAP=\"SSID\",\"PWD\"\r\n"
 * esp8266_cmd("+CIPSTART", "\"%s\",\"%s\",%d","TCP","192.168.1.2",1883);
 *                                                 // "AT+CIPSTART=\"TCP\",\"192.168.1.2\",1883\r\n"
 *
 * uart_send(ESP8266AT, esp8266_cmd_lastlen());
 * =========================================================== */
 
 ```c
/* ===========================================================
 * Basic AT Commands
 * =========================================================== */
esp8266_cmd("", NULL);                 // AT
esp8266_cmd("+RST", NULL);             // AT+RST
esp8266_cmd("+GMR", NULL);             // AT+GMR
esp8266_cmd("+GSLP", "%u", 1000);      // AT+GSLP=1000
esp8266_cmd("+ECHO", "%d", 0);         // AT+ECHO=0

/* ===========================================================
 * Wi-Fi Configuration
 * =========================================================== */
esp8266_cmd("+CWMODE?", NULL);         // AT+CWMODE?
esp8266_cmd("+CWMODE", "%d", 1);       // AT+CWMODE=1
esp8266_cmd("+CWJAP?", NULL);          // AT+CWJAP?
esp8266_cmd("+CWJAP", "\"%s\",\"%s\"", "SSID","PWD"); // AT+CWJAP="SSID","PWD"
esp8266_cmd("+CWQAP", NULL);           // AT+CWQAP
esp8266_cmd("+CWLAP", NULL);           // AT+CWLAP
esp8266_cmd("+CIPSTA?", NULL);         // AT+CIPSTA?
esp8266_cmd("+CIPSTA", "\"%s\"", "192.168.1.50"); // AT+CIPSTA="192.168.1.50"

/* ===========================================================
 * TCP/IP Related
 * =========================================================== */
esp8266_cmd("+CIPSTATUS", NULL);       // AT+CIPSTATUS
esp8266_cmd("+CIPSTART", "\"%s\",\"%s\",%d", "TCP","192.168.1.2",1883);
// AT+CIPSTART="TCP","192.168.1.2",1883
esp8266_cmd("+CIPSEND", "%u", 64);     // AT+CIPSEND=64
esp8266_cmd("+CIPCLOSE", NULL);        // AT+CIPCLOSE
esp8266_cmd("+CIFSR", NULL);           // AT+CIFSR

/* ===========================================================
 * DNS / Ping
 * =========================================================== */
esp8266_cmd("+CIPDOMAIN", "\"%s\"", "example.com"); // AT+CIPDOMAIN="example.com"
esp8266_cmd("+PING", "\"%s\"", "8.8.8.8");          // AT+PING="8.8.8.8"

/* ===========================================================
 * MQTT (if firmware supports it)
 * =========================================================== */
esp8266_cmd("+MQTTUSERCFG", "%d,%d,\"%s\",\"%s\",\"%s\"",
            0,0,"clientID","user","pass");
// AT+MQTTUSERCFG=0,0,"clientID","user","pass"
esp8266_cmd("+MQTTCONN", "%d,\"%s\",%d,%d",
            0,"broker.hivemq.com",1883,0);
// AT+MQTTCONN=0,"broker.hivemq.com",1883,0
esp8266_cmd("+MQTTPUB", "%d,\"%s\",\"%s\",%d,%d",
            0,"topic/test","Hello",0,0);
// AT+MQTTPUB=0,"topic/test","Hello",0,0

/* ===========================================================
 * SmartConfig / WPS
 * =========================================================== */
esp8266_cmd("+CWSTARTSMART", NULL);    // AT+CWSTARTSMART
esp8266_cmd("+CWSTOPSMART", NULL);     // AT+CWSTOPSMART
esp8266_cmd("+WPS", "%d", 1);          // AT+WPS=1

/* ===========================================================
 * Sleep / Power Save
 * =========================================================== */
esp8266_cmd("+SLEEP", "%d", 2);        // AT+SLEEP=2
esp8266_cmd("+RFPOWER", "%d", 82);     // AT+RFPOWER=82

/* ===========================================================
 * System & Info
 * =========================================================== */
esp8266_cmd("+SYSRAM", NULL);          // AT+SYSRAM
esp8266_cmd("+SYSFLASH", NULL);        // AT+SYSFLASH
esp8266_cmd("+SYSVER", NULL);          // AT+SYSVER
```

/* — Basic / System Commands — */
esp8266_cmd("+CMD", "?", );              // AT+CMD? — list supported AT commands  
esp8266_cmd("+UART_CUR", "%u,%d,%d,%d,%d", 115200, 8, 1, 0, 3);  // AT+UART_CUR=<baud,dat,bits,parity,flow>  
esp8266_cmd("+UART_DEF", "%u,%d,%d,%d,%d", 115200, 8, 1, 0, 3);  // AT+UART_DEF=… (saved in flash)  
esp8266_cmd("+SLEEP", "%d", 0);          // AT+SLEEP=0  
esp8266_cmd("+SYSRAM", NULL);            // AT+SYSRAM  
esp8266_cmd("+SYSMSG", NULL);            // AT+SYSMSG (query stored prompt settings)  
esp8266_cmd("+SYSFLASH", NULL);          // AT+SYSFLASH  
esp8266_cmd("+SYSROLLBACK", NULL);       // AT+SYSROLLBACK (rollback firmware)  
esp8266_cmd("+SYSTIMESTAMP", NULL);      // AT+SYSTIMESTAMP (query timestamp)  
esp8266_cmd("+SYSLOG", "%d", 1);         // AT+SYSLOG=1 (enable error code prompt)  
esp8266_cmd("+SYSSTORE", "%d", 1);       // AT+SYSSTORE=1 (enable saving config to flash)  
esp8266_cmd("+SYSREG", "%u,%u", 0x3FF, 0x55); // AT+SYSREG (read/write register)  

/* — Wi-Fi / Network / DHCP / SoftAP — */
esp8266_cmd("+CWRECONNCFG", "?", );       // AT+CWRECONNCFG?  
esp8266_cmd("+CWRECONNCFG", "%d,%d", 1, 60000);  // AT+CWRECONNCFG=<enable>,<interval>  
esp8266_cmd("+CWLAPOPT", "%d,%d", 1, 31);  // AT+CWLAPOPT=1,31 (sort + print mask)  
esp8266_cmd("+CWDHCP", "?", );             // AT+CWDHCP?  
esp8266_cmd("+CWDHCP", "%d,%d", 0, 1);     // AT+CWDHCP=<mode>,<enable>  
esp8266_cmd("+CWDHCPS_CUR", "%d,%d,\"%s\",\"%s\"", 1, 0, "192.168.4.2", "192.168.4.100");  
    // AT+CWDHCPS_CUR=1,0,"192.168.4.2","192.168.4.100"  
esp8266_cmd("+CWAUTOCONN", "%d", 1);       // AT+CWAUTOCONN=1  
esp8266_cmd("+CWAPPROTO", "?", );          // AT+CWAPPROTO?  
esp8266_cmd("+CWAPPROTO", "%d", 3);        // AT+CWAPPROTO=3  
esp8266_cmd("+CWSTAPROTO", "%d", 3);       // AT+CWSTAPROTO=3  
esp8266_cmd("+CWSTATE", "?", );            // AT+CWSTATE?  
esp8266_cmd("+IPSTA", NULL);               // AT+CIPSTA?  
esp8266_cmd("+IPSTA", "\"%s\",\"%s\",\"%s\"", "192.168.1.50", "192.168.1.1", "255.255.255.0");  
esp8266_cmd("+IPAP", "\"%s\",\"%s\",\"%s\"", "192.168.4.1", "192.168.4.1", "255.255.255.0");  
esp8266_cmd("+IPSTAMAC", NULL);            // AT+CIPSTAMAC?  
esp8266_cmd("+IPSTAMAC", "\"%s\"", "1a:2b:3c:4d:5e:6f");  
esp8266_cmd("+IPAPMAC", "\"%s\"", "1a:2b:3c:4d:5e:70");  
esp8266_cmd("+CWQIF", NULL);                // AT+CWQIF — disconnect stations from SoftAP  

/* — TCP / IP — */
esp8266_cmd("+CIPSSLRR", "%u", 4096);       // (if SSL is supported)  
esp8266_cmd("+CIPSENDBUF", "%d", 512);      // AT+CIPSENDBUF=512  
esp8266_cmd("+CIPBUFSTATUS", NULL);         // AT+CIPBUFSTATUS  
esp8266_cmd("+CIPMUX", "%d", 1);            // AT+CIPMUX=1  
esp8266_cmd("+CIPMODE", "%d", 1);           // AT+CIPMODE=1  
esp8266_cmd("+CIPSTO", "%u", 120);          // AT+CIPSTO=120  
esp8266_cmd("+CIPSERVER", "%d,%u", 1, 8080); // AT+CIPSERVER=1,8080  
esp8266_cmd("+CIPSTART", "\"%s\",\"%s\",%u", "TCP", "iot.example.com", 1883);  
esp8266_cmd("+CIPSEND", "%u", 64);           // AT+CIPSEND=64  
esp8266_cmd("+CIPCLOSE", NULL);              // AT+CIPCLOSE  
esp8266_cmd("+CIPSTATUS", NULL);             // AT+CIPSTATUS  
esp8266_cmd("+CIPDNS", "%d,%d", 1, 8);        // AT+DNS? or custom usage  
esp8266_cmd("+CIUPDATE", NULL);              // AT+CIUPDATE  

/* — HTTP / Web / Server (if module supports) — */
esp8266_cmd("+HTTPCLIENT", "%d,\"%s\",\"%s\",\"%s\",%u", 
            0, "http://api.example.com/data", "GET", "", 60000);
// AT+HTTPCLIENT = <link_id>, "url", "method", "body", timeout  
esp8266_cmd("+HTTPSCLIENT", "%d,\"%s\",\"%s\",\"%s\",%u", 
            0, "https://api.example.com", "GET", "", 60000);  

/* — SSL / Security — */
esp8266_cmd("+CIPSTART", "\"SSL\",\"%s\",%u", "secure.server.com", 443);  
esp8266_cmd("+CIPSSLSIZE", "%u", 2048);      // AT+CIPSSLSIZE=2048  

/* — Misc / Others — */
esp8266_cmd("+RFVDD", "%u", 3300);            // AT+RFVDD=<VDD33>  
esp8266_cmd("+RFPOWER", "%u", 82);            // AT+RFPOWER=82  
esp8266_cmd("+SYSADC", NULL);                 // AT+SYSADC  
esp8266_cmd("+SYSGPIOWRITE", "%u,%u", 2, 1);  // AT+SYSGPIOWRITE=GPIO,PINLEVEL  
esp8266_cmd("+SYSGPIODIR", "%u,%u", 4, 0);    // AT+SYSGPIODIR=GPIO,DIR  
esp8266_cmd("+SYSGPIOREAD", "%u", 2);         // AT+SYSGPIOREAD=GPIO  
esp8266_cmd("+SYSIOSETCFG", "%u,%u,%u", 12, 0, 2);  
esp8266_cmd("+SYSIOGETCFG", "%u", 12);  

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define CMD_BUFFER_SIZE 256
static char CMD_BUFFER[CMD_BUFFER_SIZE];

// Generic command types
typedef enum {
    CMD_EXECUTE,    // e.g., AT+RST
    CMD_QUERY,      // e.g., AT+CWMODE?
    CMD_QUERYPAR,   // e.g., AT+CWMODE=?
    CMD_SET         // e.g., AT+CWMODE=1
} cmd_type_t;

/**
 * Core command builder
 * base: base command, e.g., "CWMODE"
 * type: execute/query/set
 * fmt: printf-style parameter format, e.g., "%d,%s"
 * ...: parameters matching fmt
 */
const char* cmd_build(const char* base, cmd_type_t type, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char params[CMD_BUFFER_SIZE];
    if(fmt && *fmt) {
        vsnprintf(params, sizeof(params), fmt, args);
    } else {
        params[0] = 0;
    }

    va_end(args);

    switch(type) {
        case CMD_EXECUTE:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s\r\n", base);
            break;
        case CMD_QUERY:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s?\r\n", base);
            break;
        case CMD_QUERYPAR:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=?\r\n", base);
            break;
        case CMD_SET:
            if(params[0])
                snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=%s\r\n", base, params);
            else
                snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s\r\n", base);
            break;
    }
    return CMD_BUFFER;
}


// WiFi mode
const char* esp_set_wmode(uint8_t mode) {
    return cmd_build("CWMODE_CUR", CMD_SET, "%d", mode);
}

const char* esp_query_wmode(void) {
    return cmd_build("CWMODE_CUR", CMD_QUERY, NULL);
}

// Connect to AP
const char* esp_connect_ap(const char* ssid, const char* pwd) {
    return cmd_build("CWJAP_CUR", CMD_SET, "\"%s\",\"%s\"", ssid, pwd);
}

// Send TCP data on link 0
const char* esp_send_tcp0(uint16_t len) {
    return cmd_build("CIPSEND", CMD_SET, "%d", len);
}


#define CMD_EXEC(cmd) cmd_build(cmd, CMD_EXECUTE, NULL)
#define CMD_QUERY(cmd) cmd_build(cmd, CMD_QUERY, NULL)
#define CMD_SET1(cmd, fmt, arg1) cmd_build(cmd, CMD_SET, fmt, arg1)

#ifndef ESP8266_AT_CORE_H
#define ESP8266_AT_CORE_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CMD_BUFFER_SIZE 256
extern char CMD_BUFFER[CMD_BUFFER_SIZE];

// Command types
typedef enum {
    CMD_EXECUTE,
    CMD_QUERY,
    CMD_QUERY_PARAM,
    CMD_SET
} cmd_type_t;

// Base commands
typedef enum {
    AT_RST,
    AT_GMR,
    AT_CWMODE_CUR,
    AT_CWMODE_DEF,
    AT_CWJAP_CUR,
    AT_CWJAP_DEF,
    AT_CIPSTART,
    AT_CIPSEND,
    AT_CIFSR,
    // ... add more as needed
} esp8266_cmd_base_t;

// Convert enum to string
static inline const char* cmd_base_to_string(esp8266_cmd_base_t base) {
    switch(base) {
        case AT_RST:          return "RST";
        case AT_GMR:          return "GMR";
        case AT_CWMODE_CUR:   return "CWMODE_CUR";
        case AT_CWMODE_DEF:   return "CWMODE_DEF";
        case AT_CWJAP_CUR:    return "CWJAP_CUR";
        case AT_CWJAP_DEF:    return "CWJAP_DEF";
        case AT_CIPSTART:     return "CIPSTART";
        case AT_CIPSEND:      return "CIPSEND";
        case AT_CIFSR:        return "CIFSR";
        default:              return "";
    }
}

// Flexible builder with va_list
static inline const char* cmd_build_va(cmd_type_t type, esp8266_cmd_base_t base, ...) {
    const char* bstr = cmd_base_to_string(base);
    va_list args;
    va_start(args, base);

    char temp[CMD_BUFFER_SIZE];
    temp[0] = '\0';

    switch(type) {
        case CMD_EXECUTE:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s\r\n", bstr);
            break;
        case CMD_QUERY:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s?\r\n", bstr);
            break;
        case CMD_QUERY_PARAM:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=?\r\n", bstr);
            break;
        case CMD_SET: {
            char* arg = NULL;
            int first = 1;
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=", bstr);
            while ((arg = va_arg(args, char*)) != NULL) {
                if (!first) strncat(CMD_BUFFER, ",", CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
                strncat(CMD_BUFFER, "\"", CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
                strncat(CMD_BUFFER, arg, CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
                strncat(CMD_BUFFER, "\"", CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
                first = 0;
            }
            strncat(CMD_BUFFER, "\r\n", CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
            break;
        }
    }

    va_end(args);
    return CMD_BUFFER;
}

/****************************
 * Thin semantic wrappers
 ****************************/
static inline const char* esp8266_reset(void) {
    return cmd_build_va(CMD_EXECUTE, AT_RST, NULL);
}

static inline const char* esp8266_version(void) {
    return cmd_build_va(CMD_EXECUTE, AT_GMR, NULL);
}

static inline const char* esp8266_query_ip(void) {
    return cmd_build_va(CMD_QUERY, AT_CIFSR, NULL);
}

static inline const char* esp8266_connect_ap(const char* ssid, const char* pwd) {
    return cmd_build_va(CMD_SET, AT_CWJAP_CUR, ssid, pwd, NULL);
}

static inline const char* esp8266_set_wifi_mode(uint8_t mode) {
    char mode_str[4];
    snprintf(mode_str, sizeof(mode_str), "%d", mode);
    return cmd_build_va(CMD_SET, AT_CWMODE_CUR, mode_str, NULL);
}

#endif




static inline const char* cmd_build_va(cmd_type_t type, esp8266_cmd_base_t base, const char* fmt, ...) {
    const char* bstr = cmd_base_to_string(base);
    CMD_BUFFER[0] = '\0';

    va_list args;
    va_start(args, fmt);

    switch(type) {
        case CMD_EXECUTE:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s\r\n", bstr);
            break;

        case CMD_QUERY:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s?\r\n", bstr);
            break;

        case CMD_QUERY_PARAM:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=?\r\n", bstr);
            break;

        case CMD_SET:
            snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=", bstr);
            if(fmt) {
                char argbuf[CMD_BUFFER_SIZE];
                vsnprintf(argbuf, sizeof(argbuf), fmt, args);
                strncat(CMD_BUFFER, argbuf, CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
            }
            strncat(CMD_BUFFER, "\r\n", CMD_BUFFER_SIZE - strlen(CMD_BUFFER) - 1);
            break;
    }

    va_end(args);
    return CMD_BUFFER;
}


static inline const char* esp8266_set_wifi_mode(uint8_t mode) {
    return cmd_build_va(CMD_SET, AT_CWMODE_CUR, "%d", mode);
}

static inline const char* esp8266_connect_ap(const char* ssid, const char* pwd) {
    return cmd_build_va(CMD_SET, AT_CWJAP_CUR, "\"%s\",\"%s\"", ssid, pwd);
}



case CMD_SET:
 {
            // Write prefix "AT+<cmd>=" directly
            n = snprintf(CMD_BUFFER, CMD_BUFFER_SIZE, "AT+%s=", cmd_str);
            if (n < 0) n = 0;
            if (fmt) {
                int m = vsnprintf(CMD_BUFFER + n, CMD_BUFFER_SIZE - n, fmt, args);
                if (m < 0) m = 0;
                n += m;
                if (n >= CMD_BUFFER_SIZE) n = CMD_BUFFER_SIZE - 1;
            }
            // Append CRLF safely
            if (n < CMD_BUFFER_SIZE - 2) {
                CMD_BUFFER[n++] = '\r';
                CMD_BUFFER[n++] = '\n';
                CMD_BUFFER[n] = '\0';
            } else if (n < CMD_BUFFER_SIZE - 1) {
                CMD_BUFFER[n++] = '\r';
                CMD_BUFFER[n] = '\0';
            } else {
                CMD_BUFFER[CMD_BUFFER_SIZE - 1] = '\0';
            }
        }
        break



while (1) {
    if (!isCharPtrFlush(usart1()->rxbuff) && usart1()->is_rx_idle()) {
        strncpy(parse, usart1()->rxbuff, parse_size);
        func()->tokenize_string(parse, tokens, MAX_TOKENS, "\r\n");
        usart1()->rx_purge();

        switch(esp_state) {
            case WAIT_FOR_IPD:
                if (strstr(tokens[0], "+IPD,")) {
                    esp_state = EXTRACT_LINK_ID;
                }
                break;

            case EXTRACT_LINK_ID:
                // "+IPD,<id>,<len>:<data>"
                current_link_id = tokens[0][5] - '0'; // assuming single-digit IDs
                esp_state = PROCESS_REQUEST;
                break;

            case PROCESS_REQUEST:
                if (current_link_id >= 0) {
                    // Example: status request
                    if (strstr(tokens[0], "status")) {
                        char* status_text = (stm32f411ceu6()->gpioc->ODR & (1 << 13)) ? "OFF\r\n" : "ON\r\n";
                        Turingi25to28_Station_Mux1ServerSend_tcp(current_link_id, status_text, strlen(status_text));
                    }
                    // Handle button requests similarly...
                }
                esp_state = WAIT_FOR_IPD; // reset for next request
                break;
        }
    }
}
