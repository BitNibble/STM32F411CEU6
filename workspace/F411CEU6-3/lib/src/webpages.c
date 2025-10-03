#include "webpages.h"

const char* htmlContent_1 =
"<!DOCTYPE html>"
"<html lang='en'>"
"<head>"
"<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"<title>ESP8266 Example</title><style>body { font-family: Arial, sans-serif; } h1 { color: #333; }</style>"
"</head>"
"<body>"
"<h1>Sergio Welcome to ESP8266 PHP Page!</h1><p>This is a simple HTML page served by PHP.</p>"
"</body>"
"</html>";
const size_t htmlContent_1_size = 353; //353

const char* htmlContent_2 =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Input</title>"
"</head>"
"<body>"
"<h1>Send Data to ESP8266</h1>"
"<input type=\"text\" id=\"dataInput\" placeholder=\"Enter your data here\">"
"<button onclick=\"sendData()\">Send</button>"
"<script>"
"function sendData() {"
"const input = document.getElementById('dataInput').value;"
"fetch('/data', {"
"method: 'POST',"
"headers: {"
"'Content-Type': 'application/json',"
"},"
"body: JSON.stringify({ data: input }),"
"})"
".then(response => response.json())"
".then(data => {"
"console.log('Success:', data);"
"alert('Data sent successfully!');"
"})"
".catch((error) => {"
"console.error('Error:', error);"
"alert('Error sending data.');"
"});"
"}"
"</script>"
"</body>"
"</html>" ;
const size_t htmlContent_2_size = 734; // 734

const char* htmlContent_3 =
"<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<title>ESP8266 Button Page</title>"
"<style>"
"body {"
"font-family: Arial, sans-serif;"
"text-align: center;"
"padding: 20px;"
"}"
".button {"
"font-size: 20px;"
"padding: 15px 30px;"
"margin: 20px;"
"cursor: pointer;"
"background-color: #4CAF50;"
"color: white;"
"border: none;"
"border-radius: 5px;"
"transition: background-color 0.3s;"
"}"
".button:disabled {"
"background-color: #ccc;"
"cursor: not-allowed;"
"}"
".button:hover:not(:disabled) {"
"background-color: #45a049;"
"}"
"</style>"
"</head>"
"<body>"
"<h1>Press a Button</h1>"
"<button class=\"button\" onclick=\"sendMessage('Button1', 'button1')\" id=\"button1\">Switch ON</button>"
"<button class=\"button\" onclick=\"sendMessage('Button2', 'button2')\" id=\"button2\">Switch OFF</button>"
"<script>"
"let requestInProgress = false;"
"function sendMessage(message, buttonId) {"
"if (requestInProgress) {"
"console.log('Request already in progress, ignoring button press:', message);"
"return;"
"}"
"requestInProgress = true;"
"const button = document.getElementById(buttonId);"
"button.disabled = true;"
"console.log('Sending message:', message);"
"var xhr = new XMLHttpRequest();"
"xhr.open('GET', '/send?message=' + encodeURIComponent(message), true);"
"xhr.onreadystatechange = function() {"
"if (xhr.readyState === 4) {"
"button.disabled = false;"
"requestInProgress = false;"
"if (xhr.status === 200) {"
"console.log('Message sent:', message);"
"} else {"
"console.error('Server error:', xhr.status);"
"alert('Server error. Please try again.');"
"}"
"}"
"};"
"xhr.send();"
"}"
"</script>"
"</body>"
"</html>";
const size_t htmlContent_3_size = 1526; // 1526

const char* htmlContent_4 =
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
const size_t htmlContent_4_size = 1278; // 1278

// Formula 4 x <number of line> - <number of \">

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

const size_t htmlContent_200_v3_size = 33;

const char* htmlContent_200_v4 =
"HTTP/1.1 200 OK\r\n"
"Content-Length: 0\r\n"
"\r\n";

const size_t htmlContent_200_v4_size = 38;

const char* htmlContent_200_v5 =
"HTTP/1.1 200 OK\r\n"
"\r\n";

const size_t htmlContent_200_v5_size = 19;

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

web_page webpage_4(void) // to remove
{
	web_page page;
	page.str = (char*)htmlContent_4;
	page.size = htmlContent_4_size;
	return page;
}

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
