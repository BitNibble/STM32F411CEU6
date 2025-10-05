#include "webpages.h"


const char htmlContent_1[] =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Button Page</title>"
"<style>"
"body { font-family: Arial, sans-serif; text-align: center; padding: 30px; background: #f0f0f0; }"
"h1 { color: #333; }"
".button { font-size: 22px; padding: 20px 40px; margin: 15px; cursor: pointer;"
"background-color: #4CAF50; color: white; border: none; border-radius: 8px;"
"transition: all 0.3s ease; }"
".button:disabled { background-color: #ccc; cursor: not-allowed; }"
".button:hover:not(:disabled) { background-color: #45a049; transform: scale(1.05); }"
"</style>"
"</head>"
"<body>"
"<h1>ESP8266 Control</h1>"
"<button class=\"button\" onclick=\"sendMessage('Button1', 'button1')\" id=\"button1\">Switch ON</button>"
"<button class=\"button\" onclick=\"sendMessage('Button2', 'button2')\" id=\"button2\">Switch OFF</button>"
"<script>"
"let inProgress=false;"
"function sendMessage(msg,id){"
"if(inProgress) return;"
"inProgress=true;"
"const b=document.getElementById(id);"
"b.disabled=true;"
"let xhr=new XMLHttpRequest();"
"xhr.open('GET','/send?message='+encodeURIComponent(msg),true);"
"xhr.onreadystatechange=function(){"
"if(xhr.readyState===4){"
"b.disabled=false;"
"inProgress=false;"
"if(xhr.status!==200) alert('Server error: '+xhr.status);"
"}};"
"xhr.send();"
"}"
"</script>"
"</body>"
"</html>";

const size_t htmlContent_1_size = sizeof(htmlContent_1) - 1; // 1278

const char htmlContent_2[] =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Button Page</title>"
"<style>"
"body { font-family: Arial, sans-serif; text-align: center; padding: 30px; background: #f0f0f0; }"
"h1 { color: #333; }"
".button { font-size: 22px; padding: 20px 40px; margin: 15px; cursor: pointer;"
"background-color: #4CAF50; color: white; border: none; border-radius: 8px;"
"transition: all 0.3s ease; }"
".button:disabled { background-color: #ccc; cursor: not-allowed; }"
".button:hover:not(:disabled) { background-color: #45a049; transform: scale(1.05); }"
"#statusBox { margin-top: 20px; font-size: 24px; padding: 10px; border: 2px solid #333; border-radius: 8px; display: inline-block; min-width: 120px; }"
"</style>"
"</head>"
"<body>"
"<h1>ESP8266 Control</h1>"
"<div id=\"statusBox\">OFF</div>"
"<br>"
"<button class=\"button\" onclick=\"sendMessage('Button1', 'button1')\" id=\"button1\">Switch ON</button>"
"<button class=\"button\" onclick=\"sendMessage('Button2', 'button2')\" id=\"button2\">Switch OFF</button>"
"<script>"
"let inProgress=false;"
"function sendMessage(msg,id){"
"if(inProgress) return;"
"inProgress=true;"
"const b=document.getElementById(id);"
"b.disabled=true;"
"let xhr=new XMLHttpRequest();"
"xhr.open('GET','/send?message='+encodeURIComponent(msg),true);"
"xhr.onreadystatechange=function(){"
"if(xhr.readyState===4){"
"b.disabled=false;"
"inProgress=false;"
"if(xhr.status===200){"
"document.getElementById('statusBox').innerText = msg === 'Button1' ? 'ON' : 'OFF';"
"} else {"
"alert('Server error: '+xhr.status);"
"}};"
"};"
"xhr.send();"
"}"
"</script>"
"</body>"
"</html>";

const size_t htmlContent_2_size = sizeof(htmlContent_2) - 1;

const char htmlContent_3[] =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Button Page</title>"
"<style>"
"body { font-family: Arial, sans-serif; text-align: center; padding: 30px; background: #f0f0f0; }"
"h1 { color: #333; }"
".button { font-size: 22px; padding: 20px 40px; margin: 15px; cursor: pointer;"
"background-color: #4CAF50; color: white; border: none; border-radius: 8px;"
"transition: all 0.3s ease; }"
".button:disabled { background-color: #ccc; cursor: not-allowed; }"
".button:hover:not(:disabled) { background-color: #45a049; transform: scale(1.05); }"
"#statusBox { margin-top: 20px; font-size: 24px; padding: 10px; border: 2px solid #333; border-radius: 8px; display: inline-block; min-width: 120px; }"
"</style>"
"</head>"
"<body>"
"<h1>ESP8266 Control</h1>"
"<div id=\"statusBox\">OFF</div>"
"<br>"
"<button class=\"button\" onclick=\"sendMessage('Button1', 'button1')\" id=\"button1\">Switch ON</button>"
"<button class=\"button\" onclick=\"sendMessage('Button2', 'button2')\" id=\"button2\">Switch OFF</button>"
"<button class=\"button\" onclick=\"checkStatus()\" id=\"check_status\">Check Status</button>"
"<script>"
"let inProgress=false;"
"function sendMessage(msg,id){"
" if(inProgress) return;"
" inProgress=true;"
" const b=document.getElementById(id);"
" b.disabled=true;"
" let xhr=new XMLHttpRequest();"
" xhr.open('GET','/send?message='+encodeURIComponent(msg),true);"
" xhr.onreadystatechange=function(){"
"  if(xhr.readyState===4){"
"    b.disabled=false;"
"    inProgress=false;"
"    if(xhr.status===200){"
"      document.getElementById('statusBox').innerText = msg === 'Button1' ? 'ON' : 'OFF';"
"    } else {"
"      alert('Server error: '+xhr.status);"
"    }"
"  }"
" };"
" xhr.send();"
"}"
"function checkStatus(){"
" let xhr=new XMLHttpRequest();"
" xhr.open('GET','/send?message=status',true);"
" xhr.onreadystatechange=function(){"
"   if(xhr.readyState===4 && xhr.status===200){"
"     document.getElementById('statusBox').innerText = xhr.responseText;"
"   }"
" };"
" xhr.send();"
"}"
"</script>"
"</body>"
"</html>";

const size_t htmlContent_3_size = sizeof(htmlContent_3) - 1;

web_page webpage_1(void)
{
	web_page page;
	page.str = (char*)htmlContent_1;
	page.size = htmlContent_1_size;
	return page;
}

web_page webpage_2(void)
{
	web_page page;
	page.str = (char*)htmlContent_2;
	page.size = htmlContent_2_size;
	return page;
}

web_page webpage_3(void) // to remove
{
	web_page page;
	page.str = (char*)htmlContent_3;
	page.size = htmlContent_3_size;
	return page;
}

/*
web_page webpage_4(void) // to remove
{
	web_page page;
	page.str = (char*)htmlContent_4;
	page.size = htmlContent_4_size;
	return page;
}

web_page webpage_5(void) // to remove
{
	web_page page;
	page.str = (char*)htmlContent_5;
	page.size = htmlContent_5_size;
	return page;
}
*/

/***********/
/*** 200 ***/
/***********/
// Send response back to client
const char* htmlContent_200_v1 =
"HTTP/1.1 200 OK";
const size_t htmlContent_200_v1_size = 15; // 15

// Send response back to client
const char* htmlContent_200_v2 =
"HTTP 200 OK";
const size_t htmlContent_200_v2_size = 11; // 11

const char* htmlContent_200_v3 =
"HTTP/1.1 200 OK"
"Content-Length: 0";

const size_t htmlContent_200_v3_size = 33; // 33

const char* htmlContent_200_v4 =
"HTTP/1.1 200 OK\r\n"
"Content-Length: 0\r\n"
"\r\n";

const size_t htmlContent_200_v4_size = 38; // 38

const char* htmlContent_200_v5 =
"HTTP/1.1 200 OK\r\n"
"\r\n";

const size_t htmlContent_200_v5_size = 19; // 19

web_page webpage_200(void)
{
	web_page page;
	page.str = (char*)htmlContent_200_v5;
	page.size = htmlContent_200_v5_size;
	return page;
}

/*** EOF ***/

/*** Comment ***
To calculate the size of the html file to use it in the at commands,
one should copy the text in a text editor, shift left the whole text,
then in the bottom it should indicate how many bytes it has, after that
subtract the number of lines to the number of characters to get the actual
size. To have a preview just change the file type to html and open it in
any internet explorer (chrome, firefox, etc).
If use it has a string has it is done here one must then escape all the special
characters, and add the parenthesis, for it used as a string.
****************/

